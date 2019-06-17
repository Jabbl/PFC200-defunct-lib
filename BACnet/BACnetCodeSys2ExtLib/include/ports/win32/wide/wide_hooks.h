#ifndef D_WIDE_HOOKS_H
#define D_WIDE_HOOKS_H

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
/// \brief This header (re-) defines all hooks used by codesys.
///
/// \author ${user} : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------

/********** Types **********/

/* Process hooks (see parameter ulHook of CstProcessHook)
   GENERALS:
   ulHook: the specified hook, see below
   Return:  0 = the standard kernel part is executed (hook is not handled by customer)
         1 = hook is handled by customer
*/

#define WPH_NEW_PLC_STATE               1
/* This hook is called when the internal state of the PLC is about to change.
   ulAdditionalInfo is the new state. RtsGetPLCState() still returns the old state. */

#define WPH_IO_CONFIG_CHANGED           2
/* Is called after plc-config changed (download of a new program) */

#define WPH_IO_DESCRIPTION_CHANGED         3
/* Is called after task specific IO-descritpion changed (download of a new program) */

#define WPH_AFTER_PROGRAM_DOWNLOAD         4
/* Is called after program download:
   ulAdditionalInfo:  1 = After Download, 0 = After Online-Change */

#define WPH_BEFORE_RESET                5
/* Is called before reset.
   ulAdditionalInfo: reset type (RTS_RESET_COLD, RTS_RESET_HARD, RTS_RESET_WARM) */

#define WPH_AFTER_RESET                 6
/* Is called after reset,
   ulAdditionalInfo: reset type (RTS_RESET_COLD, RTS_RESET_HARD, RTS_RESET_WARM) */

#define WPH_SYMBOL_DESCRIPTION_CHANGED     7
/* Is called after symbol descripton has changed (download of a new program) */

#define WPH_CODE_CHANGED                8
/* Is called after a new program code is loaded, but before CmInit
   ulAdditionalInfo:  1 = After Download, 0 = After Online-Change */

#define WPH_GET_TASK_TIMEBASE           9
/* Return the task timebase. The standard task timebase in CoDeSys is ms. The timebase
   must be set to the following values:
   milli sec: 1000   [default]
   micro sec: 1
   ulAdditionalInfo:  int* that receives the value */

#define WPH_GET_TASK_SCHEDULEINTERVAL      10
/* Return the task schedule interval in microseconds.
   schedule base tick:
   1000 microseconds == 1 millisecond [default]
   ulAdditionalInfo:  int* that receives the value */

#define WPH_GET_VENDOR_NAME             11
/* Return the vendor name of the controller.
   ulAdditionalInfo:  char* pointer to copy the vendor name;
                  maximum size to copy must not exceed 31 characters!!*/

#define WPH_GET_CODE_SIZE               12
/* Return the predefined code size for the IEC-program */

#define WPH_GET_DATA_SIZE               13
/* Return the predefined data size for the IEC-program */

#define WPH_GET_TASK_STACK_SIZE            14
/* Return the stack size for the created task.
   ulAdditionalInfo:  priority of the task */

#define WPH_GET_RETAIN_SIZE             15
/* Return the size of retain area */
#define WPH_GET_RETAIN_ADDRESS          16
/* Return the address of retain area. Memory must exist or NULL if not available! */

#define WPH_GET_TASK_PRIORITY           17
/* Return the task priority for the created task.
   ulAdditionalInfo:  pointer to structure PH_GET_TASK_PRIORITY_INFO. Contains priority of the task
   and ulTaskId
   Return new priority of the task */

typedef struct tagPH_GET_TASK_PRIORITY_INFO
{
   unsigned long ulPriority;
   unsigned long ulTaskId;
   unsigned long ulNewVersionTag; /* always 0x22111964 */
   unsigned long ulNewVersionTag2; /* always 0x03031963 */
   unsigned long ulVersion;
   unsigned long ulTaskHandle;
} PH_GET_TASK_PRIORITY_INFO;

#define WPH_DONT_INIT_RETAIN_ON_DOWNLOAD      18
/* Is called on download of plc-program.
   Specifies, if retain variables should not be initialized on download. */

