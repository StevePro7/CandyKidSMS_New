#include "select_screen.h"
//#include "..\engine\asm_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"

// Private helper methods.
static void print_title();
//static void print_level();
static void print_trees();
static void print_exits();

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

		engine_memo_manager_option();
	}
	// TODO delete

	engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
	engine_level_manager_draw_level();
	engine_level_manager_draw_middle();

	//engine_cursor_manager_draw_title2();
	engine_cursor_manager_draw_titles( menu_type_select );
	//print_level();
	print_trees();
	print_exits();

	engine_cursor_manager_draw2( menu_type_select );
	engine_memo_manager_levels( 28, 5, 10 );

	engine_delay_manager_load( SOUND_SCREEN_DELAY + 10 );
	st->state_object_curr_screen = screen_type_select;
	st->state_object_next_screen = screen_type_select;
	event_stage = event_stage_start;
}

void screen_select_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input[ 2 ] = { 0, 0 };
	unsigned char cursor;
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

	engine_cursor_manager_update2( menu_type_select );

	// Draw sprites last.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	input[ 0 ] = engine_input_manager_hold( input_type_left );
	input[ 1 ] = engine_input_manager_hold( input_type_right );
	if( input[ 0 ] || input[ 1 ] )
	{
		cursor = engine_cursor_manager_get_cursor( menu_type_select );
		if( 0 == cursor )
		{
			check = 1;
			if( input[ 0 ] )
			{
				if( st->state_object_world_data == 0 )
				{
					st->state_object_world_data = MAX_WORLDS - 1;
				}
				else
				{
					st->state_object_world_data--;
				}
			}
			if( input[ 1 ] )
			{
				st->state_object_world_data++;
				if( st->state_object_world_data >= MAX_WORLDS )
				{
					st->state_object_world_data = 0;
				}
			}
		}
		else if( 1 == cursor )
		{
			check = 1;
			if( input[ 0 ] )
			{
				if( st->state_object_round_data == 0 )
				{
					st->state_object_round_data = MAX_ROUNDS - 1;
				}
				else
				{
					st->state_object_round_data--;
				}
			}
			if( input[ 1 ] )
			{
				st->state_object_round_data++;
				if( st->state_object_round_data >= MAX_ROUNDS )
				{
					st->state_object_round_data = 0;
				}
			}
		}
		else if( 2 == cursor )
		{
			st->state_object_trees_type = 1 - st->state_object_trees_type;
			engine_board_manager_border( border_type_game );
			engine_level_manager_draw_trees();
			print_trees();
		}
		else if( 3 == cursor )
		{
			st->state_object_exits_type = 1 - st->state_object_exits_type;
			engine_board_manager_toggle();
			print_exits();
		}
	}

	if( check )
	{
		engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
		engine_level_manager_draw_level();
		engine_level_manager_draw_middle();
		engine_memo_manager_levels( 28, 5, 10 );
	}

	input[ 0 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 0 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_accept );
		st->state_object_next_screen = screen_type_init;
		event_stage = event_stage_pause;
		return;
	}

	input[ 1 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 1 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_reset );
		st->state_object_next_screen = screen_type_option;
		event_stage = event_stage_pause;
		return;
	}

	// Draw sprites last.
	//engine_enemy_manager_draw();
	//engine_gamer_manager_draw();

	*screen_type = st->state_object_curr_screen;
}

static void print_title()
{
	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_select[ 0 ], TEXT_X, TEXT0_Y + 0 );
	engine_font_manager_draw_text( locale_object_select[ 1 ], TEXT_X, TEXT0_Y + 1 );
}

//static void print_level()
//{
//	//engine_cursor_manager_draw_grant2( menu_type_select, 3, 0 );
//	//engine_cursor_manager_draw_select2( 3, 0 );
//	//engine_cursor_manager_draw_select2( 6, 1 );
//}

static void print_trees()
{
	struct_state_object *st = &global_state_object;
	unsigned char delta = 8 + st->state_object_trees_type + 1;
	//engine_cursor_manager_draw_select2( index, 2 );
	engine_cursor_manager_draw_grant2( menu_type_select, delta, 2 );
}

static void print_exits()
{
	struct_state_object *st = &global_state_object;
	unsigned char delta = 11 + st->state_object_exits_type + 1;
	//engine_cursor_manager_draw_select2( index, 3 );
	engine_cursor_manager_draw_grant2( menu_type_select, delta, 3 );
}