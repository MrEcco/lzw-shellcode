// Some fck becose Visual Studio 2015 cant create native C applications, 
// but can recognize *.c and *.h file like C-coded files
// For Linux use makefile
#ifdef __WINDOWS__
#include <windows.h>
#endif
#include "lzw_c.h"

int main(int argc, char * argv[])
{
	return c_main(argc, argv);
}
