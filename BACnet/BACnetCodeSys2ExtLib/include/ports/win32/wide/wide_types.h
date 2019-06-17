#ifndef D_WIDE_TYPES_H
#define D_WIDE_TYPES_H

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

#include <dal/adi_application_interface.h>

#include "wide_events.h"
#include "wide_codesys_types.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

/* copy from RtsTypes.h */
typedef enum tagWideTypeClass
{
  WIDE_TYPE_BOOL,
  WIDE_TYPE_INT,
  WIDE_TYPE_BYTE,
  WIDE_TYPE_WORD,
  WIDE_TYPE_DINT,
  WIDE_TYPE_DWORD,
  WIDE_TYPE_REAL,
  WIDE_TYPE_TIME,
  WIDE_TYPE_STRING,
  WIDE_TYPE_ARRAY,
  WIDE_TYPE_ENUM,
  WIDE_TYPE_USERDEF,
  WIDE_TYPE_BITORBYTE,
  WIDE_TYPE_POINTER,
  WIDE_TYPE_SINT,
  WIDE_TYPE_USINT,
  WIDE_TYPE_UINT,
  WIDE_TYPE_UDINT,
  WIDE_TYPE_DATE,
  WIDE_TYPE_TOD,
  WIDE_TYPE_DT,
  WIDE_TYPE_VOID,
  WIDE_TYPE_LREAL,
  WIDE_TYPE_REF,
  WIDE_TYPE_SUBRANGE, /* this class is only used for load and save
              in all other cases a subrange type behaves like the basetype! */
  WIDE_TYPE_LBITORBYTE,
  WIDE_TYPE_LINT,
  WIDE_TYPE_ULINT,
  WIDE_TYPE_LWORD,
  WIDE_TYPE_NONE,
  WIDE_TYPE_BIT,
  WIDE_MAXTYPES
} WideTypeClass;

typedef enum enWideErrorCodes
{
   WIDE_SUCCESS = DAL_SUCCESS,
   WIDE_NOTUSED = DAL_NOTUSED,
   WIDE_FAILURE = DAL_FAILURE,
}tWideErrorCodes;

typedef struct stWideDeviceInfo
{
   uint32_t DeviceNr;
   tDeviceId DeviceId;
   size_t   OffsetInput;
   size_t   OffsetOutput;
   size_t   MaxSizeInput;
   size_t   MaxSizeOutput;
}tWideDeviceInfo;


typedef union
{
   void* ConfigData;
   tWideCCModule *ModuleParameter;
}tConfigParameter;

/**
 * The tWideInterface is the WIDE equivalent of the codesys DevItf.
 */
typedef struct stWideInterface
{
	/**
	 * Is called by the runtime to collect the IEC functions implemented
   * by the library.
	 * @return
	 */
	tWideExtRef *(*GetExternalTextReferenceTable)(void);

	/**
	 * This function is called to signal that the library is about to get unloaded.
	 * All acquired resources should get freed here.
	 * @return WIDE_SUCCESS.
	 */
	int32_t (*Close)(void);

  
  /* Functions from the codesys DevItf */
  uint32_t (*ProcessHook)(uint32_t hook,
                  uint32_t additionalInfo);
  int32_t (*ConfigureBegin)(uint32_t deviceNr);
  int32_t (*ConfigureEnd)(uint32_t deviceNr);
  int32_t (*ConfigureIoNet)(uint32_t deviceNr,
                    tWideCCModule* pccm,
                    uint32_t param);
  int32_t (*ConfigureDevice)(uint32_t deviceNr,
                    void *configData);
  int32_t (*ConfigureSubdevice)(uint32_t deviceNr,
                      uint32_t subdeviceNr,
                      void *configData);

  /**
   * Corresponds to
   * @param deviceNr
   * @param taskId
   * @return
   */
  int32_t (*ReadBegin)(uint32_t deviceNr, uint32_t taskId);

  /**
   *
   * @param deviceNr
   * @param taskId
   * @return
   */
  int32_t (*ReadEnd)(uint32_t deviceNr, uint32_t taskId);

  /**
   *
   * @param deviceNr
   * @param taskId
   * @return
   */
  int32_t (*WriteBegin)(uint32_t deviceNr, uint32_t taskId);

  /**
   *
   * @param deviceNr
   * @param taskId
   * @return
   */
  int32_t (*WriteEnd)(uint32_t deviceNr, uint32_t taskId);


  /**
   * Special function to get the state of the start/stop switch.
   * This one should only be implemented by the lib reading the physical SSS.
   * @param run Set to TRUE if running, FALSE otherwise.
   * @return Return 1.
   */
  int32_t (*StartStopSwitch)(int32_t *run);


  /**
   * Gets the name of the SDI device, the extension is associated with.
   * @return The device name if associated with a SDI device.
   *         In case the WIDE is not associated with any device return an
   *         empty string ("") otherwise (or set this func to NULL).
   */
  const char* (*GetDeviceName)(void);

   /**
    * This function is called by the IO-Driver to tell
    * the WIDE what its codesys device number and its DAL deviceId are.
    * @param info The dal device Id.
    * @return WIDE_SUCCESS.
    */
  int32_t (*SetDeviceInfo)(tWideDeviceInfo *info);


	/**
	 * Corresponds to read inputs function from the codesys device interface.
	 * This functions was added to support the digital offset (mod_com) for the kbus.
	 * @param dev_nr
	 * @param taskid
	 * @param offset
	 * @param size
	 * @param buffer
	 * @return
	 */
	int32_t (*ReadInputs)(  uint32_t deviceNr,
                           uint32_t taskId,
                           uint32_t offset,
                           size_t size,
                           uint8_t *buffer);

	/**
	 * Corresponds to the write outputs functions from the codesys device interface (DevItf).
	 * This functions was added to support the digital offset (mod_com) for the kbus.
	 * @param dev_nr
	 * @param taskid
	 * @param offset
	 * @param size
	 * @param buffer
	 * @return
	 */
	int32_t (*WriteOutputs)(uint32_t deviceNr,
                           uint32_t taskId,
                           uint32_t offset,
                           size_t size,
                           uint8_t *buffer);
} tWideInterface, *IWide;


