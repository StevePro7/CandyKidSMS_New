#include "cursor_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "input_manager.h"
#include "locale_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

static unsigned char type1_cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };
static unsigned char type2_cursorY[ MAX_ACTORS ] = { TEXT1_Y, TEXT2_Y, TEXT3_Y, TEXT4_Y };
static unsigned char menu_cursor[ 2 ];

void engine_cursor_manager_init()
{
	menu_cursor[ menu_type_option ] = 0;
	menu_cursor[ menu_type_select ] = 0;
}

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

void engine_cursor_manager_draw_titles()
{
	unsigned char index;
	unsigned char loops;
	unsigned char *actor;
	devkit_SMS_mapROMBank( FIXED_BANK );

	engine_font_manager_draw_text( locale_object_option[ 0 ], TEXT_X, TEXT0_Y + 0 );
	engine_font_manager_draw_text( locale_object_option[ 1 ], TEXT_X, TEXT0_Y + 1 );

	for( loops = 0; loops < MAX_ACTORS; loops++ )
	{
		index = 2 + loops * 3;
		actor = ( unsigned char * ) locale_object_option[ index ];

		engine_font_manager_draw_text( actor, DATA_X - 2, type2_cursorY[ loops ] );
	}
}

void engine_cursor_manager_draw_option( unsigned char index, unsigned char x, unsigned char y )
{
	unsigned char *title = ( unsigned char * ) locale_object_option[ index ];
	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( title, x, y );
	
}
void engine_cursor_manager_draw_option2( unsigned char index, unsigned char actor )
{
	engine_cursor_manager_draw_option( index, DATA_X - 2, type2_cursorY[ actor ] + 1 );
}