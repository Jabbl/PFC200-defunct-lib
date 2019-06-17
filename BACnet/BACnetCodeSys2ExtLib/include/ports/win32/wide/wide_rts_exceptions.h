#ifndef D_WIDE_RTS_EXCEPTION_H
#define D_WIDE_RTS_EXCEPTION_H

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
/// \version <Revision>: $Rev: 4046 $
///
/// \brief short description of the file contents
///
/// \author ${user} $Author$ : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------

#define WIDE_RTSEXCPT_UNKNOWN               ((unsigned long)-1)
#define WIDE_RTSEXCPT_NOEXCEPTION           0x00000000
#define WIDE_RTSEXCPT_WARNING               0x00000001
#define WIDE_RTSEXCPT_INFO                  0x00000002

/* Global errors */
#define WIDE_RTSEXCPT_WATCHDOG              0x00000010  /* Software watchdog of IEC-task expired */
#define WIDE_RTSEXCPT_HARDWAREWATCHDOG         0x00000011  /* Hardware watchdog expired. Global software error */
#define WIDE_RTSEXCPT_BUS_ERROR             0x00000012  /* Fieldbus error occurred */
#define WIDE_RTSEXCPT_PROGRAMCHECKSUM       0x00000013  /* Checksum error after program download */
#define WIDE_RTSEXCPT_FIELDBUS_ERROR           0x00000014  /* Fieldbus error */
#define WIDE_RTSEXCPT_IOUPDATE_ERROR           0x00000015  /* IO-update error */
#define WIDE_RTSEXCPT_CYCLE_TIME_EXCEED        0x00000016  /* Cycle time exceed */
#define WIDE_RTSEXCPT_ONLCHANGE_PROGRAM_EXCEEDED 0x00000017   /* Online change program too large */
#define WIDE_RTSEXCPT_UNRESOLVED_EXTREFS       0x00000018  /* Unresolved external references */
#define WIDE_RTSEXCPT_DOWNLOAD_REJECTED        0x00000019  /* Download was rejected by custom adaption */
#define WIDE_RTSEXCPT_BOOTPROJECT_REJECTED_DUE_RETAIN_ERROR   0x0000001A  /* Boot project not loaded because retain variables could not be relocated */
#define WIDE_RTSEXCPT_LOADBOOTPROJECT_FAILED      0x0000001B  /* Boot project not loaded and deleted */
#define WIDE_RTSEXCPT_MEMORY_LOW               0x0000001C  /* System memory very low (for example, due to a memory leak) */
#define WIDE_RTSEXCPT_RETAIN_MEMORY_ERROR      0x0000001D  /* Retain memory corrupt or cannot be mapped */
#define WIDE_RTSEXCPT_BOOTPROJECT_CRASH        0x0000001E  /* Boot project that could be loaded but caused a crash later */
#define WIDE_RTSEXCPT_TARGETVISU_OUTOFMEMORY      0x0000001F  /* Not enough memory for target visu */
#define WIDE_RTSEXCPT_CONFIG_DOWNLOAD_OUTOFMEMORY 0x00000020  /* Not enough memory for config */
#define WIDE_RTSEXCPT_BOOTPROJECTTARGETMISMATCH   0x00000021  /* Target of the bootproject doesn't match the current target */
#define WIDE_RTSEXCPT_SCHEDULEERROR            0x00000022  /* Error at scheduling tasks */
#define WIDE_RTSEXCPT_FILE_CHECKSUM_ERR        0x00000023  /* Checksum of downloaded file does not match */
#define WIDE_RTSEXCPT_RETAIN_IDENTITY_MISMATCH 0x00000024  /* Retain identity does not match to current bootproject program identity */
#define WIDE_RTSEXCPT_IECTASKCREATE_ERROR      0x00000025  /* an IEC task could not be created */
#define WIDE_RTSEXCPT_TASKSTOP_TIMEOUT_EXCEEDED   0x00000026  /* an IEC task could not be stopped within timeout s_lMaxInterval */
#define WIDE_RTSEXCPT_OVERLOAD              0x00000027  /* PLC load higher than configured maximum load */
#define WIDE_RTSEXCPT_TOO_MANYUPDATEREGIONS    0x00000028  /* target visu: limit of array of update regions is reached */
#define WIDE_RTSEXCPT_TOO_MANYTVFUNCCALLS      0x00000029  /* target visu: limit of drawing calls per cycle is reached */

/* Exceptions of IEC-program */
#define WIDE_RTSEXCPT_ILLEGAL_INSTRUCTION      0x00000050  /* Illegal instruction */
#define WIDE_RTSEXCPT_ACCESS_VIOLATION         0x00000051  /* Access violation */
#define WIDE_RTSEXCPT_PRIV_INSTRUCTION         0x00000052  /* Privileged instruction */
#define WIDE_RTSEXCPT_IN_PAGE_ERROR            0x00000053  /* Page fault */
#define WIDE_RTSEXCPT_STACK_OVERFLOW           0x00000054  /* Stack overflow */
#define WIDE_RTSEXCPT_INVALID_DISPOSITION      0x00000055  /* Invalid disposition */
#define WIDE_RTSEXCPT_INVALID_HANDLE           0x00000056  /* Invalid handle */
#define WIDE_RTSEXCPT_GUARD_PAGE               0x00000057  /* Guard page */
#define WIDE_RTSEXCPT_DOUBLE_FAULT          0x00000058  /* Double fault */
#define WIDE_RTSEXCPT_INVALID_OPCODE           0x00000059  /* Double fault */

#define WIDE_RTSEXCPT_MISALIGNMENT          0x00000100  /* Datatype misalignment */
#define WIDE_RTSEXCPT_ARRAYBOUNDS           0x00000101  /* Array bounds exceeded */
#define WIDE_RTSEXCPT_DIVIDEBYZERO          0x00000102  /* Division by zero */
#define WIDE_RTSEXCPT_OVERFLOW              0x00000103  /* Overflow */
#define WIDE_RTSEXCPT_NONCONTINUABLE           0x00000104  /* Non continuable */

#define WIDE_RTSEXCPT_FPU_ERROR             0x00000150  /* FPU: Unspecified error */
#define WIDE_RTSEXCPT_FPU_DENORMAL_OPERAND     0x00000151  /* FPU: Denormal operand */
#define WIDE_RTSEXCPT_FPU_DIVIDEBYZERO         0x00000152  /* FPU: Division by zero */
#define WIDE_RTSEXCPT_FPU_INEXACT_RESULT       0x00000153  /* FPU: Inexact result */
#define WIDE_RTSEXCPT_FPU_INVALID_OPERATION    0x00000154  /* FPU: Invalid operation */
#define WIDE_RTSEXCPT_FPU_OVERFLOW          0x00000155  /* FPU: Overflow */
#define WIDE_RTSEXCPT_FPU_STACK_CHECK       0x00000156  /* FPU: Stack check */
#define WIDE_RTSEXCPT_FPU_UNDERFLOW            0x00000157  /* FPU: Underflow */

/* Custom exceptions */
#define WIDE_RTSEXCPT_CUSTOM                0x00010000


/*---- Return values ----*/

#define WIDE_EXCPT_UNHANDLED          0
#define WIDE_EXCPT_TASKCONTINUE       1
#define WIDE_EXCPT_TASKSUSPEND        2
#define WIDE_EXCPT_PLCEXIT            3
#define WIDE_EXCPT_PLCSTOP            4

#define WIDE_EXCPT_CUSTOM          0x4000

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------



#endif  // D_WIDE_RTS_EXCEPTION_H
