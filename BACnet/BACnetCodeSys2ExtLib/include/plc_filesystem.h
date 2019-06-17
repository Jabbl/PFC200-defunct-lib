/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/
#pragma once

#include <stdbool.h>

/** Initializes the filepaths needed for this BACnet driver to run on the Wago system.
*/
void plc_filesystem_init(void);

/** Gets if the Linux system on this Wago system has been booted from the SD- card.
*/
bool plc_filesystem_is_linux_booted_from_sd_card(void);
