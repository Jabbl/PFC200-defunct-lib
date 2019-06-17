
#include "runner.h"

// Bridge between C and C++ code
void runner(void)
{
	cpp_runner();
}

// Actual C++ runner
void cpp_runner(void)
{
	uint32_t* value = new uint32_t(16); // This valid C++ line seems to be causing problems

	(void)value;
}
