#include "func_screen.h"
#include "..\engine\board_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
//#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
//#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
//#include "..\engine\storage_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"

// FUNC screen - is the main command playback driver
// Assumes that commands have already been saved to SRAM
static unsigned char first_time;

void screen_func_screen_load()
{
	//engine_command_manager_init();
	//engine_delay_manager_load( 0 );

	engine_board_manager_init();
	//engine_gamer_manager_init();
	//engine_enemy_manager_init();

	engine_score_manager_load();

	// Draw functions.
	//engine_board_manager_debugger();
	//engine_board_manager_draw_full();
	engine_board_manager_debugger();
	//engine_board_manager_draw_exit();

	//engine_font_manager_draw_text( "FUNC SCREEN!!", 4, 10 );
	engine_score_manager_draw_all();
	engine_score_manager_draw_text();
	first_time = 1;
}

void screen_func_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	input = engine_input_manager_hold( input_type_up );
	if( input )
	{
		engine_score_manager_update_bonus( tile_type_bonusA );
	}
	input = engine_input_manager_hold( input_type_down );
	if( input )
	{
		engine_score_manager_update_bonus( tile_type_bonusB );
	}
	input = engine_input_manager_hold( input_type_left );
	if( input )
	{
		engine_score_manager_update_bonus( tile_type_bonusC );
	}
	input = engine_input_manager_hold( input_type_right );
	if( input )
	{
		engine_score_manager_update_bonus( tile_type_bonusD );
	}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		engine_score_manager_update_candy();
	}

	first_time = 0;
	*screen_type = screen_type_func;
}