#define WPH_SINGLETASKING               19
/* Return whether singletasking is desired.
   Default should be FALSE */

#define WPH_GETFUNCTIONPOINTER          20
/* Return the function of the function. Name given in ulAdditionalInfo */

#define WPH_GET_FILE_PATH               21
/* Set the standard file path for all files.
   In ulAdditionalInfo, the pointer to the file name is passed.
   ulAdditionalInfo is also a pointer to the buffer where you can
   copy the file-path string (size 255). Copy only the path to the
   buffer, not the filename. Doing this, you overwrite the filename,
   but thats ok. The core system will append the file name. */


#define WPH_DONT_LOAD_BOOTPROJECT       22
/* To suppress loading bootproject.
   Return:   1: Bootproject would not be loaded
          0: Bootproject is loaded (Default) */

#define WPH_GET_TICK_INTERRUPT          23
/* mainly for CE, return interrupt which triggers the realtime scheduler
   Return:   interrupt number
          ffffffff: no interrupt */

#define WPH_INSTALL_CUSTOMER_SCHEDULED_TASK   24
/* an IEC task will be created which can be controlled by user hooks (blocked at the start of the task function)
   Pointer to task description given in ulAdditionalInfo
   Return:   ignored */

#define WPH_UNINSTALL_ALL_CUSTOMER_SCHEDULED_TASKS  25
/* hook to throw away all objects created for handling customer controlled tasks (e.g. semaphores)
   Return:   ignored */

#define WPH_START_CUSTOMER_SCHEDULED_TASK  26
/* hook at start of customer controlled tasks => user can block task here to synchronize it with some other task etc.
   Pointer to task description given in ulAdditionalInfo
   Return:   ignored */

#define WPH_END_CUSTOMER_SCHEDULED_TASK    27
/* hook at end of customer controlled tasks => user can block task again here => 1 shot tasks
   Pointer to task description given in ulAdditionalInfo
   Return:   ignored */

#define WPH_DISABLE_ONLINE_CHANGE       28
/* hook to disable feature online change
   if so, only one code buffer is allocated and therefore significantly less RAM is used

   Return:  TRUE to disable
         FALSE to enable */

#define WPH_DISABLE_SERIAL_PROGRAMMING     29
/* hook to disable serial communications to CoDeSys and other Windows clients
   if disabled, no COM ports are opened and no comm driver task is created

   Return:  TRUE to disable
         FALSE to enable */

#define WPH_DISABLE_TCPIP_PROGRAMMING      30
/* hook to disable TCP/IP communications to CoDeSys and other Windows clients
   if disabled, no sockets/ports are opened and no comm driver task is created

   Return:  TRUE to disable
         FALSE to enable */

#define WPH_DENY_PLC_STATE              31
/* This hook is called when the state of the plc is about to change.
   ulAdditionalinfo in the new state. RtsGetPLCState() still returns the old state.
   Return 1 if you want to forbid the new state, else 0 */

#define WPH_INSTALL_ISR                 32
/* This hook is called when an IEC callback function for an ISR is to be installed
   ulAdditionalinfo is a long[2] array with elements: interrupt number and ISR function address
   Return 1 if handled
   used mainly for Windows CE */

#define WPH_DEINSTALL_ISR               33
/* This hook is called when an IEC callback function for an ISR is to be installed
   ulAdditionalinfo is a long[2] array with elements: interrupt number and ISR function address
   Return 1 if handled
   used mainly for Windows CE */

#define WPH_GET_PLC_STATE_FOR_BOOTPROJECT  34
/* Hook to get plc state after the bootproject is loaded.
   Here e.g. a hardware switch can be used to set the state.
   ulAdditionalInfo:  unsigned char* that receives the new plc state */

#define WPH_CODESYS_LOGGEDOUT           35
/* Hook to get info, when codesys logged out */

#define WPH_RTS_INIT_DONE               36
/* Initialization of runtime system is finished successful */

#define WPH_GET_NUM_OF_COM_PORTS           37
/* Get num of serial COM-ports to open for communication */

