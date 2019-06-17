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

/** Initialize the BACnet server for CodeSys v2.3
*/
bool server_codesys23_init(void);

/** Stops and cleans up all resources used by the BACnet server for CodeSys v2.3
*/
void server_codesys23_cleanup(void);

/** Resets the state of the BACnet server to an initial stopped state.
*/
void server_codesys23_reset(bool online_change);

/** Call when user is about to download PLC program.
*/
void server_codesys23_plc_program_before_download(void);

/** Sets if we should inhibits calls from CodeSys to library functions while reset/program download is in progress
*/
static inline bool server_codesys23_get_driver_inhibited(void)
{
	extern bool CodeSys_DownloadBegun;
	return CodeSys_DownloadBegun;
}

/** Sets if we should inhibits calls from CodeSys to library functions while reset/program download is in progress
*/
static inline void server_codesys23_set_driver_inhibited(bool inhibited)
{
	extern bool CodeSys_DownloadBegun;
	CodeSys_DownloadBegun = inhibited;
}
