#include "starter.h"

uint32_t runner(void);

bool run_service(void)
{
	if (runner() > 0)
		return true;
	else
		return false;
}
