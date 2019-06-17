/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "native/native_objects.h"
#include "binary_common.h"
#include "device.h"
#include "native/native_io_modules.h"
#include "PT/logging.h"
#include <ldkc_kbus_register_communication.h> 

static const char* LogCategory = "NativeObjects";

/** Local function prototypes */
static bool create_native_objects(void);
static void create_native_objects_for_terminal(uint16_t TerminalPosition, uint16_t RelPos, uint16_t TerminalType, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void delete_all_native_objects(void);

/** Local static variables */
static uint32_t UniqueID = 0;
static BACNET_NATIVE_OBJECTS* hashtable = NULL;
static tDeviceId adi_deviceId = -1;
static tApplicationDeviceInterface* adi_current = NULL;
static tldkc_KbusInfo_TerminalInfo terminalDescription[LDKC_KBUS_TERMINAL_COUNT_MAX];


/** Reads out all IO modules from PLC and creates the native objects that represents them.
Call this when PLC starts up and IO modules are ready.
*/
bool native_objects_init(void)
{
	// Are native objects enabled?
	if (!BACNET_NATIVE_OBJECTS_ENABLED)
		return false;

	// Connect to ADI-interface and init the interface
	tApplicationDeviceInterface* adi = adi_GetApplicationInterface();

	/// TODO: Check if it's a good idea to call Init() here. It might be already initialized by CodeSys?
	adi->Init();

	// Scan for devices
	size_t nrDevicesFound;               // number of devices found
	tDeviceInfo deviceList[10];          // the list of devices given by the ADI
	adi->ScanDevices();
	adi->GetDeviceList(sizeof(deviceList), deviceList, &nrDevicesFound);

	// Find the kbus device
	int nrKbusFound = -1;             // position of the kbus in the list
	size_t i;
	for (i = 0; i < nrDevicesFound; ++i)
	{
		if (strcmp(deviceList[i].DeviceName, "libpackbus") == 0)
		{
			nrKbusFound = i;
			bacnet_log_debug_printf(LogCategory, "KBUS device found as device %i", i);
			break;
		}
	}

	// Kbus device not found > exit
	if (nrKbusFound == -1)
	{
		bacnet_log_debug_printf(LogCategory, "%s", "No KBUS device found");
		adi->Exit(); // Disconnect ADI-Interface  (TODO: Check this. Might not be a good idea if it's used by CodeSys)
		return false;
	}

	// Retrieve the device id
	adi_deviceId = deviceList[nrKbusFound].DeviceId;
	bacnet_log_debug_printf(LogCategory, "KBUS device id %i", adi_deviceId);

	// Is device open?
	bool dev_open = adi->IsDeviceOpen(adi_deviceId);
	bacnet_log_debug_printf(LogCategory, "adi->IsDeviceOpen = %u", dev_open);
	if (!dev_open)
	{
		bacnet_log_debug_printf(LogCategory, "%s", "Device is not open");
		adi->Exit(); // Disconnect ADI-Interface  (TODO: Check this. Might not be a good idea if it's used by CodeSys)
		return false;
	}

	// Create all the native objects for the terminals using K-bus interface
	create_native_objects();

	// Success. Store adi for later access to IO- modules.
	adi_current = adi;
	return true;
}


/** Updates all native objects according to the given event type.
Call this at specific events in PLC cycle to process each native object.
@param EventType [in] Type of event to process (sent directly to the IO module handlers)
*/
void native_objects_process(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType)
{
	// Are native objects enabled?
	if (!BACNET_NATIVE_OBJECTS_ENABLED)
		return;

	// Check that we have an adi interface (if earlier call to 'init' succeeded)
	if (!adi_current)
		return;

	// Set up the arguments we pass to the processing functions
	BACNET_NATIVE_OBJECT_EVENT_ARGS Args;
	Args.adi = adi_current;
	Args.adi_deviceId = adi_deviceId;
	Args.adi_taskId = 0;

	// Iterate each native object created earlier.
	// Call their event- method if it exists.
	BACNET_NATIVE_OBJECTS *pCurrent, *pTemp;
	BAC_HASH_ITER(hh, hashtable, pCurrent, pTemp)
	{
		if (pCurrent->fn_process)
		{
			Args.native = pCurrent;
			pCurrent->fn_process(EventType, &Args);
		}
	}
}


/** Deletes all native objects and cleans up native objects.
Call this when PLC is shut down or when IO modules have changed.
*/
void native_objects_cleanup(void)
{
	// Check that we have an adi interface (if earlier call to 'init' succeeded)
	if (!adi_current)
		return;

	// Close the adi interface
	//adi_current->Exit();		// TODO: Check this with Wago. Calling this terminales the IO- bus during CodeSys download.
	adi_current = NULL;
	adi_deviceId = -1;

	// Delete our native objects
	delete_all_native_objects();
}


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4702)
#endif
/** Create a native objects terminal for the given PLC terminal
@param pTerminalInfo [in] Pointer to the terminal info
@param TerminalTypePos [in] Relative position of to terminal in the IO stack of the same type (example type:555, 5 = 5th card of the type 555)
@param TerminalType [in] Type of terminal (example 555)
@param fn_event [in] Callback function for events (called from 'native_objects_process')
*/
BACNET_NATIVE_OBJECTS* native_terminal_create(tldkc_KbusInfo_TerminalInfo* pTerminalInfo, uint16_t TerminalTypePos, uint16_t TerminalType, bacnet_native_object_event fn_event)
{
	// Alloc the native object
	BACNET_NATIVE_OBJECTS* pCreated = calloc(1, sizeof(*pCreated));
	if (pCreated)
	{
		// Set it up and add to the hashtable
		pCreated->id = ++UniqueID;
		pCreated->terminal_info = *pTerminalInfo;
		pCreated->fn_process = fn_event;
		pCreated->TerminalTypePos = TerminalTypePos;
		pCreated->TerminalType = TerminalType;
		BAC_HASH_ADD(hh, hashtable, id, sizeof(hashtable->id), pCreated);
	}

	// Return the created object
	return pCreated;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif


/** Create a BACnet native object for the given terminal.
The Object Name is formatted in this way:
{strPrefix}_{TerminalType}_{TerminalTypePos}_C{Channel}[.{strSuffix}]

For example:
AO_555_04_C03 = Analog Output, Terminal Type 555, 4th card of type 555, channel 03

@param pNative [in] Native objects terminal created using 'native_terminal_create'
@param strPrefix [in] Prefix for the Object Name of this native object to create
@param ObjectType [in] BACnet Object Type to create for this native object
@param Channel [in] Channel number for the channel on this terminal that the object is created for (1 or higher)
@param strSuffix [in] Suffix to add at the end of the Object Name of the terminal (NULL = no suffix)
*/
BACNET_NATIVE_OBJECT_REF* native_object_create(BACNET_NATIVE_OBJECTS* pNative, const char* strPrefix, BACNET_OBJECT_TYPE ObjectType, uint16_t Channel, const char* strSuffix)
{
	// Find free space in the list of references
	BACNET_NATIVE_OBJECT_REF* pFound = NULL;
	int i;
	for (i = 0; i < MAX_BACNET_NATIVE_OBJECT_REF_PER_TERMINAL; i++)
	{
		if (!pNative->ref[i].Exists)
		{
			pFound = &pNative->ref[i];
			break;
		}
	}
	if (pFound)
	{
		// Generate the BACnet Object Name to use for this native object
		char ObjectName[MAX_OBJECT_NAME_SIZE];
		if (strSuffix && strSuffix[0])
			snprintf(ObjectName, sizeof(ObjectName) - 1, "%s_%u_%02u_C%02u.%s", strPrefix, pNative->TerminalType, pNative->TerminalTypePos, Channel, strSuffix);
		else
			snprintf(ObjectName, sizeof(ObjectName) - 1, "%s_%u_%02u_C%02u", strPrefix, pNative->TerminalType, pNative->TerminalTypePos, Channel);

		// Create the BACnet tag. Instance number is autogenerated using FNV22 for preserving them without needing a persistent storage.
		BACNET_COMMON_DESCR* pCreatedObject = Device_Create_Object(ObjectName, NULL, ObjectType, BACNET_MAX_INSTANCE, false);
		if (!pCreatedObject)
			return NULL;

		// Created native BACnet tags should always persist their state, limit values and configuration across power failures
		// These properties may be changed by the programmer, the BMS top-system at any time.
		pCreatedObject->Internal.PersistSettings = BACNET_PERSIST_PRESENTVALUE_IF_FLAG | BACNET_PERSIST_PROPERTIES | BACNET_PERSIST_CONFIGURATION;
		pCreatedObject->Internal.Persist = true;

		// Init the native object created
		pFound->ObjectID.type = pCreatedObject->ObjectType;
		pFound->ObjectID.instance = pCreatedObject->ObjectID;
		pFound->Exists = true;
	}

	// Return the created object
	return pFound;
}


/** Process a BACnet Binary Value for an input according to the new value and Reliability
@param pObjectID [in] Object ID of the BACnet object to alter that represents this input
@param NewValue [in] The new binary value coming from the physical IO- module input
@param Reliability [in] The current reliability status of the 'NewValue' parameter (use 'RELIABILITY_NO_FAULT_DETECTED' in case of no fault)
@param pInputPV [in/out] The actual value that should be used by the PLC program (Priority-Array and Out-Of-Service state taken into account)
@return true in case of success (pOutputPV is never altered in case of failure)
*/
bool native_object_process_input_bv(BACNET_OBJECT_ID* pObjectID, bool NewValue, BACNET_RELIABILITY Reliability, bool* pInputPV)
{
	// Fetch the object of the given ID
	BINARY_OBJECT_DESCR* pBO = Binary_Object_Cast(Device_Object_Instance_ById(pObjectID->type, pObjectID->instance));
	if (!pBO) return false;

	// Set actual the reliability according to the input.
	// This will eventually trigger eventstate changes according to the BACnet tags' configuration.
	pBO->Reliability = Reliability;

	// Update the value if Out-Of-Service is not set
	if (!pBO->Out_Of_Service)
	{
		pBO->Priority_Array_Val[15] = NewValue;
		pBO->Priority_Array_En[15] = true;
		//Device_Update_Object(&pBO->Common);
	}

	// Set the PLC input variable
	if (pInputPV)
	{
		// TODO: Take polarity of the object into account
		//if(pBO->Polarity)
		//	*pInputPV = !pBO->Present_Value;
		//else
			*pInputPV = pBO->Present_Value;
	}

	// Success
	return true;
}


/** Process a BACnet Binary Value for an output according to the Reliability
@param pObjectID [in] Object ID of the BACnet object to alter that represents this output
@param NewValue [in] The binary value for this output coming from the PLC program
@param Reliability [in] The current reliability status of the output (use 'RELIABILITY_NO_FAULT_DETECTED' in case of no fault)
@param pOutputPV [in/out] The actual value that should be used by the physical IO module output (Priority-Array and Out-Of-Service state taken into account)
@return true in case of success (pOutputPV is never altered in case of failure)
*/
bool native_object_process_output_bv(BACNET_OBJECT_ID* pObjectID, bool NewValue, BACNET_RELIABILITY Reliability, bool* pOutputPV)
{
	// Fetch the object of the given ID
	BINARY_OBJECT_DESCR* pBO = Binary_Object_Cast(Device_Object_Instance_ById(pObjectID->type, pObjectID->instance));
	if (!pBO) return false;

	// Set actual the reliability according to the input.
	// This will eventually trigger eventstate changes according to the BACnet tags' configuration.
	pBO->Reliability = Reliability;

	// Update the value if Out-Of-Service is not set
	if (!pBO->Out_Of_Service)
	{
		pBO->Priority_Array_Val[15] = NewValue;
		pBO->Priority_Array_En[15] = true;
		//Device_Update_Object(&pBO->Common);
	}

	// Set the IO module output
	if (pOutputPV)
	{
		// TODO: Take polarity of the object into account
		//if(pBO->Polarity)
		//	*pOutputPV = !pBO->Present_Value;
		//else
			*pOutputPV = pBO->Present_Value;
	}

	// Success
	return true;
}


/** Creates all the BACnet native objects by reading out terminals from K-bus
*/
static bool create_native_objects(void)
{
	// Create K-bus info structure for retrieving data from the K-bus
	if (KbusInfo_Failed == ldkc_KbusInfo_Create())
	{
		bacnet_log_debug_printf(LogCategory, "%s", "ldkc_KbusInfo_Create() failed");
		return false;
	}

	// Get data for the connected terminals
	tldkc_KbusInfo_Status status;
	if (KbusInfo_Failed == ldkc_KbusInfo_GetStatus(&status))
	{
		bacnet_log_debug_printf(LogCategory, "%s", "ldkc_KbusInfo_GetStatus() failed");
		ldkc_KbusInfo_Destroy();
		return false;
	}
	bacnet_log_debug_printf(LogCategory, "\n        .KbusBitCount: %i ", status.KbusBitCount);
	bacnet_log_debug_printf(LogCategory, "\n        .TerminalCount: %i ", status.TerminalCount);
	bacnet_log_debug_printf(LogCategory, "\n        .ErrorCode: %i ", status.ErrorCode);
	bacnet_log_debug_printf(LogCategory, "\n        .ErrorArg: %i ", status.ErrorArg);
	bacnet_log_debug_printf(LogCategory, "\n        .ErrorPos: %i ", status.ErrorPos);
	bacnet_log_debug_printf(LogCategory, "\n        .BitCountAnalogInput: %i ", status.BitCountAnalogInput);
	bacnet_log_debug_printf(LogCategory, "\n        .BitCountAnalogOutput: %i ", status.BitCountAnalogOutput);
	bacnet_log_debug_printf(LogCategory, "\n        .BitCountDigitalInput: %i ", status.BitCountDigitalInput);
	bacnet_log_debug_printf(LogCategory, "\n        .BitCountDigitalOutput: %i ", status.BitCountDigitalOutput);

	// Get detailed information about every connected terminal
	unsigned char ucPosition;
	unsigned char ucIndex;
	size_t ucMaxPosition;
	size_t terminalCount;
	u16 terminals[LDKC_KBUS_TERMINAL_COUNT_MAX];
	if (KbusInfo_Failed == ldkc_KbusInfo_GetTerminalInfo(OS_ARRAY_SIZE(terminalDescription), terminalDescription, &terminalCount))
	{
		bacnet_log_debug_printf(LogCategory, "%s", "ldkc_KbusInfo_GetTerminalInfo() failed");
		ldkc_KbusInfo_Destroy();
		return false;
	}
	if (KbusInfo_Failed == ldkc_KbusInfo_GetTerminalList(OS_ARRAY_SIZE(terminals), terminals, NULL))
	{
		bacnet_log_debug_printf(LogCategory, "ldkc_KbusInfo_GetTerminalList() failed");
		ldkc_KbusInfo_Destroy();
		return false;
	}
	ucPosition = 1;
	ucMaxPosition = terminalCount;

	// Iterate each terminal found
	uint16_t RelativePosition;
	int j;
	for (ucIndex = 0; ucPosition <= ucMaxPosition; ucPosition++, ucIndex++)
	{
		const u32 idx = ucPosition - 1;

		// Calculate the relative position according to card type number
		RelativePosition = 1;
		for (j = 0; j < ucIndex; j++)
		{
			if (terminals[j] == terminals[ucIndex])
				++RelativePosition;
		}

		// Create the native objects for this terminal
		create_native_objects_for_terminal(ucPosition, RelativePosition, terminals[idx], &terminalDescription[idx]);
	}

	// Clean up after us
	ldkc_KbusInfo_Destroy();

	// Success
	return true;
}


/** Creates BACnet native objects for a single terminal on the K-bus
*/
static void create_native_objects_for_terminal(uint16_t TerminalPosition, uint16_t RelPos, uint16_t TerminalType, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Debug info
	bacnet_log_debug_printf(LogCategory, "Pos:%i;", TerminalPosition);
	if (0 == (TerminalType & 0x8000))
	{
		// Show second part of order number in "dec" format for complex IO-Terminals
		bacnet_log_debug_printf(LogCategory, "\t Type:%i;", TerminalType);
	}
	else
	{
		// Show bit coded information of stupid digital IO-Terminals in "hex" format			
		bacnet_log_debug_printf(LogCategory, "\t Type:0x%x;", TerminalType);
	}
	bacnet_log_debug_printf(LogCategory, "\t BitOffsetOut:%i;", pTerminalInfo->OffsetOutput_bits);
	bacnet_log_debug_printf(LogCategory, "\t BitSizeOut:%i;", pTerminalInfo->SizeOutput_bits);
	bacnet_log_debug_printf(LogCategory, "\t BitOffsetIn:%i;", pTerminalInfo->OffsetInput_bits);
	bacnet_log_debug_printf(LogCategory, "\t BitSizeIn:%i;", pTerminalInfo->SizeInput_bits);
	bacnet_log_debug_printf(LogCategory, "\t Channels:%i;", pTerminalInfo->AdditionalInfo.ChannelCount);
	bacnet_log_debug_printf(LogCategory, "\t PiFormat:%i;", pTerminalInfo->AdditionalInfo.PiFormat);
	bacnet_log_debug_printf(LogCategory, "\n");

	// Create the native object
	native_io_modules_create(TerminalType, RelPos, pTerminalInfo);
}


/** Deletes all BACnet native objects ever created by us
*/
static void delete_all_native_objects(void)
{
	// Delete all the native objects
	BACNET_NATIVE_OBJECTS *pCurrent, *pTemp;
	BAC_HASH_ITER(hh, hashtable, pCurrent, pTemp)
	{
		// Delete the BACnet objects
		int i;
		for (i = 0; i < MAX_BACNET_NATIVE_OBJECT_REF_PER_TERMINAL; i++)
		{
			if (pCurrent->ref[i].Exists)
			{
				Device_Delete_Object_ByID(&pCurrent->ref[i].ObjectID, false);
				pCurrent->ref[i].Exists = false;
			}
		}

		// Remove from hashtable and free the native instance
		BAC_HASH_DELETE(hh, hashtable, pCurrent);
		free(pCurrent);
		pCurrent = NULL;
	}
}
