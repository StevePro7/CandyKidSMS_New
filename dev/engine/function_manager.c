#include "function_manager.h"
#include "..\devkit\_sms_manager.h"

// Bank changer
unsigned char lastbank;

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

// TODO change this function name.
void changeBank( unsigned char b )
{
	if( b != lastbank )
	{
		devkit_SMS_mapROMBank( b );
		lastbank = b;
	}
}