#define WPH_BEFORE_IEC_CYCLE               38
/* Is called at the beginning of each IEC-task. The task can be located by TaskId:
   ulAdditionalInfo:  unsigned long ulTaskId of the IEC-task */

#define WPH_AFTER_IEC_CYCLE             39
/* Is called at the end of each IEC-task. The task can be located by TaskId:
   ulAdditionalInfo:  unsigned long ulTaskId of the IEC-task */

#define WPH_EXCEPTION                40
/* Is called, if an exception occurred. The behaviour can be selected by the result:
   ulAdditionalInfo: PH_EXCEPTION_DESC* = pointer to exception description
   ulResult:   EXCPT_UNHANDLED / EXCPT_TASKCONTINUE / EXCPT_TASKSUSPEND /
            EXCPT_PLCEXIT / EXCPT_PLCSTOP
*/

#define WPH_BEFORE_PROGRAM_DOWNLOAD        41
/* Is called before program download:
   ulAdditionalInfo:  1 = After Download, 0 = After Online-Change */

#define WPH_TASK_START                  42
/* Is called when a task in created. It is called from the context of the new task
   ulAdditionalInfo:  TASK_DESCRIPTION* = pointer to task description */

#define WPH_GET_SYSTEM_TIME             43
/* Must give system time in ms, turnaround at 0xffffffff
   ulAdditionalInfo:  unsigned long* = pointer time value */

/* #define WPH_UI_MESSAGE                  44 no longer implemented */
/* Output a user message, e.g. a message box
   ulAdditionalInfo:  pointer to a UIMessage structure */

#define WPH_SYMBOL_DESCRIPTION_INVALID     45
/* Symbol file is being deleted. User must immediately kill all symbol access
   and reinitialize symbol access with next hook PH_SYMBOL_DESCRIPTION_CHANGED */

#define WPH_GET_COMM_BUFFER_SIZE           46
/* Determines the size of the communication buffers for all drivers
   ulAdditionalInfo:  unsigned long* = pointer to buffer size, contains default buffer size at call */

#define WPH_GET_MASTER_PASSWORD           47
/* Get master password to crack forgotten passwords.
   ulAdditionalInfo:  char* = pointer to char string with 255 bytes length to get clear password */

#define WPH_GET_CONFIG_FILENAME            48
/* Get the filename for the runtime configuration.
   ulAdditionalInfo:  char* = pointer to char string with 255 bytes length to get filename */

#define WPH_DISABLE_POINTERWATCH           49
/* hook to disable feature monitoring of pointers
   Return:  TRUE to disable
         FALSE to enable */

#define WPH_DISABLE_MUTABLEOFFSETWATCH     50
/* hook to disable feature monitoring of array elements with variable index
   Return:  TRUE to disable
         FALSE to enable */

#define WPH_DISABLE_EXTENDEDTASKCONFIG     51
/* hook to disable support for CoDeSys 23.extended task configuration and use older task config instead
   Return:  TRUE to disable
         FALSE to enable */

#define WPH_FREEWHEELING_CYCLE_TIME        52
/* hook to get the cycle time in [ms] of a freewheeling IEC-task */

#define WPH_ENABLE_SOFTMOTION           53
/* Enable soft-motion support
   Return:  1 to enable
         0 to disable */

#define WPH_USE_IODRIVER_INTERFACE         54
/* hook to enable standard IO-driver interface
   Return:  1 enable
         0 IO update must be done in custom module! */

#define WPH_INTERRUPTOCCURED               55
/* hook to inform that interrupt number n has occured
   ulAdditionalInfo:  interrupt number n
   return: ignored
 */

#define WPH_BUFFERINTERRUPTS               56
/* hook to tell the kernel that for an interrupt the occured events should be counted
   implemented only for external event task under Windows CE
   ulAdditionalInfo:  TASK_DESCRIPTION*
   return: 1 or 0
 */

#define WPH_SCHEDULERTICKFROMIODRIVER      57
/* hook to disable default timer task and get system tick from an IO driver
   ulAdditionalInfo:  pointer to scheduler function (TimerHandler) to be called every 1 ms
   return: 0 for using default handler
         != 0 if the IO driver provides a timer task
*/

