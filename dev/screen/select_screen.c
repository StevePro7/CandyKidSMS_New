#include "select_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

void screen_select_screen_load()
{
	state_object_curr_screen = screen_type_select;
	//state_object_next_screen = screen_type_option;
	state_object_next_screen = screen_type_init;

	//if( state_object_mydebugger )
	//{
	//	engine_asm_manager_clear_VRAM();
	//	engine_content_manager_load_tiles_font();
	//	engine_content_manager_load_tiles_game();
	//	engine_content_manager_load_sprites_game();
	//}

	// TODO delete as this comes after option screen.
	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();
	//engine_board_manager_draw_full();
	//engine_board_manager_draw_exit();
	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();
	// TODO delete as this comes after option screen.

	engine_level_manager_load_level( state_object_world_data, state_object_round_data );
	engine_level_manager_draw_level();
	engine_level_manager_draw_middle();

	//engine_locale_manager_draw_text( 1, SCREEN_TILE_LEFT + LFT_SIDE_X + 24, TOP_SIDE_Y + 0 );
	//engine_locale_manager_draw_text( 2, SCREEN_TILE_LEFT + LFT_SIDE_X + 24, TOP_SIDE_Y + 1 );

	//engine_locale_manager_draw_text( 10, SCREEN_TILE_LEFT + LFT_SIDE_X + 24, TOP_SIDE_Y + 4 );
	//engine_locale_manager_draw_text(  6, SCREEN_TILE_LEFT + LFT_SIDE_X + 24, TOP_SIDE_Y + 5 );
}

void screen_select_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	unsigned char check;
	check = 0;

	input = engine_input_manager_hold( input_type_left );
	if( input )
	{
		check = 1;
		if( state_object_round_data == 0 )
		{
			state_object_round_data = MAX_ROUNDS - 1;
		}
		else
		{
			state_object_round_data--;
		}
	}

	input = engine_input_manager_hold( input_type_down );
	if( input )
	{
		check = 1;
		if( state_object_world_data == 0 )
		{
			state_object_world_data = MAX_WORLDS - 1;
		}
		else
		{
			state_object_world_data--;
		}
	}

	input = engine_input_manager_hold( input_type_right );
	if( input )
	{
		check = 1;
		state_object_round_data++;
		if( state_object_round_data >= MAX_ROUNDS )
		{
			state_object_round_data = 0;
		}
	}

	input = engine_input_manager_hold( input_type_up );
	if( input )
	{
		check = 1;
		state_object_world_data++;
		if( state_object_world_data >= MAX_WORLDS )
		{
			state_object_world_data = 0;
		}
	}

	if( check )
	{
		engine_score_manager_update_level();
		engine_level_manager_load_level( state_object_world_data, state_object_round_data );
		engine_level_manager_draw_level();
		engine_level_manager_draw_middle();
	}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		*screen_type = state_object_next_screen;
		return;
	}

	*screen_type = screen_type_select;
}
