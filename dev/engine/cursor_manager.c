#include "cursor_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "input_manager.h"
#include "locale_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

//#define TYPE1_TEXT_X			SCREEN_TILE_LEFT + 7
//#define TYPE1_TEXT_Y			18
//#define TYPE1_OPT1_X			TYPE1_TEXT_X + 0
//#define TYPE1_OPT2_X			TYPE1_TEXT_Y + 11
//
//static unsigned char type1_cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };

static unsigned char type1_cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };

void engine_cursor_manager_cursor1( unsigned char index )
{
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, TYPE1_OPT1_X, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, TYPE1_OPT2_X, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_ARROWS, type1_cursorX[ index ], TYPE1_TEXT_Y + 1 );
}

void engine_cursor_manager_draw1( unsigned char index )
{
	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_menus[ index + 0 ], TYPE1_TEXT_X, TYPE1_TEXT_Y + 0 );
	engine_font_manager_draw_text( locale_object_menus[ index + 1 ], TYPE1_TEXT_X + 2, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( locale_object_menus[ index + 2 ], TYPE1_TEXT_X + 13, TYPE1_TEXT_Y + 1 );
}