#define WPH_NOSCHEDULER                 58
/* hook to use sleep based scheduling instead of a scheduler
   needed if using IO driver interface
   ulAdditionalInfo:  0
   return: 0 for using scheduler
         1 for using sleep mechanism
*/

#define WPH_SHUTDOWN                    59
/* hook during shutdown task (SysLibShutDownPlc)
   ulAdditionalInfo:  0 => before RtsExitPlc is called
   Return:     TRUE if RtsExitPlc should not be called
            FALSE otherwise
   ulAdditionalInfo:  1 => after RtsExitPlc has been performed
   Return:     ignored
*/

#define WPH_RESTORE_RETAIN_DIRECT       60
/* hook to call IOItf/CstRestoreRetain even if mode CST_RETAIN_DIRECT is selected
   ulAdditionalInfo:
   Return:     TRUE if RestoreRetain should be called
            FALSE otherwise
   Return:     ignored
*/

#define WPH_SET_LAST_ERROR              61
/* Hook is called, if an error occurred and last error is set.
   Can be used to add the last error e.g. to a log-file, etc.
   ulAdditionalInfo:  pointer to RTS_LAST_ERROR structure
   Return:     ignored
*/

#define WPH_SCHEDULE_ONE_TASK           62
/*
   Return:     1=Scheduler only activates one task (only one IEC task is active)
            0=Scheduler activates all task that must run at each scheduler tick
   Default: 0
*/

#define WPH_SCHEDULE_TASK_LOGGING       63
/* Hook to enable IEC task logging. Log file is written, when TskLogWriteToFile() is called
   or plc shutdown is done (here log is saved as: TskSched.log).
*/

#define WPH_SETSEGMENTSIZE              64
/* Hook to change a segment size (must match with target settings)
   to be used carefully
   is not called for all OSes (only Win32, segments 0..2)
   ulAdditionalInfo: pointer to unsigned long [2], first is segment number,
                  second is size (which can be changed)
   Return:           ignored
*/

#define WPH_PRE_COMPUTE_SERVICE            65
/* Hook to pre handle online service.
   ulAdditionalInfo: pointer to PH_ONLINE_SERVICE_DESC
   Return:           1: online service handled
                  0: kernel handels the service
*/

#define WPH_POST_COMPUTE_SERVICE           66
/* Hook to pre handle online service.
   ulAdditionalInfo: pointer to PH_ONLINE_SERVICE_DESC
   Return:           ignored
*/

#define WPH_RTC_CHECK_BATTERY           67
/* Hook to implement sys function SysRtcCheckBattery. Needed if this function can not be
   implemented with OS API (for example in WinCE)
   ulAdditionalInfo: unsigned long* == pointer to result value (1 == OK / 0 otherwise)
   Return:           1:
                  0:
*/



#define WPH_HWWATCHDOG_TRIGGER          68
/* Hook to retrigger hardware watchdog. Resets the elapsed time of the hardware
   watchdog to 0 ms and starts it again.
   *ATTENTION*: The hook is called out of the scheduler and this could be an interrupt context!
             Be aware not to use floating point operations, semaphores,
   ulAdditionalInfo: ignored
   Return:           1: retrigger done
                  0: retrigger not implemented
*/

#define WPH_HWWATCHDOG_SETTIME          69
/* Hook to start hardware watchdog with specified elapse time.
   ulAdditionalInfo: hardware watchdog interval
   Return:           1: hardware watchdog started
                  0: hardware watchdog not handled by IO driver
*/

#define WPH_GET_PROCESSING_STATE        70
/* Hook to update the processing state, before it is used to warn the
   user for doing a program download in an unsafe processing state.
   Called before a download or online change is performed.
    ulAdditionalInfo:   pointer to unsigned long ulProcessingState, contains current
                  processing state, can be changed in Hook
                  0 = Download and online change can be performed
                  other values: CoDeSys displays a confirmation dialog box before download
   Return:           1: New value of ulProcessingState taken
                  0: ulProcessingState not updated
*/

