#include "TestLib.h"
#include "starter.h"

/* The implemenation templates */
BOOL F_PROCESS(void)
{
	return run_service();
}

BOOL F_TESTFUNCTION(BOOL XINPUTparam)
{
	return !XINPUTparam;
}

void FB_TESTFUNCTIONBLOCK(FB_TESTFUNCTIONBLOCKtyp* inst)
{
	if (inst->XINVAR)
	{
		inst->ROUTVAR = (REAL)(inst->RINVAR * 3.1415);
		inst->XOUTVAR = (0x01 << inst->WINVAR);
	}
	else
	{
		inst->ROUTVAR = inst->WINVAR * (REAL)(inst->RINVAR / 2.71828);
		inst->XOUTVAR = !inst->XINVAR;
	}
}

BOOL FB_TESTFUNCTIONBLOCKinit(FB_TESTFUNCTIONBLOCKtyp* inst, BOOL bRetain)
{
	/* Initializing Function Block components */
	inst->XINVAR = FALSE;
	inst->RINVAR = 0.000000E+000;
	inst->WINVAR = 0;
	inst->XOUTVAR = FALSE;
	inst->ROUTVAR = 0.000000E+000;
	if (bRetain)
		return bRetain;

	/* Initalize the retain variables only if bRetain is FALSE */
	return bRetain;
}

