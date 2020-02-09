#ifndef _FUNCTION_MANAGER_H_
#define _FUNCTION_MANAGER_H_

void engine_function_manager_foo();
void engine_function_manager_convertXYtoZ( unsigned char divide, unsigned char x, unsigned char y, unsigned char *z );
void engine_function_manager_convertZtoXY( unsigned char divide, unsigned char z, unsigned char *x, unsigned char *y );

void changeBank( unsigned char b );

#endif//_FUNCTION_MANAGER_H_