#define WPH_GET_BP_OPCODE               71
/* Hook to get alternative breakpoint opcode.
   ulAdditionalInfo: pointer to unsigned long with bp opcode from rtstrg.c, can be changed if needed
   Return:           ignored
*/

#define WPH_CUSTOM_HOOK                 72
/* Hook for custom use to hook from one custom module to another (e.g. from RtsCst to CstItf).
   ulAdditionalInfo: custom dependant
   Return:           custom dependant
*/

#define WPH_ENABLEACCESSTODATAAREA         73
/* Hook to allow access to data area if implemented as a shared memory object
   ulAdditionalInfo: unsigned long == access mode,
                           1 means access is not allowed because IEC code is executed by a task
                           or a variables list is written by CoDeSys or another client of RtsSrv
                           0 means a task has finished with its code, or the variable list has been written
                  So a different application can only have exclusive access to the data area, if it counts
                  the hooks with ulAdditionalInfo == 1 and the hooks with ulAdditionalInfo == 0
                  and if these two counters are equal
   Return:           ignored

*/

#define WPH_GETTASKDESCFORINTERRUPT        74
/* hook to get the task description of an external event task
   implemented only for Windows CE
   ulAdditionalInfo:  interrupt number
   return: TASK_DESCRIPTION*
 */

#define WPH_AFTERNEWPLCSTATE               75
/* hook after controller status has been changed
   (PH_NEW_PLC_STATE comes before the controller status has been changed)
   ulAdditionalInfo is the new state.
   return:        ignored
 */

#define WPH_APPEND_RTSINFO              76
/* hook to append text to rtsinfo browser command
   ulAdditionalInfo: char* to buffer to write to
   return:        ignored
 */

#define WPH_BROWSER_RECEIVETEXT            77
/* hook when a PLC browser command has been received
   ulAdditionalInfo: char* to received text
   return:        ignored
 */

#define WPH_BROWSER_SENDTEXT               78
/* hook before a PLC browser response is sent (change the text etc.)
   ulAdditionalInfo: char* to text to be sent
   return:        ignored
 */

#define WPH_DONT_DELETE_BOOTPROJECT_WITH_RETAIN_ERRORS 79
/* hook to modify behaviour if access to retain variables cannot be relocated when loading boot project
   useful e.g. if a SRAM card is missing
   ulAdditionalInfo: ignored
   return:        1: the boot project file (and other files) are not deleted, but only the project is deleted from RAM
               0: default behaviour, delete boot project file and other files
 */

#define WPH_SCHEDULE_EXT_TIMESLICE         80
/* External timeslicing.
   return:  1: External timeslicing is on
         0: Standard scheduling without timeslicing */

#define WPH_USE_CFG_FILE_INSTEAD_OF_SYSCONFIG    81
/* for operating system which support a system-specific configuration media, like registry
   use this hook to force taking settings from rts3s.CFG (INI) file and not from the system-specific media
   return:  1: take settings from rts3s.cfg
         0: take settings using system-specific method, e.g. registry
*/

#define WPH_COMPARE_SDBFILES_AT_BOOTING    82
/* When loading a boot project, normally the download.sdb is deleted and then boot.sdb copied to download.sdb
   with some targets, this is a problem for the flash
   use this option to do the following instead of the above method:
   compare sdb files and only delete+copy if necessary
   return:  1: enable compare sdb files and only delete+copy if necessary
         0: Standard method, see above */

#define WPH_BOOTBEHAVIOUR               83
/* Hook to modify startup behaviour with boot project
      ulAdditionalInfo: unsigned long* == pointer to result value (desired behaviour)
      Return: TRUE/FALSE
      with TRUE, a Reset command is performed
     ulAdditionalInfo:  unsigned long* == desired behaviour:   RTS_RESET_COLD, RTS_RESET_HARD
                                                any other value: RTS_RESET_WARM

*/

