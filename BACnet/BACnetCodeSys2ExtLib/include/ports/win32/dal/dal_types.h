//------------------------------------------------------------------------------
/// Copyright (c) WAGO Kontakttechnik GmbH & Co. KG
///
/// PROPRIETARY RIGHTS are involved in the subject matter of this material. All
/// manufacturing, reproduction, use, and sales rights pertaining to this
/// subject matter are governed by the license agreement. The recipient of this
/// software implicitly accepts the terms of the license.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// \file dal_types.h
///
/// \version <Revision>: $Rev: 7698 $
///
/// \brief This file contains the common type definitions of ADI, DAL and SDI.
///
/// \author $Author$ : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------
#ifndef _DAL_TYPES_H_
#define _DAL_TYPES_H_

#include "dal_limits.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* define error code   */
#define DAL_FAILURE                           -1 /*< */
#define DAL_SUCCESS                            0 /*< */
#define DAL_NOTUSED                            1 /*< Indicates a function is not implemented by the device */


/*
 * define for gcc's warning about unused results.
 */

// Disabled by A.Gantvorg due to trunk compile errors
//TODO: reenable after the errors in plclinuxrt have been fixed

/*
#if   (__GNUC__ == 4 && __GNUC_MINOR__ == 4 ) // <- this version is bugged as a cast to void doesn't prevent the warning about unused result..
#define DAL_GNUC_WARN_UNUSED_RESULT
#elif    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define DAL_GNUC_WARN_UNUSED_RESULT      \
  __attribute__((warn_unused_result))
#else
#define DAL_GNUC_WARN_UNUSED_RESULT
#endif */ /* __GNUC__ */

#define DAL_GNUC_WARN_UNUSED_RESULT // TODO: remove this when the above macro has been re-enabled

typedef int32_t tDeviceId;

//typedef enum enDeviceState
//{
//   DeviceState_Closed,
//   DeviceState_Opened,
//   DeviceState_Ready,
//   DeviceState_Running,
//   DeviceState_Error,
//}tDeviceState;

//typedef struct stCommonEvent_DeviceStateChanged
//{
//   tDeviceState  OldState;
//   tDeviceState  NewState;
//}tCommonEvent_DeviceStateChanged;

typedef enum enCommonEvent
{
   CommonEvent_BASE = 0,
   CommonEvent_WatchdogTriggered,
   CommonEvent_IoSizeChanged,
   CommonEvent_TOP,
}tCommonEvent;

typedef struct stCommonEvent_WatchdogTriggered
{
   uint32_t Count;
}tCommonEvent_WatchdogTriggered;

typedef struct stCommonEvent_IoSizeChanged
{
   size_t OldInputSize;
   size_t OldOutputSize;

   size_t NewInputSize;
   size_t NewOutputSize;
}tCommonEvent_IoSizeChanged;

typedef uint32_t tError;

typedef enum enApplicationState
{
   ApplicationState_BASE = 0,       //!< ApplicationState_BASE
   ApplicationState_Running,        //!< ApplicationState_Running
   ApplicationState_Stopped,        //!< ApplicationState_Stopped
   ApplicationState_Unconfigured,   //!< ApplicationState_Unconfigured
   ApplicationState_TOP,            //!< ApplicationState_TOP
}tApplicationState;

typedef struct stApplicationStateChangedEvent
{
   tApplicationState State;
}tApplicationStateChangedEvent;



// tDeviceInfo objects are created dynamically by adi's GetDeviceList() function from
// tDeviceInfoInternal objects. This way we don't have to expose internal data to the user.
typedef struct stDeviceInfo
{
   tDeviceId DeviceId;
   const char* DeviceName;
}tDeviceInfo;

/**
 * This enum lists the state a bus can be in. The values correspond
 * to the BUSSTATE_* defines from codesys (RtsIODrvItf.h).
 */
typedef enum enBusState
{
  BusState_NotEnabled = 0,         //!< BusState_NotEnabled
  BusState_BusOk = 1,              //!< BusState_BusOk The bus is up and running
  BusState_BusFault = 2,           //!< BusState_BusFault
  BusState_BusNotCommunicating = 3,//!< BusState_BusNotCommunicating
  BusState_BusStopped = 4,         //!< BusState_BusStopped
}tBusState;

/**
 * The enum lists the states of an diagnose request. The values correspond
 * to the values defined by codesys (NDSTATE_*) in RtsIODrvItf.h
 */
typedef enum enDiagnoseState
{
   DiagnoseState_InvalidInputParameter = ((short)(-1)),//!< DiagnoseState_InvalidInputParameter
   DiagnoseState_NotEnabled = 0,                       //!< DiagnoseState_NotEnabled
   DiagnoseState_GetDiagInfo = 1,                      //!< DiagnoseState_GetDiagInfo
   DiagnoseState_DiagInfoAvailable = 2,                //!< DiagnoseState_DiagInfoAvailable
   DiagnoseState_DiagInfoNotAvailable = 3              //!< DiagnoseState_DiagInfoNotAvailable
}tDiagnoseState;

/**
 * This enum list the flags for the DeviceState's extended info.
 */
typedef enum enBusMemberState
{
   BusMemberState_Configured= 0x01,//!< BusMemberState_Configured
   BusMemberState_Alive = 0x02,    //!< BusMemberState_Alive
   BusMemberState_Faulted = 0x04   //!< BusMemberState_Faulted
}tBusMemberState;


#endif
