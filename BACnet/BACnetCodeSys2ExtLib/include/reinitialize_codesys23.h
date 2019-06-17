/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

/** This module handles backup procedure through BACnet protocol.
**/
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bacenum.h"


/** Initializes reinitialize/backup/restore procedure handling.
*/
void reinitialize_codesys23_init(void);

/** Cleans up reinitialize/backup/restore procedure handling.
*/
void reinitialize_codesys23_cleanup(void);

/** Call periodically to update. This function may never return upon a reboot.
*/
void reinitialize_codesys23_update(void);

/** Force the system to perform a reinitialize now.
*/
bool reinitialize_codesys23_force(BACNET_REINITIALIZED_STATE state, BACNET_ERROR_DATA* out_error_data);

/** Gets the filepath where files will be backuped from and restored to. This is usually the CodeSys folder.
*/
const char* reinitialize_codesys23_get_backup_restore_path(void);

/** Gets the filepath to a file where files will be backuped from and restored to. This is usually in the CodeSys folder.
*/
const char* reinitialize_codesys23_get_backup_restore_filepath(char* buffer, size_t size_buffer, const char* filename);

/** Sets the filepath where files will be backuped from and restored to. This is usually the CodeSys folder.
@param path [in] - Absolute path without trailing /
*/
void reinitialize_codesys23_set_backup_restore_path(const char* path);
