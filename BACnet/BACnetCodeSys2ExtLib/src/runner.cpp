
#include "runner.h"
#include "cpp/appDataValue2.h"
#include "cpp/OctetString.h"


uint32_t runner(void)
{
	return cpp_runner();
}

bool cpp_runner(void)
{

	OctetString* value = new OctetString;

	(void)value;

	return true;
}
