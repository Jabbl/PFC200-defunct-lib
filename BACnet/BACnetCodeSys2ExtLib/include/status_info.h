/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

/** This module handles statistic data from BACnet module to the CodeSys struct for debug purposes
**/
#pragma once

#include "external_lib_structs.h"


/** Set CodeSys instance to write statistical data to.
This buffer is invalidated once PLC program download starts because memory may have moved.
@param pInstance [in] Instance data
*/
void status_info_set_instance(BACNET_STATUS_INFO_OBJECTtyp* pInstance);

/** Update the currently registered CodeSys instance
*/
void status_info_update(void);
