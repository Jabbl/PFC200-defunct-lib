
#include "wide/wide_api.h"

typedef struct
{
	BOOL XINVAR;
	REAL RINVAR;
	WORD WINVAR;
	BOOL XOUTVAR;
	REAL ROUTVAR;
}
FB_TESTFUNCTIONBLOCKtyp;


/* Enum definitions */

/* Enum 'ETEST' */
enum ETEST
{
	BANANA = 1,
	CHILI = 2,
	APPLE = 3 
};


/* The Prototypes */
BOOL F_TESTFUNCTION(BOOL XINPUTparam);
;
void FB_TESTFUNCTIONBLOCK(FB_TESTFUNCTIONBLOCKtyp* inst);
BOOL FB_TESTFUNCTIONBLOCKinit(FB_TESTFUNCTIONBLOCKtyp* inst, BOOL bRetain);
