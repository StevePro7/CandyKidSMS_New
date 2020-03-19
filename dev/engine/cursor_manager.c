#include "cursor_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "input_manager.h"
#include "locale_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

#define GRANT_OFFSET	14

static unsigned char type1_cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };
static unsigned char type2_cursorY[ MAX_ACTORS ] = { TEXT1_Y, TEXT2_Y, TEXT3_Y, TEXT4_Y };
static unsigned char menu_cursor[ 2 ];

void engine_cursor_manager_init()
{
	menu_cursor[ menu_type_option ] = 0;
	menu_cursor[ menu_type_select ] = 0;
}

void engine_cursor_manager_update1( unsigned char index )
{
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, TYPE1_OPT1_X, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, TYPE1_OPT2_X, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_ARROWS, type1_cursorX[ index ], TYPE1_TEXT_Y + 1 );
}

void engine_cursor_manager_update2( unsigned char index )
{
	unsigned char input[ 2 ] = { 0, 0 };
	input[ 0 ] = engine_input_manager_hold( input_type_up );
	input[ 1 ] = engine_input_manager_hold( input_type_down );

	if( input[ 0 ] || input[ 1 ] )
	{
		if( input[ 0 ] )
		{
			if( menu_cursor[ index ] <= 0 )
			{
				menu_cursor[ index ] = NUM_DIRECTIONS - 1;
			}
			else
			{
				menu_cursor[ index ]--;
			}
		}
		else
		{
			if( input[ 1 ] )
			{
				if( menu_cursor[ index ] >= NUM_DIRECTIONS - 1 )
				{
					menu_cursor[ index ] = 0;
				}
				else
				{
					menu_cursor[ index ]++;
				}
			}
		}

		engine_cursor_manager_draw2( index );
	}
}

void engine_cursor_manager_draw1( unsigned char index )
{
	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_menus[ index + 0 ], TYPE1_TEXT_X, TYPE1_TEXT_Y + 0 );
	engine_font_manager_draw_text( locale_object_menus[ index + 1 ], TYPE1_TEXT_X + 2, TYPE1_TEXT_Y + 1 );
	engine_font_manager_draw_text( locale_object_menus[ index + 2 ], TYPE1_TEXT_X + 13, TYPE1_TEXT_Y + 1 );
}

void engine_cursor_manager_draw2( unsigned char index )
{
	unsigned char cursor;
	unsigned char yValue;
	unsigned char loop;

	for( loop = 0; loop < NUM_DIRECTIONS; loop++ )
	{
		yValue = type2_cursorY[ loop ] + 1;
		engine_font_manager_draw_text( LOCALE_SELECT_SPACES, DATA_X - 4, yValue );
	}

	cursor = menu_cursor[ index ];
	yValue = type2_cursorY[ cursor ] + 1;
	engine_font_manager_draw_text( LOCALE_SELECT_ARROWS, DATA_X - 4, yValue );
}

void engine_cursor_manager_draw_titles( unsigned char index )
{
	unsigned char delta;
	unsigned char loops;
	unsigned char *title;

	delta = GRANT_OFFSET * index;
	devkit_SMS_mapROMBank( FIXED_BANK );

	engine_font_manager_draw_text( locale_object_grants[ delta + 0 ], TEXT_X, TEXT0_Y + 0 );
	engine_font_manager_draw_text( locale_object_grants[ delta + 1 ], TEXT_X, TEXT0_Y + 1 );

	for( loops = 0; loops < MAX_ACTORS; loops++ )
	{
		index = delta + 2 + loops * 3;
		title = ( unsigned char * ) locale_object_grants[ index ];

		engine_font_manager_draw_text( title, DATA_X - 3, type2_cursorY[ loops ] );
	}
}

//void engine_cursor_manager_draw_title1()
//{
//	unsigned char index;
//	unsigned char loops;
//	unsigned char *actor;
//	devkit_SMS_mapROMBank( FIXED_BANK );
//
//	engine_font_manager_draw_text( locale_object_option[ 0 ], TEXT_X, TEXT0_Y + 0 );
//	engine_font_manager_draw_text( locale_object_option[ 1 ], TEXT_X, TEXT0_Y + 1 );
//
//	for( loops = 0; loops < MAX_ACTORS; loops++ )
//	{
//		index = 2 + loops * 3;
//		actor = ( unsigned char * ) locale_object_option[ index ];
//
//		engine_font_manager_draw_text( actor, DATA_X - 3, type2_cursorY[ loops ] );
//	}
//}

//void engine_cursor_manager_draw_title2()
//{
//	unsigned char index;
//	unsigned char loops;
//	unsigned char *actor;
//	devkit_SMS_mapROMBank( FIXED_BANK );
//
//	engine_font_manager_draw_text( locale_object_select[ 0 ], TEXT_X, TEXT0_Y + 0 );
//	engine_font_manager_draw_text( locale_object_select[ 1 ], TEXT_X, TEXT0_Y + 1 );
//
//	for( loops = 0; loops < MAX_ACTORS; loops++ )
//	{
//		index = 2 + loops * 3;
//		actor = ( unsigned char * ) locale_object_select[ index ];
//		engine_font_manager_draw_text( actor, DATA_X - 3, type2_cursorY[ loops ] );
//	}
//}

void engine_cursor_manager_draw_grant1( unsigned char index, unsigned char delta, unsigned char x, unsigned char y )
{
	unsigned char *title;
	index = GRANT_OFFSET * index + delta;
	devkit_SMS_mapROMBank( FIXED_BANK );
	title = ( unsigned char * ) locale_object_grants[ index ];
	engine_font_manager_draw_text( title, x, y );
}

void engine_cursor_manager_draw_grant2( unsigned char index, unsigned char delta, unsigned char value )
{
	engine_cursor_manager_draw_grant1( index, delta, DATA_X - 2, type2_cursorY[ value ] + 1 );
}

//void engine_cursor_manager_draw_option1( unsigned char index, unsigned char x, unsigned char y )
//{
//	unsigned char *title = ( unsigned char * ) locale_object_option[ index ];
//	devkit_SMS_mapROMBank( FIXED_BANK );
//	engine_font_manager_draw_text( title, x, y );
//	
//}
//void engine_cursor_manager_draw_option2( unsigned char index, unsigned char actor )
//{
//	engine_cursor_manager_draw_option1( index, DATA_X - 3, type2_cursorY[ actor ] + 1 );
//}

//void engine_cursor_manager_draw_select1( unsigned char index, unsigned char x, unsigned char y )
//{
//	unsigned char *title = ( unsigned char * ) locale_object_select[ index ];
//	devkit_SMS_mapROMBank( FIXED_BANK );
//	engine_font_manager_draw_text( title, x, y );
//}
//void engine_cursor_manager_draw_select2( unsigned char index, unsigned char actor )
//{
//	engine_cursor_manager_draw_select1( index, DATA_X - 3, type2_cursorY[ actor ] + 1 );
//}

unsigned char engine_cursor_manager_get_cursor( unsigned char index )
{
	return menu_cursor[ index ];
}