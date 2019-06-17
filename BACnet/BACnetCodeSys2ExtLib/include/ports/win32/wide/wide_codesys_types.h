#ifndef D_WIDE_CODESYS_TYPES_H
#define D_WIDE_CODESYS_TYPES_H

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
/// \brief This header defines all types needed to develop a WIDE. Most
///        typedefs redefine existing codesys types.
///
/// \author ${user} : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#define _need_timespec
#include <time.h>


#include <dal/adi_application_interface.h>

#include "wide_events.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------

#define WDRV_MAX_DRIVERS 1
#define WDRV_MAX_DEVICES 10
#define WTASK_DOWNLOAD_NAME_LEN 32 //!< As defined by the codesys rts.

/* codesys defines taken from RtsGlb.h */
/* <RtsGlb.h> */
#define RTS_RESET_WARM        0
#define RTS_RESET_COLD        1
#define RTS_RESET_HARD        2

/* Controller Status definitions */
#define RTS_VOID              ((unsigned char)-1)
#define RTS_RUN                  0
#define RTS_STOP_SRV             1
#define RTS_STOP_BP              2
#define RTS_RUN_STEP_IN          3
#define RTS_RUN_STEP_OVER        4
#define RTS_RUN_WATCHDOG         5
#define RTS_STOP_WATCHDOG        6
#define RTS_STOP_ERROR           7
#define RTS_SINGLE_CYCLE         8
#define RTS_STOP_BP_SWITCH       9
#define RTS_MAX_STATUS           10
/* </RtsGlb.h> */



#define WIDE_LZS_TEXT_SIZE   800
#define WIDE_LZS_MAX_TEXT_SIZE  ((WIDE_LZS_TEXT_SIZE>>2)<<2)

/* common config load error */
#define WIDE_CCERR_TYPE_LOADERROR    0
#define WIDE_CCERR_TYPE_UNDEFINED    (char)(-1)

/* <RtsSys.h> */
#define WIDE_PORTID_INVALID  (~0U)
#define WIDE_TASKID_INVALID  ((unsigned long)-1)
#define WIDE_IECTASK_INVALID ((unsigned short)-1)
#define WIDE_SEM_INVALID     ((unsigned long)-1)
#define WIDE_EVENT_INVALID   ((unsigned long)-1)
#define WIDE_TIMER_INVALID   ((unsigned long)-1)
#define WIDE_SYS_MAXTASKNAME    80
/* </RtsSys.h> */

#define WIDE_COMM_TASK_PRIORITY 0x41

/* IEC Types as defined by codesys */
/**
 * \addtogroup IEC Types
 */
#define BOOL char
#define BYTE unsigned char
#define USINT unsigned char
#define INT short
#define UINT unsigned short
#define WORD unsigned short
#define DINT long
#define UDINT unsigned long
#define DWORD unsigned long
#define REAL float
#define LREAL double

#ifndef FALSE
# define FALSE  0
#endif
#ifndef TRUE
  #define TRUE  1
#endif

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

typedef struct stWideCCLoadError
{
    uint32_t LastError; /*contains the error code of the last error*/
    uint32_t AddInfo1; /*According to ulLastError, the meaning changes.*/
    uint32_t AddInfo2; /*According to ulLastError, the meaning changes.*/
    char LastErrorText[32]; /*A possibility to make debugging easier.*/
}tWideCCLoadError;

typedef struct stWideExtRef
{
   char  szName[32];
   void  (*pFunction)(void);
}tWideExtRef;

typedef struct stWideProjectInfo
{
   unsigned long  dwDate         ;
   char*       pszProject     ;
   char*       pszTitle    ;
   char*       pszVersion     ;
   char*       pszAuthor      ;
   char*       pszDescription ;
}tWideProjectInfo;

typedef struct stWideRtsLastError
{
   uint32_t error;
   uint32_t timeStamp ;
   uint32_t parameter ;
   char text[WIDE_LZS_MAX_TEXT_SIZE];
   uint32_t ulTaskId ;
} tWideRtsLastError;

#define CC_COMM_CFG_NAME   "CommConf"
typedef struct stWideCCHeader
{
    char szTag[10]; /*Contains the zero terminated string "CommConf"*/
    unsigned char cByteOrder; /* The file data is in intel format ('I')  or motorola format ('M')*/
    unsigned long ulSize; /* Size of the following data */
    unsigned long lVersion; /*Version number of the file*/
}tWideCCHeader;

/*The 'help-structures' (channel- and parameterdata):*/
/*keep packmode independent from project-settings in visual studio.*/
/*All IOdrivers rely on this fact.*/
typedef struct stWideCCParameter
{
    unsigned long    ulParameterId;/*  Id of the parameter given in the configuration file (*.cfg)*/
    unsigned short      usParameterNumber;/* Number of the parameter in the module*/
    unsigned char    byReadOnly;/*     1=TRUE, 0=FALSE*/
    unsigned short      usParameterType;/*      Type of the parameter (coded as CoDeSys "TypeClass")*/
    unsigned long    ulSize;/*         Size of the parameter in bytes*/
    unsigned char     byValue[1];/*       Memory representation of the parameter value*/
}tWideCCParameter;

