//------------------------------------------------------------------------------
// Copyright (c) WAGO Kontakttechnik GmbH & Co. KG
//
// PROPRIETARY RIGHTS are involved in the subject matter of this material. All
// manufacturing, reproduction, use, and sales rights pertaining to this
// subject matter are governed by the license agreement. The recipient of this
// software implicitly accepts the terms of the license.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// \file $file_name$
///
/// \version <Revision>: $Rev: 4946 $
///
/// \brief short description of the file contents
///
/// \author Jan Sondhauss <jan.sondhauss@wago.com> : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

#ifndef LDKC_KBUS_INFORMATION_H_
#define LDKC_KBUS_INFORMATION_H_

#include <stdint.h>
#include <stddef.h>

#include <OsCommon.h>


// Silence warning C4214: nonstandard extension used: bit field types other than int
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4214)
#endif


enum KbusInfo {
   KbusInfo_Ok = 0,
   KbusInfo_Failed = -1,
};

enum KbusInfoProcessDataFormat
{
   KbusInfoProcessDataFormat_Default,
   KbusInfoProcessDataFormat_Alternative,
};

typedef struct ldkc_KbusInfo_Status
{
   u16 KbusBitCount;
   u16 TerminalCount;
   u16 ErrorCode;
   u16 ErrorArg;
   u16 ErrorPos;
   u16 BitCountAnalogInput;
   u16 BitCountAnalogOutput;
   u16 BitCountDigitalInput;
   u16 BitCountDigitalOutput;
}tldkc_KbusInfo_Status;


typedef struct ldkc_KbusInfo_TerminalInfo
{
   u16 OffsetInput_bits;
   u16 OffsetOutput_bits;
   u16 SizeInput_bits;
   u16 SizeOutput_bits;
   struct {
      u16 :8;
      u16 ChannelCount:5;
      u16 PiFormat:1;
      u16 :2;
   }AdditionalInfo;
}tldkc_KbusInfo_TerminalInfo;

typedef struct ldkc_KbusInfo_TerminalDiagnose
{
   u8 *Diagnose;
   u8 *TerminalNo;
   u8 *Channel;
   size_t Count;
}tldkc_KbusInfo_TerminalDiagnose;

i32 ldkc_KbusInfo_Create(void);

void ldkc_KbusInfo_Destroy(void);

i32 ldkc_KbusInfo_GetTerminalCount( u16 *count);

i32 ldkc_KbusInfo_GetTerminalInfo(size_t capacity, tldkc_KbusInfo_TerminalInfo *info, size_t *count);

i32 ldkc_KbusInfo_GetTerminalList(size_t capacity, u16 *list, size_t *count);

i32 ldkc_KbusInfo_GetTerminalDiagnose(tldkc_KbusInfo_TerminalDiagnose *diag);

void ldkc_KbusInfo_TerminalDiagnoseRelease(tldkc_KbusInfo_TerminalDiagnose *diag);

i32 ldkc_KbusInfo_GetStatus(tldkc_KbusInfo_Status *status);

i32 ldkc_KbusInfo_GetDigitalOffset(u16 *input, u16 *output);

i32 ldkc_KbusInfo_GetDigitalOffsetInput(u16 *offset);

i32 ldkc_KbusInfo_GetDigitalOffsetOutput(u16 *offset);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* LDKC_KBUS_INFORMATION_H_ */
