/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "server_codesys23.h"
#include "api.h"
#include "device.h"
#include "devicecommunicationcontrol_codesys23.h"
#include "licensing.h"
#include "plc_filesystem.h"
#include "PT/files.h"
#include "PT/paths.h"
#include "reinitialize_codesys23.h"
#include "status_info.h"
#include "typelabel.h"

// Local prototypes
static void server_codesys23_invalidate_plc_memory(bool online_change);
static void load_hardware_id(void);
static void codesys23_set_device_object_softwareinfo(void);
static void hook_provide_application_software_version(void);

// Local variables
bool CodeSys_DownloadBegun = false; // Flag used to prevent creating objects while online-change is happening
static char hardware_id_model_number[MAX_DEV_MOD_LEN + 1] = { 0 };
static char hardware_id_model_name[MAX_DEV_MOD_LEN + 1] = { 0 };
static char hardware_id_mac[MAX_DEV_MOD_LEN + 1] = { 0 };
static char hardware_id_serial_number[128] = { 0 };
static bool hardware_id_has_valid_serial = false;


/** Initialize the BACnet server for CodeSys v2.3
*/
bool server_codesys23_init(void)
{
	// Initialize our filesystem.
	plc_filesystem_init();

	// Load hardware info from our PLC for licensing.
	load_hardware_id();
#ifndef LICENSE_ALLOW_INVALID_HARDWARE_ID
	if (hardware_id_has_valid_serial)
#endif
	{
		licensing_set_challenge_code_raw(hardware_id_serial_number);
	}

	// Execute the zaphire_boot.sh file that was attached to the install.
	system("/etc/bacnet/zaphire_boot.sh");

	// Initialize the BACnet server using the API
	bool success = bacnet_api_server_init();
	if (success)
	{
		// Initialize ReinitializeDevice and DeviceCommunicationControl- handlers
		devicecommunicationcontrol_codesys23_init();
		reinitialize_codesys23_init();

		// Apply information from our hardware controller to the Device Object.
		Device_Object_Set_Model_Name(hardware_id_model_name);
		Device_Object_Set_Serial_Number(hardware_id_serial_number);

		// Add hook so we can set the app version correctly each time property is read
		Device_Object_Set_Application_Software_Version_Callback(hook_provide_application_software_version);
	}
	return success;
}


/** Stops and cleans up all resources used by the BACnet server for CodeSys v2.3
*/
void server_codesys23_cleanup(void)
{
	// Remove hooks
	Device_Object_Set_Application_Software_Version_Callback(NULL);

	// Cleanup ReinitializeDevice and DeviceCommunicationControl- handlers
	reinitialize_codesys23_cleanup();
	devicecommunicationcontrol_codesys23_cleanup();

	// Clean up all resources/threads/memory used by the BACnet stack using the API
	bacnet_api_server_cleanup();
}


/** Resets the state of the BACnet server to an initial stopped state.
*/
void server_codesys23_reset(bool online_change)
{
	// If not online change
	if (!online_change)
	{
		// Stop the server if not online change
		bacnet_api_server_stop();

		// Reset persistence status so we're ready to load again
		bacnet_api_persist_reset();
	}

	// Invalidate all PLC memory so the stack cannot use it anymore
	server_codesys23_invalidate_plc_memory(online_change);
}


/** Call when user is about to download PLC program.
*/
void server_codesys23_plc_program_before_download(void)
{
	// Increment database revision because when PLC program changes, our tags might also change.
	bacnet_api_before_program_download();
}


/** Invalidates all memory eventually referenced by the BACnet Stack to the PLC memory (pointers, PLC objects etc...)
*/
static void server_codesys23_invalidate_plc_memory(bool online_change)
{
	// Invalidate BACnet objects previously registered as they might be moved in memory during Online-Change
	// Also destroy dynamically created objects if not Online Change
	bacnet_api_invalidateobjects(!online_change);

	// Reset status info so we don't keep writing debug info to non-existing memory
	status_info_set_instance(NULL);
}


/** Loads the hardware info into local variables.
*/
static void load_hardware_id()
{
	hardware_id_has_valid_serial = true;

	// Set our model name read from typelabel.
	const char* typelabel = typelabel_get_model_name();
	if (typelabel)
	{
		snprintf(hardware_id_model_number, sizeof(hardware_id_model_number), "%s", typelabel);
		snprintf(hardware_id_model_name, sizeof(hardware_id_model_name), "Zaphire B-BC %s", typelabel);
	}
	else
	{
		snprintf(hardware_id_model_number, sizeof(hardware_id_model_number), "%s", "Unknown");
		snprintf(hardware_id_model_name, sizeof(hardware_id_model_name), "%s", "Zaphire B-BC");
		typelabel = "Unknown";
		hardware_id_has_valid_serial = false;
	}

	// Get the MAC address.
	const char* mac_adr = typelabel_get_mac();
	if (mac_adr)
	{
		snprintf(hardware_id_mac, sizeof(hardware_id_mac), "%s", mac_adr);
	}
	else
	{
		snprintf(hardware_id_mac, sizeof(hardware_id_mac), "%s", "FF:FF:FF:FF:FF:FF");
		hardware_id_has_valid_serial = false;
	}

	// Get the unique ID for serial.
	const char* unique_id = typelabel_get_unique_identifier();
	snprintf(hardware_id_serial_number, sizeof(hardware_id_serial_number), "%s,%s%s%s", 
		hardware_id_model_number, hardware_id_mac, (unique_id != NULL) ? "," : "", (unique_id != NULL) ? unique_id : "");
}


/* Transfers information from the user application to the Device Object
*/
static void codesys23_set_device_object_softwareinfo(void)
{
	// Get the version number based on when the DEFAULT.PRG file was loaded (info from filesystem)
	char app_software_version[64];
	time_t modified_local_time = 0;
	char buffer[MAX_PATH_SIZE];
	reinitialize_codesys23_get_backup_restore_filepath(buffer, sizeof(buffer), "DEFAULT.PRG");
	if (file_get_time_modified(buffer, &modified_local_time))
	{
		BACNET_DATE_TIME bac_dt = { { 0 } };
		datetime_local_to_bac(&bac_dt, modified_local_time);
		snprintf(app_software_version, sizeof(app_software_version), "%04u.%02u.%02u-%02u:%02u:%02u", bac_dt.date.year, bac_dt.date.month, bac_dt.date.day, bac_dt.time.hour, bac_dt.time.min, bac_dt.time.sec);
	}
	else
	{
		snprintf(app_software_version, sizeof(app_software_version), "No application");
	}

	// Set the application version
	Device_Object_Set_Application_Software_Version(app_software_version);
}


/** Provides a new application software version when the device object property is read
*/
static void hook_provide_application_software_version(void)
{
	codesys23_set_device_object_softwareinfo();
}
