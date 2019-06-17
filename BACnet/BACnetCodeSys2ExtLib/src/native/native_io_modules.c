/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "native/native_io_modules.h"
#include "native/native_objects.h"
#include <dal/adi_application_interface.h>
#include "PT/common.h"

/** Local function prototypes */
static void native_io_modules_create_750_402(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_402(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_430(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_430(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_457(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_457(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_504(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_504(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_523(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_523(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_554(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_554(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_555(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_555(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);
static void native_io_modules_create_750_1506(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);
static void native_io_modules_update_750_1506(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args);


/** Called from native_objects.c to create the native objects for correct TerminalType of the given IO module
@param TerminalType [in] Type of terminal to create native objects for
@param RelPos [in] Relative position of to terminal in the IO stack of the same type (example type:555, 5 = 5th card of the type 555)
@param pTerminalInfo [in] Pointer to the terminal info
@return true if we recognized the IO module and were able to create native objects for it.
*/
bool native_io_modules_create(uint16_t TerminalType, uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// TODO: For digital modules, check the following data:
	// 1XXX XXXX XXXX XXXX
	// ^ Indicates digital module
	//      ^^^^  Number of channels
	//      8421
	//                  ^^  output or input
	//					QI
	//    ^ 16-channels

	// Try to create native objects with one of our known terminal types.
	// Return false if we don't know anything about this IO module.
	switch (TerminalType)
	{
	case 0x8401: native_io_modules_create_750_402(RelPos, pTerminalInfo); return true;
	case 0x8801: native_io_modules_create_750_430(RelPos, pTerminalInfo); return true;
	case 0x8402: native_io_modules_create_750_504(RelPos, pTerminalInfo); return true;
	case 0x8203: native_io_modules_create_750_523(RelPos, pTerminalInfo);  return true;
	case 457: native_io_modules_create_750_457(RelPos, pTerminalInfo); return true;
	case 554: native_io_modules_create_750_554(RelPos, pTerminalInfo); return true;
	case 555: native_io_modules_create_750_555(RelPos, pTerminalInfo); return true;
	case 0x880F: native_io_modules_create_750_1506(RelPos, pTerminalInfo); return true;
	default: return false;
	}
}


/*****************************************************************************/
/*** Implementation of the Wago 750-402 4-channel digital input IO- module ***/
/*****************************************************************************/
static void native_io_modules_create_750_402(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 4 inputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 402, native_io_modules_update_750_402);
	if (pNative)
	{
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 1, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 2, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 3, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 4, NULL);
	}
}

static void native_io_modules_update_750_402(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;

	// Read the processdata from the inputs
	uint8_t Data = 0;
	BACNET_RELIABILITY Reliability;
	if (args->adi->ReadBytes(args->adi_deviceId, args->adi_taskId, args->native->terminal_info.OffsetInput_bits, sizeof(Data), &Data) == 0)
		Reliability = RELIABILITY_NO_FAULT_DETECTED;
	else
		Reliability = RELIABILITY_MEMBER_FAULT;

	// TODO: plc_input_state contains the BOOL that should be given to CodeSys as the %IX value
	bool plc_input_state;
	native_object_process_input_bv(&args->native->ref[0].ObjectID, CHECK_BIT(Data, 0), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[1].ObjectID, CHECK_BIT(Data, 1), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[2].ObjectID, CHECK_BIT(Data, 2), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[3].ObjectID, CHECK_BIT(Data, 3), Reliability, &plc_input_state);
}


/*****************************************************************************/
/*** Implementation of the Wago 750-430 8-channel digital input IO- module ***/
/*****************************************************************************/
static void native_io_modules_create_750_430(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 8 inputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 430, native_io_modules_update_750_430);
	if (pNative)
	{
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 1, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 2, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 3, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 4, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 5, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 6, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 7, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 8, NULL);
	}
}

static void native_io_modules_update_750_430(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;

	// Read the processdata from the inputs
	uint8_t Data = 0;
	BACNET_RELIABILITY Reliability;
	if(args->adi->ReadBytes(args->adi_deviceId, args->adi_taskId, args->native->terminal_info.OffsetInput_bits, sizeof(Data), &Data) == 0)
		Reliability = RELIABILITY_NO_FAULT_DETECTED;
	else
		Reliability = RELIABILITY_MEMBER_FAULT;

	// TODO: plc_input_state contains the BOOL that should be given to CodeSys as the %IX value
	bool plc_input_state;
	native_object_process_input_bv(&args->native->ref[0].ObjectID, CHECK_BIT(Data, 0), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[1].ObjectID, CHECK_BIT(Data, 1), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[2].ObjectID, CHECK_BIT(Data, 2), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[3].ObjectID, CHECK_BIT(Data, 3), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[4].ObjectID, CHECK_BIT(Data, 4), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[5].ObjectID, CHECK_BIT(Data, 5), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[6].ObjectID, CHECK_BIT(Data, 6), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[7].ObjectID, CHECK_BIT(Data, 7), Reliability, &plc_input_state);
}


/**********************************************************************************/
/*** Implementation of the Wago 750-457 4-channel 0-10V analog input IO- module ***/
/**********************************************************************************/
static void native_io_modules_create_750_457(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 4 outputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 457, native_io_modules_update_750_457);
	if (pNative)
	{
		native_object_create(pNative, "AO", OBJECT_ANALOG_INPUT, 1, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_INPUT, 2, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_INPUT, 3, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_INPUT, 4, NULL);
	}
}

static void native_io_modules_update_750_457(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;
	(void)args;

	// TODO: Not programmed yet. How do you read from outputs anyway?? Don't think it's possible through 'adi'.
}


/******************************************************************************/
/*** Implementation of the Wago 750-504 4-channel digital output IO- module ***/
/******************************************************************************/
static void native_io_modules_create_750_504(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 4 outputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 504, native_io_modules_update_750_504);
	if (pNative)
	{
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 1, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 2, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 3, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 4, NULL);
	}
}

static void native_io_modules_update_750_504(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;
	(void)args;

	// TODO: Not programmed yet. How do you read from outputs anyway?? Don't think it's possible through 'adi'.
}


/*********************************************************************************************/
/*** Implementation of the Wago 750-523 1-channel potential free digital output IO- module ***/
/*********************************************************************************************/
static void native_io_modules_create_750_523(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for the output, as well as an additional native object for the little 'HAND' dip switch on the card to indicate output is overriden
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 523, native_io_modules_update_750_523);
	if (pNative)
	{
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 1, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_INPUT, 1, "ManualStatus");
	}
}

static void native_io_modules_update_750_523(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;

	// TODO: Output not programmed yet. How do you read from outputs anyway?? Don't think it's possible through 'adi'.
	BACNET_RELIABILITY Reliability;

	// Feedback from manual HAND switch located on the physical card into the native object
	uint8_t Data;
	if(args->adi->ReadBit(args->adi_deviceId, args->adi_taskId, args->native->terminal_info.OffsetInput_bits, &Data) == 0)
		Reliability = RELIABILITY_NO_FAULT_DETECTED;
	else
		Reliability = RELIABILITY_MEMBER_FAULT;
	native_object_process_input_bv(&args->native->ref[1].ObjectID, CHECK_BIT(Data, 0), Reliability, NULL);
}



/************************************************************************************/
/*** Implementation of the Wago 750-554 2-channel 4-20mA analog output IO- module ***/
/************************************************************************************/
static void native_io_modules_create_750_554(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 4 outputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 554, native_io_modules_update_750_554);
	if (pNative)
	{
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 1, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 2, NULL);
	}
}

static void native_io_modules_update_750_554(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;
	(void)args;

	// TODO: Not programmed yet. How do you read from outputs anyway?? Don't think it's possible through 'adi'.
}



/***********************************************************************************/
/*** Implementation of the Wago 750-555 4-channel 0-10v analog output IO- module ***/
/***********************************************************************************/
static void native_io_modules_create_750_555(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the 4 outputs this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 555, native_io_modules_update_750_555);
	if (pNative)
	{
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 1, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 2, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 3, NULL);
		native_object_create(pNative, "AO", OBJECT_ANALOG_OUTPUT, 4, NULL);
	}
}