#define WPH_NEW_CODE_SIZE               84
/* Get informed when a new project with a new code size is received
      ulAdditionalInfo: unsigned long == new size
   return:  ignored
*/
#define WPH_NEW_DATA_SIZE               85
/* Get informed when a new project with a new data size is received
      ulAdditionalInfo: unsigned long == new size
   return:  ignored
*/

#define WPH_CHECK_BOOTPROJECT_SUCCESSFUL      86
/* Hook to en/disable checking if the PLC has booted with the boot project successfully
   when the bootproject file etc. is OK, but nevertheless the PLC crashes
      ulAdditionalInfo: unsigned long == new size
   return:  1/0, default 0
*/

#define WPH_PRE_LOADING_XML_LANGUAGE_FILE  87
/* Hook for target visu: before loading and parsing an XML language file (startup, switching active language)
   this can be a long operation with big files so here one could output information etc.
   this hook is called once for each file
      ulAdditionalInfo: file size in bytes of the XML file
   return:  ignored
*/

#define WPH_POST_LOADING_XML_LANGUAGE_FILE 88
/* Hook for target visu: an XML language file has been read and parsed
   this hook is called once for each file
      ulAdditionalInfo: ---
   return:  ignored
*/

#define WPH_NEW_HANDLE_FOR_COM_PORT        89
/* Hook after opening/closing a COM port
      ulAdditionalInfo:
      unsigned long*

      ulAdditionalInfo[0]  COM port number
      ulAdditionalInfo[1]  operating system handle for COM port number

   return:  ignored
   implemented for Win32 only
*/

#define WPH_RTS_START_BEFORE_BOOTPROJECT      90
/* Hook on startup before loading bootproject */

#define WPH_ADDITIONAL_INFO_FOR_CE_SCHEDULER  91
/* Windows CE only
the 1 ms interrupt handler for the scheduler needs additional, e.g. time resolution

      ulAdditionalInfo:
      unsigned long*

      ulAdditionalInfo[0]  LPVOID data
      ulAdditionalInfo[1]  DWORD sizeof(data)

   return: TRUE if you want to set the information
*/

#define WPH_PRE_BEFORE_RESET               92
/* Is called before reset, even before the hook PH_BEFORE_RESET
   ulAdditionalInfo: reset type (RTS_RESET_COLD, RTS_RESET_HARD, RTS_RESET_WARM)

   Usage:
   e.g. after booting with a stored hardware watchdog event, PLC could have set some
   error LEDs etc. and loading the boot project might have been suppressed by hook
   PH_DONT_LOAD_BOOTPROJECT. This could now be acknowledged by the user with a RESET
   command so the error is cleared and the boot project might now be loaded
*/

#define WPH_FREEWHEELING_TASK_WITH_IDLE_PRIORITY       93
/* Hook to execute freewheeling tasks with idle priority
   return 1: SysTaskCreate will be called with lowest priority (255)
   return 0: SysTaskCreate will be called as usual (IECTASK_BASE_PRIORITY + prio defined in CoDeSys)

   so the behaviour is to some extent OS dependent
*/

#define WPH_USE_SERIAL_COMM_WITH_ROUTING               94
/* Hook to use routing in serial communication
   return 1: Use serial communication with routing
   return 0: Use serial communication without routing
*/

#define WPH_RETAIN_IDENTITY_MISMATCH                95
/* Hook to set the action after a retain identity mismatch was detected
   ulAdditionalInfo: PH_RETAIN_IDENTITY_MISMATCH_ACTION* == pointer to specify the action:
      PH_RETAIN_IDENTITY_MISMATCH_ACTION.bInitRetains = 1: Initialze all retains
      PH_RETAIN_IDENTITY_MISMATCH_ACTION.bStop = 1: Don#T start plc program after loading bootproject
   return 1: Do the specified action
   return 0: Default action (init retains and run program)
*/

#define WPH_DISABLE_WEBVISU                      96
/* Hook to disable web visu
   return 1: Webvisu not possible
   return 0: Webvisu enabled
*/

