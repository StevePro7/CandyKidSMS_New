#include "locale_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

//void engine_locale_manager_draw_text( unsigned char *text, unsigned char x, unsigned char y )
void engine_locale_manager_draw_text( unsigned char index, unsigned char x, unsigned char y )
{
	const unsigned char *text = locale_object_texts[ index ];
	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( text, x, y );
}