static void native_io_modules_update_750_555(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;
	(void)args;

	// TODO: Not programmed yet. How do you read from outputs anyway?? Don't think it's possible through 'adi'.
}



/*********************************************************************************************************/
/*** Implementation of the Wago 750-1506 8-channel digital input + 8-channel digital output IO- module ***/
/*********************************************************************************************************/
static void native_io_modules_create_750_1506(uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo)
{
	// Create one native object for each of the terminal this terminal card has
	BACNET_NATIVE_OBJECTS* pNative = native_terminal_create(pTerminalInfo, RelPos, 1506, native_io_modules_update_750_1506);
	if (pNative)
	{
		// 8 inputs
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 1, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 2, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 3, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 4, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 5, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 6, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 7, NULL);
		native_object_create(pNative, "BI", OBJECT_BINARY_INPUT, 8, NULL);

		// 8 outputs
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 1, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 2, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 3, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 4, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 5, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 6, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 7, NULL);
		native_object_create(pNative, "BO", OBJECT_BINARY_OUTPUT, 8, NULL);
	}
}

static void native_io_modules_update_750_1506(BACNET_NATIVE_OBJECT_EVENT_TYPE EventType, BACNET_NATIVE_OBJECT_EVENT_ARGS* args)
{
	(void)EventType;

	// Read the processdata from the inputs
	uint8_t Data = 0;
	BACNET_RELIABILITY Reliability;
	if (args->adi->ReadBytes(args->adi_deviceId, args->adi_taskId, args->native->terminal_info.OffsetInput_bits, sizeof(Data), &Data) == 0)
		Reliability = RELIABILITY_NO_FAULT_DETECTED;
	else
		Reliability = RELIABILITY_MEMBER_FAULT;

	// TODO: plc_input_state contains the BOOL that should be given to CodeSys as the %IX value
	bool plc_input_state;
	native_object_process_input_bv(&args->native->ref[0].ObjectID, CHECK_BIT(Data, 0), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[1].ObjectID, CHECK_BIT(Data, 1), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[2].ObjectID, CHECK_BIT(Data, 2), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[3].ObjectID, CHECK_BIT(Data, 3), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[4].ObjectID, CHECK_BIT(Data, 4), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[5].ObjectID, CHECK_BIT(Data, 5), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[6].ObjectID, CHECK_BIT(Data, 6), Reliability, &plc_input_state);
	native_object_process_input_bv(&args->native->ref[7].ObjectID, CHECK_BIT(Data, 7), Reliability, &plc_input_state);
}
