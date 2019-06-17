#pragma once

#include <stdint.h>

// Extern c to allow calling from C-code
extern "C" void runner(void);

// Actual C++ runner
void cpp_runner(void);