#define WPH_LOAD_SYMBOLS                         97
/* Hook to let the OEM decide if the symbol should be loaded after download.
   Most OEMs use the symbol file download for the OPC server. The controller is
   just a file storage for the symbol file in this case. Therefore, it needn't to be loaded
   to memory.
   Some customers want to use the functions in RtsSym.h to access some variables by name.
   To avoid concurrent access to the symbol file out of different tasks, return 1 on this hook.
   This will cause that the symbol file is loaded to rtssym.c by the runtime system.
   return 1: If you want the symbol file to be loaded into memory automatically after download
   return 0: The symbol file is not loaded automatically (default)
*/

#define WPH_PROGRAM_LOADED                       98
/* Hook to get informed when a program load/unload is finished
   ulAdditionalInfo : state of the program (1:loaded,0:unloaded)
   return : ignored
*/

#define WPH_USE_CONFIGURED_AND_UNCONFIGURED_IO         99
/* Hook to disable the check, if configured and unconfiguresd IOs are mixed. Normally in
   this case appears an IO-update-error in CoDeSys. This Hook has to be used, if there
   are configured IOs and additional a Hilschercard (Interbus,...), which is configured
   by an axternal tool.
   return 1: use configured and also unconfigured IOs
   return 0: Mix-mode ist not allowed. (default)
*/

#define WPH_SET_BYTE_ADDRESSING_FOR_SYMBOLIC_ITF       100
/* Hook to set the Byte-Addressing Mode for the Symbolinterface. This is only used for
   symbolic access to symbols like "%QD100" or "%MX10.0" with the functions defined
   in RtsSym.c. In all other cases the Addressing-Mode have not to be set.
   return 1: Byte-Addressing Mode
   return 0: Word-Addresssing-Mode (default)
*/

#define WPH_ENABLE_PARTIAL_FILE_DOWNLOAD      101
/* Hook to enable two related features:
   1. if a new download is performed and a partial download with the same content is already present
   this download is continued.
   2. if a new file transfer starts, and a partial file with the same content is already stored,
   this file download is continued
*/

#define WPH_GET_MAX_NUMBER_OF_EXTREFS      102
/* Hook to set the maximal number of External References, which are defined in the
    IO-Drivers.
   ulAdditionalInfo: unsigned long* == pointer to desired number of ExtRefs.
   return 1: Number of max. ExtRefs is defined by ulAdditionalInfo
   return 0: about 120 ExtRefs can be defined in the IO-Drivers (default)
*/

#define WPH_TARGETVISU_EXIT             103
/* Hook to perform target visu exit
   Your hook should perform TargetVisuUserExit and TargetVisuKernelExit

   ulAdditionalInfo: ----
   return: ignored
*/

#define WPH_IS_TARGETVISU_TASK          104
/* Hook to determine if a task is an implicit task of target visu
   (tasks with name VISU_TASK, VISU_INPUT_TASK, ALARM_TASK, TREND_TASK)
   ulAdditionalInfo: pointer to TaskDescription
   return: 0/1
*/

#define WPH_IS_TARGETVISU_INITIALIZED      105
/* Hook to determine if target visu initialization has been finished
   (target visu kernel and target visu user part must have been initialized)

   ulAdditionalInfo: ----
   return: 0/1
*/

#define WPH_USE_UNICODE_FILEPATH           106
/* Hook to set a unicode filepath

   ulAdditionalInfo[0]: Pointer to file path buffer
   ulAdditionalInfo[1]: Pointer to Unicode Filename
   return: 0/1
*/

#define WPH_CONFIG_SKIP_MODULE          107
/* Hook to allow the adaptation part to skip a IO configuration module
   To avoid errors if a (profibus) module is defined in the IO configuration,
   but not present physically.

   ulAdditionalInfo: Pointer to a CCModule structure
   Return 1 to overread the modue description. The modue is not added to the module list
   Return 0 for default behaviour
*/

#define WPH_AFTERNEWPLCSTATE_DONE       108
/* hook after controller status has been changed to RTS_STOP_SRV and tasks are stopped
   (PH_NEW_PLC_STATE comes before the controller status has been changed)
   (PH_AFTERNEWPLCSTATE comes when the new status has been set to stop, but some
   tasks may still be running at this time)
   ulAdditionalInfo is the new state.
   return:        ignored
 */

