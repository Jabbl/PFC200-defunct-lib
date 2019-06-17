/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#pragma once

#include <stdbool.h>
#include <ldkc_kbus_information.h>

/** Called from native_objects.c to create the native objects for correct TerminalType of the given IO module
@param TerminalType [in] Type of terminal to create native objects for
@param RelPos [in] Relative position of to terminal in the IO stack of the same type (example type:555, 5 = 5th card of the type 555)
@param pTerminalInfo [in] Pointer to the terminal info
@return true if we recognized the IO module and were able to create native objects for it.
*/
bool native_io_modules_create(uint16_t TerminalType, uint16_t RelPos, tldkc_KbusInfo_TerminalInfo* pTerminalInfo);

