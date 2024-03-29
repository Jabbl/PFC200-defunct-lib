#ifndef D_WIDE_EVENTS_H
#define D_WIDE_EVENTS_H

//------------------------------------------------------------------------------
/// Copyright (c) WAGO Kontakttechnik GmbH & Co. KG
///
/// PROPRIETARY RIGHTS are involved in the subject matter of this material. All
/// manufacturing, reproduction, use, and sales rights pertaining to this
/// subject matter are governed by the license agreement. The recipient of this
/// software implicitly accepts the terms of the license.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// \file ${file_name}
///
/// \version <Revision>:
///
/// \brief short description of the file contents
///
/// \author ${user} : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include <stdint.h>

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

typedef enum enWideRtsEvent
{
   WideRtsEvent_ALL,

   /* General events */
   WideRtsEvent_START,
   WideRtsEvent_STOP,
   WideRtsEvent_BEFORE_RESET,
   WideRtsEvent_AFTER_RESET,
   WideRtsEvent_SHUTDOWN,

   /* Exceptions generated by runtime */
   WideRtsEvent_EXCPT_CYCLETIME_OVERFLOW,        /* Sycle time overflow */
   WideRtsEvent_EXCPT_WATCHDOG,               /* Software watchdog of IEC-task expired */
   WideRtsEvent_EXCPT_HARDWARE_WATCHDOG,         /* Hardware watchdog expired. Global software error */
   WideRtsEvent_EXCPT_FIELDBUS,               /* Fieldbus error occurred */
   WideRtsEvent_EXCPT_IOUPDATE,               /* IO-update error */

   /* Exceptions generated by system */
   WideRtsEvent_EXCPT_ILLEGAL_INSTRUCTION,    /* Illegal instruction */
   WideRtsEvent_EXCPT_ACCESS_VIOLATION,       /* Access violation */
   WideRtsEvent_EXCPT_PRIV_INSTRUCTION,       /* Privileged instruction */
   WideRtsEvent_EXCPT_IN_PAGE_ERROR,          /* Page fault */
   WideRtsEvent_EXCPT_STACK_OVERFLOW,            /* Stack overflow */
   WideRtsEvent_EXCPT_MISALIGNMENT,           /* Datatype misalignment */
   WideRtsEvent_EXCPT_ARRAYBOUNDS,               /* Array bounds exceeded */
   WideRtsEvent_EXCPT_DIVIDEBYZERO,           /* Division by zero */
   WideRtsEvent_EXCPT_OVERFLOW,               /* Overflow */
   WideRtsEvent_EXCPT_NONCONTINUABLE,            /* Non continuable */

   WideRtsEvent_EXCPT_NO_FPU_AVAILABLE,       /* FPU: No FPU available */
   WideRtsEvent_EXCPT_FPU_ERROR,              /* FPU: Unspecified error */
   WideRtsEvent_EXCPT_FPU_DENORMAL_OPERAND,      /* FPU: Denormal operand */
   WideRtsEvent_EXCPT_FPU_DIVIDEBYZERO,       /* FPU: Division by zero */
   WideRtsEvent_EXCPT_FPU_INVALID_OPERATION,     /* FPU: Invalid operation */
   WideRtsEvent_EXCPT_FPU_OVERFLOW,           /* FPU: Overflow */
   WideRtsEvent_EXCPT_FPU_STACK_CHECK,        /* FPU: Stack check */

   /* IO events */
   WideRtsEvent_AFTER_READING_INPUTS,
   WideRtsEvent_BEFORE_WRITING_OUTPUTS,

   /* Miscellaneous events */
   WideRtsEvent_TIMER,         /* Schedule tick (timer interrupt), is active only if PLC is in run */
   WideRtsEvent_DEBUG_LOOP,    /* Debug loop at breakpoint */
   WideRtsEvent_SCHEDULE,         /* Schedule tick (timer interrupt), is called always */

   WideRtsEvent_ONLINE_CHANGE, /* Is called after CodeInit() at Online-Change */
   WideRtsEvent_BEFORE_DOWNLOAD,  /* Is called after CodeInit() at Online-Change */

   WideRtsEvent_TASKCODE_NOT_CALLED,
   WideRtsEvent_SYNC_RECEIVED,
   WideRtsEvent_BEFORE_READING_INPUTS,
   WideRtsEvent_AFTER_WRITING_OUTPUTS,
   WideRtsEvent_SYSTEM_CRASH,
   WideRtsEvent_POWERFAIL,
   WideRtsEvent_CANMESSAGE_RECEIVED,
   WideRtsEvent_EXCPT_PLC_OVERLOAD,

   WideRtsEvent_TARGETVISU_WINDOW_ACTIVATED,
   WideRtsEvent_TARGETVISU_WINDOW_DEACTIVATED,

   /* Online services */
   WideRtsEvent_ONLINE_SERVICES_BEGIN = 500,
   WideRtsEvent_LOGIN,
   WideRtsEvent_CUSTOM_SERVICES,

   /* Interrupts */
   WideRtsEvent_INT_0 = 1000,
   WideRtsEvent_INT_1,
   WideRtsEvent_INT_2,
   WideRtsEvent_INT_3,
   WideRtsEvent_INT_4,
   WideRtsEvent_INT_5,
   WideRtsEvent_INT_6,
   WideRtsEvent_INT_7,
   WideRtsEvent_INT_8,
   WideRtsEvent_INT_9,
   WideRtsEvent_INT_10,
   WideRtsEvent_INT_11,
   WideRtsEvent_INT_12,
   WideRtsEvent_INT_13,
   WideRtsEvent_INT_14,
   WideRtsEvent_INT_15,
   WideRtsEvent_INT_255 = 1255,

   WideRtsEvent_IIO_BASE = 1300,  /*for osadl IIO Interface*/
   WideRtsEvent_IIO_1 = 1301,
   WideRtsEvent_IIO_2,
   WideRtsEvent_IIO_3,
   WideRtsEvent_IIO_4,
   WideRtsEvent_IIO_5,
   WideRtsEvent_IIO_6,
   WideRtsEvent_IIO_7,
   WideRtsEvent_IIO_8,
   WideRtsEvent_IIO_9,
   WideRtsEvent_IIO_MAX = 1350,

   WideRtsEvent_KEYBOARD = 1400, /* only on Windows CE, not guaranteed to work by Microsoft and 3S */

   WideRtsEvent_CUSTOM_BEGIN = 1500,
   WideRtsEvent_CUSTOM_END = 2000,

   WideRtsEvent_MAX_RTS
} tWideRtsEvent;

typedef enum enWideRtsEventFilter
{
   WideRtsEventFilter_NONE          = 0x000000000,
   WideRtsEventFilter_ONLINE_SERVICES  = 0x000000001,
   WideRtsEventFilter_INFOS         = 0x000000002,
   WideRtsEventFilter_WARNINGS         = 0x000000004,
   WideRtsEventFilter_ERRORS        = 0x000000008,
   WideRtsEventFilter_EXCEPTIONS    = 0x000000010,
   WideRtsEventFilter_INTERRUPTS    = 0x000000020,
   WideRtsEventFilter_IO            = 0x000000040
} tWideRtsEventFilter;

typedef enum enWideEventSource
{
   WideRtsEventSource_UNSPECIFIED,
   WideRtsEventSource_SYSTEM,
   WideRtsEventSource_RUNTIME,
   WideRtsEventSource_IECPROGRAM,
   WideRtsEventSource_IECTASK
} tWideRtsEventSource;

//------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local variables
//------------------------------------------------------------------------------


#endif  // D_Wide_api_H