typedef struct stWideCCChanel
{
    unsigned char ucEntryTag;/*  'C' = Channel*/
    signed long      ulChannelId;/* Id of the channel given in the configuration file*/
    unsigned short   usChannelNumber;/*   Number of the channel in the parent module*/
    unsigned long    ulRefId;/*  Direction of the channel (1=input, 2=output,
                      3=input and output)*/
    unsigned short      usChannelType;/*     Type of the channel (coded as CoDeSys "TypeClass")*/
    unsigned long    ulBitOffset;/*    Offset of the channel in in-/output area*/
    unsigned short      usParameterCount;/*  Number of parameters*/
    tWideCCParameter** ppccpParams; /*<PARAMETER[1..usParameterCount]> pointer to an array of pointers to CCParam-structures.*/
}tWideCCChanel;



typedef struct stWideCCModule
{
    unsigned char ucEntryTag;/*     'M' = Module*/
    unsigned long ulModuleId;/*     Id of the module given in the configuration file (*.cfg)*/
    signed short  sModuleNumber;/*  Number of the module in the parent module (-1 if root)*/
    unsigned short   usModuleTag;/*    Describes the kind of the module
    (0=3S-Module, 1=DP-Master, 2=DP-Slave, 3=CAN-Master, 4=CAN-Slave, 5=DP-SingleSlave)*/
    unsigned char byDeviceDriver;/* The module needs a device driver (0=FALSE, 1=TRUE)*/
    unsigned long ulNodeId; /*      NodeId of the module*/
    unsigned char byDefinedWithStruct;/*  The module was defined with a structure (0=FALSE, 1=TRUE)*/
    unsigned long ulBitOffsetInput;/*  Offset of the modules input area */
    unsigned long ulBitSizeInput;/* Size of the modules input area in bit*/
    unsigned long ulBitOffsetOutput;/*Offset of the modules output area*/
    unsigned long ulBitSizeOutput;/*  Size of the modules output area in bit*/
    unsigned long ulRefIdCommonDiag;/*RefId of the modules common diagnosis area*/
    unsigned long ulBitOffsetCommonDiag;/*Offset of the modules common diagnosis area*/
    unsigned long ulBitSizeDiag;/*     Size of the modules diagnosis area in bit*/
    unsigned short   usParameterCount;/*  Number of parameters*/
    tWideCCParameter**       ppccpModuleParams;/* <PARAMETER[0..usParameterCount]> a pointer to an array of pointers to CCModuleParam-structures.(Definition above)*/
    unsigned long ulSizeOfSpecificData; /*Size in bytes of the module specific data*/
    void* pModuleData; /*<MODULE_SPECIFIC_DATA> Here the data, according to usModuleTag is located:
                        pModuleData is possible to be a pointer to PBSlave,CANSlave,PBMaster,PBSlave,PBSingleSlave(exotic, used by Elau),
                        see definitions below.*/
    unsigned short   usChannelCount;/*    Number of configured channels*/
    unsigned short   usModuleCount;/*     Number of configured modules */

    /*Here the Channels and Modules of this Module in the configured order are located!
    (DP-Slaves are ordered by the stationnumber!)
    This means, its possible a CCModule structure is inserted here.*/
    tWideCCChanel**       ppcccChannels; /*(Definition above)*/
    struct stWideCCModule** ppccmSubModules;
}tWideCCModule;


typedef struct stWideTaskDownloadFormat
{
   unsigned long ulFlags;
   unsigned long ulPriority;
   long lInterval;
   long lWatchDogTime;
   long lWatchDogSensitivity;
   unsigned short usEventRefid;
   unsigned short usEventSize;
   unsigned long ulEventOffset;
   unsigned long ulEventId;
   unsigned long ulPOUIndex;
   char cName[WTASK_DOWNLOAD_NAME_LEN];
} tWideTaskDownloadFormat;

typedef struct stWideTaskLoggingEntry
{
   unsigned long ulTime;
   long bActive;
} tWideTaskLoggingEntry;

typedef struct stWideTaskLogging
{
   unsigned long ulEntries;
   int iAct;
   unsigned long ulCS;
   tWideTaskLoggingEntry *pList;
} tWideTaskLogging;


typedef struct stWideIoDescEntry
{
   unsigned long ulOffset     ;
   unsigned long ulSize    ;
} tWideIoDescEntry;


// <RtsSys.h>
typedef struct stWideSysTaskInfo
{
   unsigned long  ulHandle;
   unsigned long  ulId;
   unsigned long  ulSem;
   unsigned short usIecTaskIndex;
   char          szName[WIDE_SYS_MAXTASKNAME];
   unsigned long  ulState;    /* see task state definitions above */
} tWideSysTaskInfo;

