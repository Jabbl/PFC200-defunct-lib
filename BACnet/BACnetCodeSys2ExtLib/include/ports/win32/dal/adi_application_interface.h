//------------------------------------------------------------------------------
/// Copyright (c) WAGO Kontakttechnik GmbH & Co. KG
///
/// PROPRIETARY RIGHTS are involved in the subject matter of this material.
/// All manufacturing, reproduction, use and sales rights pertaining to this
/// subject matter are governed by the license agreement. The recipient of this
/// software implicitly accepts the terms of the license.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
///
///  \file     adi_application_interface.h
///
///  \version  $Revision: 7698 $
///
///  \brief    Register and configure devices 
///
///  \author   <rs> : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------
#ifndef _ADI_APPLICATION_INTERFACE_
#define _ADI_APPLICATION_INTERFACE_

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "dal_types.h"
#include "events/events.h"

typedef struct stApplicationDeviceInterface tApplicationDeviceInterface,
      *IApplication;

tApplicationDeviceInterface *adi_GetApplicationInterface(void);


/**
 * This structure defines the Application interface of the DAL.
 */
struct stApplicationDeviceInterface
{
   /**
    * Opens i.e. initializes the DAL.
    * @return DAL_FAILURE in case another instance is already running.
    *         DAL_SUCCESS on success.
    */
   int32_t (*Init)(void) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Main cleanup routine for the DAL. Releases the allocated ressources, triggers
    * closing of the devices etc.
    * @note currently this never fails.
    * @return DAL_SUCCESS.
    */
   int32_t (*Exit)(void) DAL_GNUC_WARN_UNUSED_RESULT;