/**
 * The tWideRts is the WIDE equivalent to the codesys RtsApi.
 */
typedef struct stWideRts
{
   int32_t  (*RtsStopAllTasks)(void);
   void (*RtsStartAllTasks)(void);
   uint8_t (*RtsGetPlcState)(void);
   uint8_t (*RtsProgramLoaded)(void);
   uint8_t* (*RtsGetInputMemory)(void);
   uint8_t* (*RtsGetOutputMemory)(void);

   uint32_t (*RtsGetInputSize)(void);
   uint32_t (*RtsGetOutputSize)(void);
   uint8_t*  (*RtsGetRetainSegment)(void);
   size_t (*RtsGetRetainSegmentSize)(void);
   size_t (*RtsGetProjectRetainSize)(void);

   void (*RtsProgramReset)(uint8_t);
   tWideProjectInfo *(*RtsGetProjectInfo)(void);
   void (*CstDebugOut)(const char *fmt, va_list args);

   char (*RtsEvtGenerateEvent)(tWideRtsEvent event, tWideRtsEventFilter filter, tWideRtsEventSource source);


   void (*RtsSetLastError)(uint32_t error, uint32_t parameter, const char *errorText, uint32_t taskId);
   tWideRtsLastError *(*RtsGetLastError)(void);

   /* CommonConfig interface */
   tWideCCHeader *(*RtsCCGetHeader)(void);
   tWideCCModule *(*RtsCCGetRootModule)(void);
   tWideCCModule *(*RtsCCGetRootModuleByModuleId)(uint32_t  moduleId);
   tWideCCModule *(*RtsCCGetRootModuleByNodeId)(uint32_t nodeId);
   tWideCCLoadError *(*RtsCCGetError)(char );

   void (*RtsStopIECTasks)(void);
   void (*RtsResumeIECTasks)(void);

   int16_t (*RtsGenerateException)(uint32_t ulTaskId, uint32_t ulExceptionNumber, char *infoText);

   /* Is called to create a task.
    szTaskName: The name of the task
    byPriority: Priority of the task
    ulInterval: Interval in microseconds
    pFunction:  Function which implements the task.
    pArgument:  Pointer to the argument which is passed on entry.
    Returns a unique task id. */
   uint32_t (*SysTaskCreate)(char*,
                             uint8_t,
                             uint32_t,
                             void*,
                             void*);
   /* Is called to destroy the given task. Returns 0 if the task couldn't be destroyed. */
   char (*SysTaskDestroy)(uint32_t ulTaskId);
   /* Prevents excecution of the current task and addresses the scheduler to resume
    excecution after the given time (ms). */
   void (*SysTaskSleep)(uint32_t ulMilliSeconds);
   /* Terminates the task from which the function is called. */
   void (*SysTaskEnd)(uint32_t ulExitCode,
                      uint32_t ulTaskId);

   /**
    * Returns the taskNr of the current task. (pthread_self() for codesys)
    * @return Returns the number of the task on success,
    *                 WIDE_TASKID_INVALID otherwise.
    */
   uint32_t (*SysTaskGetCurrent)(void);


   tWideSysTaskInfo* (*RtsGetTaskInfo)(uint32_t taskId);


     /* Returns the task description of the specified task. */
   tWideTaskDescription *(*TskGetDescById)(uint32_t ulTaskId);

   /* Returns the task description of the specified task. */
   tWideTaskDescription *(*TskGetDesc)(uint8_t byTaskNr);

   /* Returns the download configuration of the specified task */
   tWideTaskDownloadFormat *(*TskGetConfig)(uint32_t ulTaskId);

   /**
    * Returns the number of tasks.
    * @return Number of tasks
    */
   uint8_t (*TskGetNumberOfTasks)(void);

   char (*ConfigReadInt)(char *pszSection, char *pszKey, int *piRead);

   char (*ConfigWriteInt)(char *pszSection, char *pszKey, int iWrite);

   char (*ConfigReadString)(char *pszSection, char *pszKey, char *pszRead, int *piReadLen);

   char (*ConfigWriteString)(char *pszSection, char *pszKey, char *pszWrite);

   char (*ConfigReadBin)(char *pszSection, char *pszKey, unsigned char *pbyRead, int *piReadLen);

   char (*ConfigWriteBin)(char *pszSection, char *pszKey, unsigned char *pbyWrite, int iWriteLen);

   char* (*ConfigGetConfigFileName)(void);

   uint8_t * (*RtsGetMemorySegment)(void);

   size_t (*RtsGetMemorySegmentSize)(void);

   /**
    * Opens a system com port.
    * @param sPort The port to open.
    * @return Returns a handle which has to be used in the further
    *         access to the com port. On failure WIDE_PORTID_INVALID is returned.
    */
   uint32_t (*SysComOpen)(int16_t sPort);

   /**
    * Closes a system com port.
    * @param ulPort Handle of the port to close.
    * @return 1 on success, 0 otherwise
    */
   int8_t (*SysComClose)(unsigned long ulPort);

   /**
    * Changes the systems' com port setting.
    * @param ulPort Handle to the port
    * @param pSettings The new settings to apply.
    * @return Returns 1 on success, 0 otherwise.
    */
   int8_t (*SysComSetSettings)(unsigned long ulPort, tWideCOMSettings *pSettings);


   /**
    * Changes the systems' com port setting.
    * @param ulPort Handle to the port
    * @param pSettings The new settings to apply.
    * @return Returns 1 on success, 0 otherwise.
    */
   int8_t (*SysComSetSettingsEx)(unsigned long ulPort, tWideCOMSettingsEx *pSettings);

   /**
    * Enables/ Disables the rs485 transciever.
    * @return Returns 1 on success, 0 otherwise.
    */
   int32_t (*SysComSetRs485Enabled)(uint32_t fd, bool enabled);

   /**
    * Reads from a systems' com port until ulSize bytes are read or until ulTimeout is reached.
    * @param ulPort Handle to the port.
    * @param pbyBuffer Pointer to the buffer.
    * @param ulSize Amount of bytes to read.
    * @param ulTimeout Timeout after which to stop reading.
    * @return Returns the number of bytes read.
    */
   uint32_t (*SysComRead)(uint32_t ulPort, uint8_t *pbyBuffer, size_t ulSize, uint32_t ulTimeout);

   /**
    * Writes to a systems' com port until ulSize bytes are written or untul ulTimout is reached.
    * @param ulPort Handle to the port
    * @param pbyBuffer Pointer to the buffer
    * @param ulSize Amount of bytes to write
    * @param ulTimeout Timeout after which to stop writing.
    * @return Returns the number of bytes written.
    */
   uint32_t (*SysComWrite)(uint32_t ulPort, uint8_t *pbyBuffer, size_t ulSize, uint32_t ulTimeout);

   /**
    * Routine to get the complete path for file handling.
    * If pszFileName has still a directory definition, this will copied to pszFilePath.
    * If pszFileName has no directory definition, default directory is called from
    * CstProcessHook with PH_GET_FILE_PATH
    * @param pszFilePath Resultating Path
    * @param ulSizePath Size of pszFilePath
    * @param pszFileName original name (and Path)
    */
   char (*RtsGetCompleteFilePath)(char *pszFilePath, unsigned long ulSizePath, char *pszFileName);

   /**
    * Call this routine to update the task_io_usage in the wago ipc io driver.
    */
   void (*IoDriverCheckIoUsage)(void);


   /**
    *  Call this function to enable codesys' task supsension.
    */
   void (*SysTaskSuspensionEnable)(void);

   /**
    *  Call this function to disable codesys' task suspension.
    *  This is useful when running in IEC-context to prevent data from getting inconsistent.
    *  Note: Codesys suspends and later cancels iec task, when they don't respond to a plc state change (RTS_STOP_SRV)
    *         in a specific amount of time.
    */
   void (*SysTaskSuspensionDisable)(void);

//
//   PFRTSEXITPLC pfRtsExitPLC;
//   PFSYSEXECUTECOMMAND pfSysExecuteCommand;
//
//   PFRTSSAVERETAINS pfRtsSaveRetains;
//   PFRTSRESTORERETAINS pfRtsRestoreRetains;
//
//   PFRTSGETSEGMENTADDRESS pfRtsGetSegmentAddress;
//
//   PFROUTERSENDMESSAGE pfRouterSendMessage;
//
//   PFTSKGETNUMBEROFTASKS pfTskGetNumberOfTasks;
//   PFTSKGETTASKDESC pfTskGetTaskDesc;
//   PFDBGWRITECALLSTACK pfDbgWriteCallStack;
//   PFSYSTASKGETCURRENT pfSysTaskGetCurrent;
//   PFRTSGETIECTASKDESCBYID pfTskGetDescById;
//   PFRTSGETSEGMENTSIZE pfRtsGetSegmentSize;
//
//   /* Symbol interface */
//   PFRTSGETALLSYMBOLS pfRtsGetAllSymbols;
//   PFRTSGETSYMBOL pfRtsGetSymbol;
//   PFRTSGETSYMBOLBYADDRESS pfRtsGetSymbolByAddress;
//   PFRTSGETSYMBOLADDRESS pfRtsGetSymbolAddress;
//   PFRTSGETSYMBOLADDRESSBYDESC pfRtsGetSymbolAddressByDesc;
//   PFRTSCREATEVARVALUE pfRtsCreateVarValue;
//   PFRTSCREATEVARVALUEBYDESC pfRtsCreateVarValueByDesc;
//   PFRTSDELETEVARVALUE pfRtsDeleteVarValue;
//   PFRTSREADVAR pfRtsReadVar;
//   PFRTSREADVARBYDESC pfRtsReadVarByDesc;
//   PFRTSWRITEVAR pfRtsWriteVar;
//   PFRTSWRITEVARBYDESC pfRtsWriteVarByDesc;
//   PFRTSDEFINEVARLIST pfRtsDefineVarList;
//   PFRTSDEFINEVARLISTBYDESC pfRtsDefineVarListByDesc;
//   PFRTSDEFINEVARLISTBYFILTER pfRtsDefineVarListByFilter;
//   PFRTSDELETEVARLIST pfRtsDeleteVarList;
//   PFRTSGETNUMOFSYMBOLS pfRtsGetNumOfSymbols;
//   PFRTSGETSYMBOLLIST pfRtsGetSymbolList;
//   PFRTSGETVALUELIST pfRtsGetValueList;
//   PFRTSREADVARLIST pfRtsReadVarList;
//   PFRTSWRITEVARLIST pfRtsWriteVarList;
//   PFRTSGETRTSINFO pfRtsGetRtsInfo;

/***** ATTENTION: Add new routines always at the end of the structure! *****/
} tWideRts, *IWideRts;


/**
 * This typedef defines the signature of the WIDE-open method.
 * @param wideApi Interface of the WIDE. Functions implemented by the wide must be
 *       overwritten. Functions not implemented by the WIDE have to be set to NULL.
 * @param rtsApi Api of the runtime system.
 * @param adiApi Api of the DAL.
 * @return WIDE_SUCCESS on succes, WIDE_FAILURE otherwise.
 */
typedef int32_t (*tFnWagoIoDriverExtension_Open)(IWide wideApi,
                                                 const tWideRts* rtsApi,
                                                 IApplication adiApi);

//------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local variables
//------------------------------------------------------------------------------


#endif  // D_Wide_api_H
