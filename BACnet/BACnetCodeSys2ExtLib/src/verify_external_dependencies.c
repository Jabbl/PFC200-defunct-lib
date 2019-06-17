
/*	The entire purpose of this file is to link it with "libbacnet.so" to create "libbacnet.check.bin".
	This throws an error at compile-time if any external dependencies are missing causing library crash on PLC startup.

	This file is not compiled into the .so / Shared Library.
*/
int main(void)
{
	// 
	return 0;
}