#define WPH_STOPALLTASKS_ASYNC          109
/* Hook called in function RtsStopAllTasksAsync. Gives an adaptation the possiblility to
   implement the function by its own.
   Return 1 if you implement the function by your own.
   Return 0 for default behaviour
*/

#define WPH_RETAIN_IDENTITY_MISSING        110
/* Hook to set the action after a retain identity was not found in nonvolatile memory
   ulAdditionalInfo: 0
   return 1: Retain memory is treated as invalid
   return 0: Retain memory is treated as valid to support older runtimes.
*/

#define WPH_TASK_WAIT_PERIOD               111
/* Hook to use a system specific SysTaskWaitPeriod() function instead of SysTaskSleep() for periodic tasks
   ulAdditionalInfo: 0
   return 1: system specific SysTaskWaitPeriod() function is used in the hook
   return 0: use default mechanism
*/

#define WPH_RS485_WRITE                 112
/* Hook to switch from RS232 to RS485 mode (Linux only)

   ulAdditionalInfo: 1==before SysComWrite   0==after SysComWrite
   return: ignored
*/

#define WPH_CODESYS_LOGGEDIN               113
/*  Hook to get info, when codesys logged in
   ulAdditionalInfo: 0
   return:           ignored
*/

#define WPH_CONFCONF_ADDITIONALLEVEL       114
/* Hook to have ConfConf structure like this:
   root
      => "master device"
         => "slave device"
            => IO modules with channels
   instead of normal structure:
   root
      => "master device"
         =>  IO modules with channels

   ulAdditionalInfo: 0
   return 1: one level more
   return 0: normal structure
*/

#define WPH_IOITF_ARBITRARY_ORDER_OF_DEVICES     115
/* allow arbitrary order of devices in IO configuration.
   Normally, the order of the devices in the IO config tree must be the same
   order in which the corresponding IO driver in the RTS is loaded.
   This makes sense for > 1 driver for confconf modules, and requires using
   pfSupportsModules in the IO drivers.
   ONLY implemented and tested for conf conf modules!

   ulAdditionalInfo: 0
   return 1: arbitrary order
   return 0: order of the devices in the IO config tree must be the same
   order in which the corresponding IO driver in the RTS is loaded
*/

#define WPH_TARGETVISU_TEXT_SUBSTITUTION      116
/* Linux TargetVisu only
   allow text substitution before a text is painted on the screen
   ulAdditionalInfo: pointer to TrgVisuTextSubstitutionType (defined in RtsSysGraphics.h)
   return 1: text was substituted
   return 0: nothing to change
*/

#define WPH_DONT_RUN_AT_BP_LOGOUT       117
/* Called when a logout occurs while standing on a breakpoint.
   CoDeSys default behaviour is to set the program in run mode.
   With returning a nonzero value in this hook, OEM can avoid this.
   Program stays stopped at the breakpoint
*/

#define WPH_IO_UPDATE_IN_DEBUG_LOOP        118
/* Called while standing on a breakpoint.
   CoDeSys default behaviour is no update (only when outputs are written in CoDeSys online mode
   using Online/Write values, these are updated on the hardware).
   return 1: IO update in debug loop
   return 0: no IO update in debug loop
*/

#define WPH_DISABLE_CAN_PROGRAMMING     119
/* hook to disable CanOpen communications to CoDeSys and other Windows clients (if supported by runtime)
   if disabled, no can controller is initialized and no comm driver task is created

   Return:  TRUE to disable
         FALSE to enable */

#define WPH_WDG_TRIGGERED         120
/* called if the watchdog triggered - can be used to stop fieldbus and other i/o
 * updates
 */

#define WPH_FILESYNC 200
/*     Sync filesystem if needed
 */

#define WPH_BOOTPROJECT_NOT_LOADED 201
/*     after Bootprojekt is not loaded
 */

#define WPH_LOAD_BOOTPROJECT 202
/*     before Bootprojekt is loaded
 */

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local variables
//------------------------------------------------------------------------------


#endif  // D_Wide_api_H
