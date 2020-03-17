#include "select_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

void screen_select_screen_load()
{
	struct_state_object *st = &global_state_object;
	state_object_curr_screen = screen_type_select;
	//state_object_next_screen = screen_type_option;
	state_object_next_screen = screen_type_init;

	engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
	engine_level_manager_draw_level();
	engine_level_manager_draw_middle();
}

void screen_select_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input;
	unsigned char check;
	check = 0;

	input = engine_input_manager_hold( input_type_left );
	if( input )
	{
		check = 1;
		if( st->state_object_round_data == 0 )
		{
			st->state_object_round_data = MAX_ROUNDS - 1;
		}
		else
		{
			st->state_object_round_data--;
		}
	}

	input = engine_input_manager_hold( input_type_down );
	if( input )
	{
		check = 1;
		if( st->state_object_world_data == 0 )
		{
			st->state_object_world_data = MAX_WORLDS - 1;
		}
		else
		{
			st->state_object_world_data--;
		}
	}

	input = engine_input_manager_hold( input_type_right );
	if( input )
	{
		check = 1;
		st->state_object_round_data++;
		if( st->state_object_round_data >= MAX_ROUNDS )
		{
			st->state_object_round_data = 0;
		}
	}

	input = engine_input_manager_hold( input_type_up );
	if( input )
	{
		check = 1;
		st->state_object_world_data++;
		if( st->state_object_world_data >= MAX_WORLDS )
		{
			st->state_object_world_data = 0;
		}
	}

	if( check )
	{
		engine_score_manager_update_level();
		engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
		engine_level_manager_draw_level();
		engine_level_manager_draw_middle();
	}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		*screen_type = state_object_next_screen;
		return;
	}

	// Draw sprites last.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_select;
}
