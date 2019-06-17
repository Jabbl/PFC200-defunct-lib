/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/
#pragma once

#include "bacstr.h"
#include <stdbool.h>

/** Checks if the input password matches the device password.
@param password [in] Password to check as a BACnet CharacterString
@return Returns "true" if password was correct, otherwise "false.
*/
bool device_password_check(BACNET_CHARACTER_STRING* password);

/** Checks if the input password matches the device password.
@param password [in] Password to check
@return Returns "true" if password was correct, otherwise "false.
*/
bool device_password_check_ansi(const char* password);
