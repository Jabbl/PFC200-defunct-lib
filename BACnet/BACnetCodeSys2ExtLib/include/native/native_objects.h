/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#pragma once

#include "dal/adi_application_interface.h"
#include <ldkc_kbus_information.h>          
#include <stdint.h>
#include "bacdef.h"
#include "PT/hashtable.h"

/* Forward declarations */
struct bacnet_native_objects;

/** Maximum number of native BACnet objects per terminal **/
#define MAX_BACNET_NATIVE_OBJECT_REF_PER_TERMINAL 32


/** The type of event to process the native objects for **/
typedef enum
{
	BACNET_NATIVE_OBJECT_EVENT_TYPE_UPDATE = 0
	// TODO: Extent this array with events such as BEFORE_WRITING_INPUTS, AFTER_WRITING_OUTPUTS or similar when we know where to tap in.

} BACNET_NATIVE_OBJECT_EVENT_TYPE;


/** Data sent to the event handlers of IO- modules **/
typedef struct bacnet_native_object_event_args
{
	struct bacnet_native_objects* native;
	tApplicationDeviceInterface* adi;
	tDeviceId adi_deviceId;
	uint32_t adi_taskId;

} BACNET_NATIVE_OBJECT_EVENT_ARGS;


/** Event-handler callback function implemented by the IO modules **/
typedef void(*bacnet_native_object_event) (BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* arg);


/** Contains data for a native object for a single terminal channel **/
typedef struct bacnet_native_object_ref
{
	bool Exists;
	BACNET_OBJECT_ID ObjectID;

} BACNET_NATIVE_OBJECT_REF;


/** Contains data for a IO terminal that may contain multiple channels / native objects **/
typedef struct bacnet_native_objects
{
	uint32_t id;
	bac_hash_handle hh;
	BACNET_NATIVE_OBJECT_REF ref[MAX_BACNET_NATIVE_OBJECT_REF_PER_TERMINAL];

	uint16_t TerminalTypePos;
	uint16_t TerminalType;
	tldkc_KbusInfo_TerminalInfo terminal_info;
	bacnet_native_object_event fn_process;

} BACNET_NATIVE_OBJECTS;



/** Reads out all IO modules from PLC and creates the native objects that represents them.
    Call this when PLC starts up and IO modules are ready.
*/
bool native_objects_init(void);


/** Updates all native objects according to the given event type.
    Call this at specific events in PLC cycle to process each native object.
@param EventType [in] Type of event to process (sent directly to the IO module handlers)
*/
void native_objects_process(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType);


/** Deletes all native objects and cleans up native objects.
    Call this when PLC is shut down or when IO modules have changed.
*/
void native_objects_cleanup(void);


/** Create a native objects terminal for the given PLC terminal
@param pTerminalInfo [in] Pointer to the terminal info
@param TerminalTypePos [in] Relative position of to terminal in the IO stack of the same type (example type:555, 5 = 5th card of the type 555)
@param TerminalType [in] Type of terminal (example 555)
@param fn_event [in] Callback function for events (called from 'native_objects_process')
*/
BACNET_NATIVE_OBJECTS* native_terminal_create(tldkc_KbusInfo_TerminalInfo* pTerminalInfo, uint16_t TerminalTypePos, uint16_t TerminalType, bacnet_native_object_event fn_event);


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
BACNET_NATIVE_OBJECT_REF* native_object_create(BACNET_NATIVE_OBJECTS* pNative, const char* strPrefix, BACNET_OBJECT_TYPE ObjectType, uint16_t Channel, const char* strSuffix);


/** Process a BACnet Binary Value for an input according to the new value and Reliability
@param pObjectID [in] Object ID of the BACnet object to alter that represents this input
@param NewValue [in] The new binary value coming from the physical IO- module input
@param Reliability [in] The current reliability status of the 'NewValue' parameter (use 'RELIABILITY_NO_FAULT_DETECTED' in case of no fault)
@param pInputPV [in/out] The actual value that should be used by the PLC program (Priority-Array and Out-Of-Service state taken into account)
@return true in case of success (pOutputPV is never altered in case of failure)
*/
bool native_object_process_input_bv(BACNET_OBJECT_ID* pObjectID, bool NewValue, BACNET_RELIABILITY Reliability, bool* pInputPV);


/** Process a BACnet Binary Value for an output according to the Reliability
@param pObjectID [in] Object ID of the BACnet object to alter that represents this output
@param NewValue [in] The binary value for this output coming from the PLC program
@param Reliability [in] The current reliability status of the output (use 'RELIABILITY_NO_FAULT_DETECTED' in case of no fault)
@param pOutputPV [in/out] The actual value that should be used by the physical IO module output (Priority-Array and Out-Of-Service state taken into account)
@return true in case of success (pOutputPV is never altered in case of failure)
*/
bool native_object_process_output_bv(BACNET_OBJECT_ID* pObjectID, bool NewValue, BACNET_RELIABILITY Reliability, bool* pOutputPV);
