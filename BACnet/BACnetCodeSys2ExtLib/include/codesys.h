/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

/** This module registers the methods used by CodeSys v2.3 External Library to connect to the PLC program.
**/
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "wide/wide_api.h"


/** Called from CodeSys when library is opened (PLC boot, before PLC program is loaded)
@return WIDE_SUCCESS in case of success, WIDE_FAILURE in case of fail
*/
int32_t libbacnet_open(tWideInterface *me, void const * const dont_use1, void const * const dont_use2);

/** Called from CodeSys when library is closed. Not sure when this is called.
@return WIDE_SUCCESS in case of success, WIDE_FAILURE in case of fail
*/
int32_t libbacnet_close(void);

/** Called from CodeSys when a CodeSys event happens, such as Reset, Program Download etc...
@return WIDE_SUCCESS if eventhandler succeeded
*/
uint32_t cld_CoDeSysEventHook(uint32_t hook, uint32_t info);
