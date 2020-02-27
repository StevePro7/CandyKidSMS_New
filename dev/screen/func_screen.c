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

static unsigned char first_time;

void screen_func_screen_load()
{
	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();

	engine_font_manager_draw_text( "FUNC SCREEN", 10, 2 );
}

void screen_func_screen_update( unsigned char *screen_type )
{
	unsigned char input;

	input = engine_input_manager_hold( input_type_up );
	if( input )
	{
		engine_score_manager_update_oneup();
		//engine_score_manager_update_bonus( tile_type_bonusA );

	}
	input = engine_input_manager_hold( input_type_down );
	if( input )
	{
		//engine_score_manager_update_bonus( tile_type_bonusB );
		engine_score_manager_update_lives( -1 );

	}
	input = engine_input_manager_hold( input_type_left );
	if( input )
	{
		engine_score_manager_update_candy();
	}
	input = engine_input_manager_hold( input_type_right );
	if( input )
	{
		engine_score_manager_update_bonus( tile_type_bonusD );
		//engine_score_manager_update_bonus( tile_type_bonusD );
	}

	//input = engine_input_manager_hold( input_type_fire1 );
	input = engine_input_manager_move( input_type_fire1 );
	if( input )
	{
		engine_score_manager_update_boost();
		//engine_score_manager_update_candy();
	}

	//first_time = 0;
	*screen_type = screen_type_func;
}