typedef struct stWideSysLinuxTaskInfo
{
   tWideSysTaskInfo sysInfo;
   int bIECTask;
   unsigned long ulCycle;
   int iPriority;
   int isRT;
#ifdef LINUX_PREEMPT_RT
   struct itimerspec timer;
   struct timespec wakeup_latency;
#endif
   void *task_arg; //!< Holds the pointer to the task description.
} tWideSysLinuxTaskInfo;


typedef struct stTaskRtInfo
{
   unsigned long   ulCount       ;
   unsigned long   ulCycleTime      ;
   unsigned long   ulCycleTimeMin   ;
   unsigned long   ulCycleTimeMax   ;
   unsigned long   ulCycleTimeAcc   ;
   unsigned short  uStatus       ;
   unsigned short  uMode         ;
} tTaskRtInfo;

typedef struct stWideTaskDescription
{
   unsigned long  ulTaskId;
   tWideTaskDownloadFormat TaskConf;
   unsigned long  ulInputEntries;
   unsigned long  ulOutputEntries;
   tWideIoDescEntry   *pInputs;
   tWideIoDescEntry   *pOutputs;
   void        *pfTask;
   tTaskRtInfo    rtInfo;
   long  bEventFlag;
   long  bActive;
   long  bDelete;
   long  bWatchdog;
   long  bVisuTask;
   long  bSuspended;
   long  bToSchedule;
   long  bSchedActivated;
   long  bDebug;
   int      bStopEvtGenerated;
   unsigned long ulSchedPrio;
   tWideTaskLogging *pLog;

   unsigned long  ulStartTime;
   unsigned long  ulWdgTime;
   unsigned long  ulWatchdogInCycle;
   /* for realtime scheduler */
    unsigned long bChecked;
   unsigned long  bCheckIecCycle;
   unsigned long  bCreated;
   unsigned long  bWait;
   unsigned long  ulOverrunCount;
   unsigned long  ulClockTicks;
   unsigned long  ulClockTicksRes;
   unsigned long  ulClockTicksWdg;
   unsigned long  ulEvent;

   /*
   for external event tasks: "buffering interrupts"
   a counter is maintained for such a task which is e.g. incremented
   by an interrupt handler and decremented by the external event task
   */
   unsigned long  bIsBufferedExternalEventTask;
   unsigned long  ulUnhandledEvents;   /* the event counter */
   unsigned long  ulCSEventCounter; /* restricts access to the event counter */

   long bCycleStop;
   unsigned long ulException;

   /* 0: Device unused */
   /* 1: Device used, ok */
   /* 2: Device used, error */
   int abUsedDevInputs[WDRV_MAX_DRIVERS][WDRV_MAX_DEVICES]; /* Liste der benutzten Dev. */

   unsigned long   ulRegisteredInputEntries;
   unsigned long   ulRegisteredOutputEntries;
   tWideIoDescEntry    *pRegisteredInputs;
   tWideIoDescEntry    *pRegisteredOutputs;
} tWideTaskDescription;


typedef struct COMSettings
{
   short       sPort       ; /* COM1 = 1, COM2 = 2, ... */
   unsigned long  ulBaudRate     ; /* CST_BR_4800, CST_BR_9600, CST_BR_19200, CST_BR_38400, CST_BR_57600, CST_BR_115200 */
   unsigned char  byStopBits     ; /* CST_ONESTOPBIT, CST_ONE5STOPBITS, CST_TWOSTOPBITS */
   unsigned char  byParity    ; /* CST_NOPARITY, CST_ODDPARITY, CST_EVENPARITY */
   unsigned long  ulTimeout      ;
   unsigned long  ulBufferSize   ;
   unsigned long  ulSleep        ;
} tWideCOMSettings;


typedef struct WideComSettingsEx
{
  short     sSize;       /* Sizeof this structure, in bytes */
  short     sPort;       /* COM1 = 1, COM2 = 2, ... */
  unsigned long ulBaudRate;    /* CST_BR_4800, CST_BR_9600, CST_BR_19200, CST_BR_38400, CST_BR_57600, CST_BR_115200 */
  unsigned char byStopBits;    /* CST_ONESTOPBIT, CST_ONE5STOPBITS, CST_TWOSTOPBITS */
  unsigned char byParity;    /* CST_NOPARITY, CST_ODDPARITY, CST_EVENPARITY, if number of databits/byte should be changed, use high nibble of parity. If 0 or invalid, 8 databits will be used.*/
  unsigned long ulTimeout;    
  unsigned long ulBufferSize; 
  unsigned long ulSleep;
  /* New: */
  char cByteSize;         /* Number of bits/byte, 4-8     BYTE*/
  char fOutxCtsFlow;        /* CTS handshaking on output    BOOL*/
  char fDtrControl;       /* DTR Flow control         BYTE*/
  char fDsrSensitivity;     /* DSR Sensitivity          BOOL*/
  char fRtsControl;       /* Rts Flow control         BYTE*/
  char fOutxDsrFlow;        /* DSR handshaking on output    BOOL*/
}tWideCOMSettingsEx;


//------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local variables
//------------------------------------------------------------------------------


#endif  // D_WIDE_CODESYS_TYPES_H
