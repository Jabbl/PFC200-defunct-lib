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

#ifndef LDKC_KBUS_REGISTER_COMMUNICATION_H_
#define LDKC_KBUS_REGISTER_COMMUNICATION_H_

#include <stdint.h>
#include <stddef.h>

#include <OsCommon.h>

#define LDKC_KBUS_REGISTER_REQUEST_THREAD_PRIORITY (50U)

#define LDKC_KBUS_TERMINAL_COUNT_MAX (255U)
#define LDKC_KBUS_TERMINAL_LIST_TABLE (9U)

#define LDKC_KBUS_TERMINAL_ORDER_NUMBER_TABLE (0U)
#define LDKC_KBUS_TERMINAL_ORDER_NUMBER_REGISTER (28U)
#define LDKC_KBUS_TERMINAL_ORDER_NUMBER_LENGTH (3U)

typedef enum ldkc_KbusRegisterRequestState
{
   Request_Pending, Request_Ok, Request_Failed,
} tldkc_KbusRegisterRequestState;


typedef struct ldkc_KbusRegisterRequestData
{
   u16 Terminal;
   u16 Table;
   u16 Register;
   u16 Length;
}tldkc_KbusRegisterRequestData;

typedef struct ldkc_KbusRegisterRequest tldkc_KbusRegisterRequest;

typedef void (*fnKbusRegisterRequestComplete)(tldkc_KbusRegisterRequest const *request, void *userData);


void ldkc_KbusRegisterRequest_Destroy(tldkc_KbusRegisterRequest *request);

i32 ldkc_KbusRegisterRequest_GetState(tldkc_KbusRegisterRequest const *request);

u16 * ldkc_KbusRegisterRequest_GetBuffer(tldkc_KbusRegisterRequest const *request);

u16 ldkc_KbusRegisterRequest_GetResponseLength(tldkc_KbusRegisterRequest const *request);

const tldkc_KbusRegisterRequestData* ldkc_KbusRegisterRequest_GetRequestData(tldkc_KbusRegisterRequest const *request);

tldkc_KbusRegisterRequest* ldkc_KbusRegisterRequest_ReadAsync(tldkc_KbusRegisterRequestData const *requestData,
                                                         fnKbusRegisterRequestComplete callback,
                                                         void *userData,
                                                         u16 *buffer);


tldkc_KbusRegisterRequest* ldkc_KbusRegisterRequest_WriteAsync(tldkc_KbusRegisterRequestData const *requestData,
                                                          fnKbusRegisterRequestComplete callback,
                                                          void *userData,
                                                          u16 *buffer);

i32 ldkc_KbusRegisterRequest_Read(tldkc_KbusRegisterRequestData const *requestData,
                                       u16 *buffer,
                                       u16 *length);

i32 ldkc_KbusRegisterRequest_Write(tldkc_KbusRegisterRequestData const *requestData,
                                       u16 *buffer);


void ldkc_KbusRegisterRequest_CreateWorkerThread(void);

void ldkc_KbusRegisterRequest_DestroyWorkerThread(void);

#endif /* LDKC_KBUS_REGISTER_COMMUNICATION_H_ */
