#include "load_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

#define LOAD_SCREEN_DELAY	150

static void print_level();

void screen_load_screen_load()
{
	state_object_curr_screen = screen_type_load;
	state_object_next_screen = screen_type_ready;

	engine_delay_manager_load( LOAD_SCREEN_DELAY );

	// Reset all score data.
	engine_score_manager_load();

	engine_level_manager_load_level( state_object_world_data, state_object_round_data );
	// IMPORTANT do not display Off / On here as looks better to load level over border.
	//devkit_SMS_displayOff();
	engine_level_manager_draw_level();
	//devkit_SMS_displayOn();

	print_level();
}

void screen_load_screen_update( unsigned char *screen_type )
{
//	engine_memo_manager_draw
	unsigned char delay;
	unsigned char input;

	delay = engine_delay_manager_update();
	input = engine_input_manager_hold( input_type_fire1 );
	if( delay || input )
	{
		*screen_type = state_object_next_screen;
		return;
	}

	*screen_type = state_object_curr_screen;
}

static void print_level()
{
	unsigned char world = state_object_world_data + 1;
	unsigned char round = state_object_round_data + 1;

	engine_board_manager_midd_text();
	engine_font_manager_draw_data( world, SCREEN_TILE_LEFT + 15, 11 );
	engine_font_manager_draw_data( round, SCREEN_TILE_LEFT + 15, 12 );

	if( world < 10 )
	{
		engine_font_manager_draw_char( '0', SCREEN_TILE_LEFT + 14, 11 );
	}
	if( round < 10 )
	{
		engine_font_manager_draw_char( '0', SCREEN_TILE_LEFT + 14, 12 );
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_texts[ 8 ], SCREEN_TILE_LEFT + 8, 11 );
	engine_font_manager_draw_text( locale_object_texts[ 9 ], SCREEN_TILE_LEFT + 8, 12 );

}