
#include "runner.h"

// Bridge between C and C++ code
void runner(void)
{
	cpp_runner();
}

// Defunct C++ runner
void cpp_runner(void)
{
	uint32_t* value = new uint32_t(16); // This valid C++ line seems to be causing problems

	(void)value;

	delete value;
}

//// Working C++ runner
//void cpp_runner(void)
//{
//	uint32_t value = 16;
//
//	(void)value;
//}
