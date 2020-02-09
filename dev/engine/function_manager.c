#include "function_manager.h"

void engine_function_manager_foo()
{
}

void engine_function_manager_convertXYtoZ( unsigned char divide, unsigned char x, unsigned char y, unsigned char *z )
{
	*z = y * divide + x;
}
void engine_function_manager_convertZtoXY( unsigned char divide, unsigned char z, unsigned char *x, unsigned char *y )
{
	*x = z % divide;
	*y = z / divide;
}