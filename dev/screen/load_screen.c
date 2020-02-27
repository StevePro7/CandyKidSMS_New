#include "load_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

// LOAD screen - test level manager load.
void screen_load_screen_load()
{
	engine_delay_manager_load( 0 );
	
	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( state_object_world_data, state_object_round_data );
	engine_level_manager_draw_level();
}

void screen_load_screen_update( unsigned char *screen_type )
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
	}

	*screen_type = screen_type_load;
}