   /**
    *
    * ScanDevices() checks all shared objects contained in the device library
    * search path (default path is /usr/lib/dal) and calls their initialisation
    * functions.
    *
    * After a call to ScanDevices() adi->GetDeviceList() returns a list of all
    * found devices along with their error states.  
    *
    * @return DAL_SUCCESS if no errors occured, DAL_FAILURE otherwise
    */
   int32_t (*ScanDevices)(void) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * @brief Creates a list of the devices managed by the DAL.
    * @param listCapacity The number of devices fitting in the supplied deviceList.
    * @param deviceList This list is filled with up to listCapacity devices.
    * @param deviceNumber The number of devices available.
    * @return DAL_SUCCESS
    */
   int32_t (*GetDeviceList)(size_t listCapacity,
                            tDeviceInfo *deviceList,
                            size_t *deviceNumber) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Opens the device.
    * @param deviceId Id of the device.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*OpenDevice)(tDeviceId deviceId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Closes the device
    * @param deviceId Id of the device.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*CloseDevice)(tDeviceId deviceId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Checks whether the device is open or not.
    * @param deviceId Id of the device.
    * @return Returns true when device is open, false otherwise.
    */
   bool (*IsDeviceOpen)(tDeviceId deviceId) DAL_GNUC_WARN_UNUSED_RESULT;


   /**
    * Stores the name of the device in the supplied buffer.
    * @param[in] deviceId Id of the device.
    * @param[in] bufferSize Size of the bameBuffer
    * @param[out] nameBuffer Pointer to the buffer to store the name in.
    * @param[out] nameLength The resulting length of the string in nameBuffer.
    * @return Returns DAL_SUCCESS on success, DAL_FAILURE otherwise.
    */
   int32_t (*GetDeviceName)(tDeviceId deviceId,
                            size_t bufferSize,
                            char *nameBuffer,
                            size_t *nameLength) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Returns the devices flags
    * @param deviceId
    * @param flags Pointer to the flags
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*GetDeviceFlags)(tDeviceId deviceId,
                             uint32_t *flags) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Gets the sizes of the devices input and output.
    * @param deviceId Id of the device.
    * @param inputSize Pointer to where the size of the input will be stored.
    * @param outputSize Pointer to where the size of the output will be stored.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*GetIoSizes)(tDeviceId deviceId,
                         uint32_t* inputSize,
                         uint32_t* outputSize) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Configures a sub device.
    * @param deviceId Id of the device.
    * @param subdeviceId Id of the sub device.
    * @param configData The device specific configuration.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ConfigureSubdevice)(tDeviceId deviceId,
                                 int32_t subdeviceId,
                                 void *configData) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Configures a device.
    * @param deviceId Id of the device.
    * @param configData The device specific configuration.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ConfigureDevice)(tDeviceId deviceId,
                              void *configData) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Starts the writing of process data.
    * @param deviceId Id of the device.
    * @param taskId Id of the task.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*WriteStart)(tDeviceId deviceId,
                         uint32_t taskId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The WiteBit method writes one bit from data to the given offset.
    * @param deviceId The device to write the bit to.
    * @param bitOffset The bit offset to write the bit at.
    * @param data Pointer from where the bit will be written from.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*WriteBit)(tDeviceId deviceId,
                       uint32_t taskId,
                       uint32_t bitOffset,
                       uint8_t* data) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The WiteBool method writes one bit from data to the given offset.
    * @param deviceId The device to write the bit to.
    * @param bitOffset The bit offset to write the bit at.
    * @param value Pointer from where the bit will be written from.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*WriteBool)(tDeviceId deviceId,
                       uint32_t taskId,
                       uint32_t bitOffset,
                       bool value) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Writes size bytes from at the supplied offset to
    * the process images of the device.
    * @param deviceId Id of the device
    * @param offset Offset where the data will be written at.
    * @param size Size of the data to write.
    * @param data The data to write.
    * @return Returns 0 on success, -1 otherwise
    */
   int32_t (*WriteBytes)(tDeviceId deviceId,
                         uint32_t taskId,
                         uint32_t offset,
                         uint32_t size,
                         uint8_t* data) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Finishes the writing of process data. Usually this is the point
    * when the pi is committed to the device.
    * @param deviceId The id of the device.
    * @param taskId The id of the task.
    * @return Returns 0 on success, -1 otherwise
    */
   int32_t (*WriteEnd)(tDeviceId deviceId,
                       uint32_t taskId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Starts the reading of the pi.Usually this is the point when the pi
    * is read out from the device.
    * @param deviceId The id of the device.
    * @param taskId The id of the task.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ReadStart)(tDeviceId deviceId,
                        uint32_t taskId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The ReadBit method reads one bit from the given offset into data.
    * @param deviceId The device to read the bit from.
    * @param bitOffset The bit offset to read the bit at.
    * @param data Pointer to where the bit will be read to.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ReadBit)(tDeviceId deviceId,
                      uint32_t taskId,
                      uint32_t bitOffset,
                      uint8_t* data) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The ReadBool method reads one bit from the given offset into value.
    * @param deviceId The device to read the bit from.
    * @param bitOffset The bit offset to read the bit at.
    * @param data Pointer to where the bit will be read to.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ReadBool)(tDeviceId deviceId,
                      uint32_t taskId,
                      uint32_t bitOffset,
                      bool* value) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Reads size bytes at offset from the devices pi into data.
    * @param deviceId Id of the device
    * @param offset Offset at which the data will be read.
    * @param size Size of the data to read.
    * @param data Pointer to the buffer.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ReadBytes)(tDeviceId deviceId,
                        uint32_t taskId,
                        uint32_t offset,
                        uint32_t size,
                        uint8_t* data) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Finishes the reading of process data.
    * @param deviceId The id of the device.
    * @param taskId The if of the task.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*ReadEnd)(tDeviceId deviceId,
                      uint32_t taskId) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Get the state of the device (corresponds to codesys' bus).
    * @param[in] deviceId Id of the device.
    * @param[in] bufferSize Size of the supplied buffer.
    * @param[out] diagnoseBuffer Buffer where the state is stored in.
    * @param[out] busState The state of the bus.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*DiagnoseGetDeviceState)(tDeviceId deviceId,
                                     uint32_t bufferSize,
                                     uint8_t *diagnoseBuffer,
                                     tBusState *busState) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Get the state of a subdevice (corresponds to codesys' device).
    * @param deviceId Id of the device.
    * @param subdeviceId Id of the device to get the state from.
    * @param[in] bufferSize Size of the supplied buffer.
    * @param[out] diagnoseBuffer Buffer where the state data is stored in.
    * @param[out] diagnoseState The state of the diagnose.
    * @return Returns 0 on success, -1 otherwise.
    */
   int32_t (*DiagnoseGetSubdeviceState)(tDeviceId deviceId,
                                        int32_t subdeviceId,
                                        size_t bufferSize,
                                        uint8_t* diagnoseBuffer,
                                        tDiagnoseState *diagnoseState) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The RegisterEventCallback method registers a callback function,
    * which will get called in case the given device generates an event.
    * @param deviceId The device to register the callback for.
    * @param eventCallback The callback function.
    * @return Returns 0 on success, -1 otherwise.
    * @see URL#generateUrl:fromParams:UnregisterEventCallback
    */
   int32_t (*RegisterEventHandler)(tDeviceId deviceId,
                                   tEventHandler handler,
                                   void *userData) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The UnregisterEventCallback method unregisters a previously
    * registered callback function.
    * @param deviceId The device to unregister the callback for.
    * @param eventCallback The callback to unregister.
    * @return Returns 0 on success, -1 otherwise.
    * @see URL#generateUrl:fromParams:RegisterEventCallback
    */
   int32_t (*UnregisterEventHandler)(tDeviceId deviceId,
                                     tEventHandler handler) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * The GetLastError method gets the last error set by the given device.
    * @param deviceId The device to get the error from.
    * @return Returns the error.
    */
   int32_t (*GetLastError)(tDeviceId ,tError *error) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Sets the state of the PLC application. Its up to the devices to react accordingly.
    * @param state The state of the application.
    * @return DAL_SUCCESS on success.
    *         DAL_FAILURE when at least one device returned an error.
    */
   int32_t (*ApplicationStateChanged)(tApplicationStateChangedEvent event) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * @brief Calls a device-specific function implemented by a device library.
    *
    * @param fnName  Name of the function to invoke
    * @param retVal  Return value
    * @param ...     Additional parameters
    * @return DAL_SUCCESS if the function was invoked successfully
    *         DAL_FAILURE on error
    *         DAL_NOTUSED if the function was not found
    */
   int32_t (*CallDeviceSpecificFunction)(const char *fnName,
                                         void *retVal,
                                         ...) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * @brief Calls a device-specific function implemented by a device library.
    *
    * @param fnName  Name of the function to invoke
    * @param retVal  Return value
    * @param ...     Additional parameters
    * @return DAL_SUCCESS if the function was invoked successfully
    *         DAL_FAILURE on error
    *         DAL_NOTUSED if the function was not found
    */
   int32_t (*VCallDeviceSpecificFunction)(const char *fnName,
										  void *retVal,
										  va_list args) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Sets the watchdog time. The time until the watchdog triggers
    * is the multiplication of factor and timeout_us.
    * @param factor The factor specifies how often the timeout_us
    * has to elapse until the watchdog triggers.
    * @param timeout_us The timeout of the watchdog in microseconds.
    * @return Return DAL_SUCCESS on success, DAL_FAILURE otherwise.
    */
   int32_t (*WatchdogSetTime)(uint32_t factor,
                              uint32_t timeout_us) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Starts the watchdog.
    * @return DAL_SUCCESS on
    */
   int32_t (*WatchdogStart)(void) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Stops the watchdog.
    * @return Return DAL_SUCCESS on success, DAL_FAILURE otherwise.
    */
   int32_t (*WatchdogStop)(void) DAL_GNUC_WARN_UNUSED_RESULT;

   /**
    * Triggers the watchdog.
    * @return Return DAL_SUCCESS on success, DAL_FAILURE otherwise.
    */
   int32_t (*WatchdogTrigger)(void) DAL_GNUC_WARN_UNUSED_RESULT;

};

#endif

