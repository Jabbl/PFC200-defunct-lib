/**************************************************************************
* Copyright (C) 2018 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "codesys.h"
#include "TestLib.h"
#include <stdio.h>
#include <stdlib.h>

#define ADD_FUNC(func) { #func, (void (*)(void))func}
#define END_OF_TABLE  { "", NULL }

/**
 * Table containing the functions implemented by this lib.
 * The functions are matched via their name by the runtime (codesys).
 * Note that the function table must be finished with an empty string
 * and a NULL function pointer.
 */
static tWideExtRef s_ft[] =
{
	ADD_FUNC(FB_TESTFUNCTIONBLOCKinit),
	ADD_FUNC(FB_TESTFUNCTIONBLOCK),
	ADD_FUNC(F_TESTFUNCTION),
    END_OF_TABLE,
};

// Local prototypes
static tWideExtRef* cld_GetFunctionTable(void);


/** Called from CodeSys when library is opened (PLC boot, before PLC program is loaded)
@return CLD_SUCCESS in case of success, CLD_FAILURE in case of fail
*/
int32_t libbacnet_open(tWideInterface *me, void const * const dont_use1, void const * const dont_use2)
{
	/**
	* The Open function is called after the library has been loaded.
	* Any initialization code should be placed here, mainly setting
	* up the v-table (tCodesysLib).
	*
	*/
	(void)dont_use1;
    (void)dont_use2;

    // Setup v-table
    me->GetExternalTextReferenceTable = cld_GetFunctionTable;
	me->Close = libbacnet_close;
	me->ProcessHook = cld_CoDeSysEventHook;

	// Initialize the BACnet stack
	if (true)
	{
		// Lib was initialized successfully.
		return WIDE_SUCCESS;
	}
	else
	{
		// When CLD_FAILURE is returned the library will get unloaded immediately after this call.
		// In the failure case make sure no ressources are still in use (memory, files, threads, etc)! 
		return 2;  // CLD_FAILURE = 2  (WIDE_FAILURE = -1)
	}
}


/** Called from CodeSys when library is closed. Not sure when this is called.
@return CLD_SUCCESS in case of success, CLD_FAILURE in case of fail
*/
int32_t libbacnet_close(void)
{
	/**
	*  The Close function gets called when codesys is shutting down.
	*  Any ressources used by the library should be released here.
	*/

	/* Cleanup ressources here */
	/* Attention: Make sure that threads are really finished (via pthread_join for example).
	*            Otherwise your likely to get a segmentation fault. These are somewhat hard
	*            to find because the .so is unloaded immediately after the call to Close, thus
	*            the symbols are not available anymore.
	*/
	return WIDE_SUCCESS;
}


/** Called from CodeSys when a CodeSys event happens, such as Reset, Program Download etc...
@return CLD_SUCCESS if eventhandler succeeded
*/
uint32_t cld_CoDeSysEventHook(uint32_t hook, uint32_t info)
{
	/*
	-- Function: CoDeSysEventHook ------------------------------------------------------------

	Handle Codesys Hooks

	\param hook Number of Hook
	\param info additional info to the hook

	return 0 if nothing happens otherwise hook specific values
	------------------------------------------------------------------------------
	*/

	// Before reset or cold reset
	if (hook == WPH_BEFORE_RESET)
	{
	}

	/* Before reset or cold reset */
	/* Stop the server and also invalidate all CodeSys objects. Also free dynamic objects. */
	if (hook == WPH_AFTER_RESET)
	{
	}

	/* Before full download */
	/* Stop the server and also invalidate all CodeSys objects. Also free dynamic objects. */
	if ((hook == WPH_BEFORE_PROGRAM_DOWNLOAD) && (info == 1))
	{
	}

	/* Before online change */
	/* Just invalidate the objects, but still continue to keep the server running */
	/* When Online Change is done, the CodeSys library will automatically re-validate the pointers. */
	/* Do not free dynamic objects. */
	if ((hook == WPH_BEFORE_PROGRAM_DOWNLOAD) && (info == 0))
	{
	}

	/* After full download */
	/* Stop the server and also invalidate all CodeSys objects. Also free dynamic objects. */
	if ((hook == WPH_AFTER_PROGRAM_DOWNLOAD) && (info == 1))
	{
		// NOTE: This event is also called on PLC boot, not only when PLC is downloaded using CodeSys.
	}

	/* After online change */
	/* Just invalidate the objects, but still continue to keep the server running */
	/* When Online Change is done, the CodeSys library will automatically re-validate the pointers. */
	/* Do not free dynamic objects. */
	if ((hook == WPH_AFTER_PROGRAM_DOWNLOAD) && (info == 0))
	{
		// NOTE: This event is also called on PLC boot, not only when PLC is downloaded using CodeSys.
	}


	return WIDE_SUCCESS;
}


/**
* The GetFunctionTable function is called to retrieve the functions implemented by this lib.
*/
static tWideExtRef* cld_GetFunctionTable(void)
{
	return s_ft;
}
