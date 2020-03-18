#include "select_screen.h"
//#include "..\engine\asm_manager.h"
#include "..\engine\audio_manager.h"
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

static unsigned char event_stage;

void screen_select_screen_load()
{
	struct_state_object *st = &global_state_object;

	// TODO delete
	if( st->state_object_mydebugger )
	{
		engine_content_manager_load_tiles_game();
		engine_content_manager_load_tiles_screen();

		engine_board_manager_border( border_type_game );
		engine_board_manager_side_tile();
	}
	// TODO delete

	engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
	engine_level_manager_draw_level();
	engine_level_manager_draw_middle();

	engine_delay_manager_load( SOUND_SCREEN_DELAY  );
	st->state_object_curr_screen = screen_type_select;
	st->state_object_next_screen = screen_type_select;
	event_stage = event_stage_start;
}

void screen_select_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input;
	unsigned char check;
	unsigned char delay;
	check = 0;

	if( event_stage_pause == event_stage )
	{
		//if( screen_type_select == st->state_object_next_screen )
		//{
		//	engine_enemy_manager_draw();
		//	engine_gamer_manager_draw();
		//}

		delay = engine_delay_manager_update();
		if( delay )
		{
			*screen_type = st->state_object_next_screen;
			return;
		}

		// TODO delete Draw sprites last.
		//engine_enemy_manager_draw();
		//engine_gamer_manager_draw();
	}

	// Draw sprites last.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	//input = engine_input_manager_hold( input_type_left );
	//if( input )
	//{
	//	check = 1;
	//	if( st->state_object_round_data == 0 )
	//	{
	//		st->state_object_round_data = MAX_ROUNDS - 1;
	//	}
	//	else
	//	{
	//		st->state_object_round_data--;
	//	}
	//}

	//input = engine_input_manager_hold( input_type_down );
	//if( input )
	//{
	//	check = 1;
	//	if( st->state_object_world_data == 0 )
	//	{
	//		st->state_object_world_data = MAX_WORLDS - 1;
	//	}
	//	else
	//	{
	//		st->state_object_world_data--;
	//	}
	//}

	//input = engine_input_manager_hold( input_type_right );
	//if( input )
	//{
	//	check = 1;
	//	st->state_object_round_data++;
	//	if( st->state_object_round_data >= MAX_ROUNDS )
	//	{
	//		st->state_object_round_data = 0;
	//	}
	//}

	//input = engine_input_manager_hold( input_type_up );
	//if( input )
	//{
	//	check = 1;
	//	st->state_object_world_data++;
	//	if( st->state_object_world_data >= MAX_WORLDS )
	//	{
	//		st->state_object_world_data = 0;
	//	}
	//}

	//if( check )
	//{
	//	engine_score_manager_update_level();
	//	engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
	//	engine_level_manager_draw_level();
	//	engine_level_manager_draw_middle();
	//}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		engine_audio_manager_sfx_play( sound_type_accept );
		st->state_object_next_screen = screen_type_init;
		event_stage = event_stage_pause;
		return;
	}

	input = engine_input_manager_hold( input_type_fire2 );
	if( input )
	{
		engine_audio_manager_sfx_play( sound_type_reset );
		st->state_object_next_screen = screen_type_option;
		event_stage = event_stage_pause;
		return;
	}

	// Draw sprites last.
	//engine_enemy_manager_draw();
	//engine_gamer_manager_draw();

	*screen_type = st->state_object_curr_screen;
}
