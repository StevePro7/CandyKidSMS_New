#include "option_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"

// Private helper methods.
//static void print_title();
static void print_gamer();
static void print_enemy( unsigned char enemy );

static unsigned char event_stage;

void screen_option_screen_load()
{
	struct_state_object *st = &global_state_object;
	unsigned char enemy;

	// Reset actors home.
	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();


	devkit_SMS_displayOff();
	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();

	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	//. Display text.
	//engine_cursor_manager_draw_title1();
	engine_cursor_manager_draw_titles( menu_type_option );

	//print_title();
	print_gamer();
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		print_enemy( enemy );
	}

	engine_memo_manager_option();
	engine_cursor_manager_draw2( menu_type_option );
	devkit_SMS_displayOn();

	engine_delay_manager_load( SOUND_SCREEN_DELAY + 10 );
	st->state_object_curr_screen = screen_type_option;
	st->state_object_next_screen = screen_type_option;
	event_stage = event_stage_start;
}

void screen_option_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input[ 2 ] = { 0, 0 };
	unsigned char direction;
	unsigned char cursor;
	unsigned char enemy;
	unsigned char delay;
	unsigned char tests;

	if( event_stage_pause == event_stage )
	{
		if( screen_type_select == st->state_object_next_screen )
		{
			engine_enemy_manager_draw();
			engine_gamer_manager_draw();
		}

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

	// Detect possible multi-direction first.
	direction = engine_input_manager_direction();
	if( direction_type_none != direction )
	{
		// Check up or down for cursor manager.
		tests = engine_cursor_manager_update2( menu_type_option );
		if( !tests )
		{
			// If not up or down then check left or right for select.
			input[ 0 ] = engine_input_manager_hold( input_type_left );
			input[ 1 ] = engine_input_manager_hold( input_type_right );

			if( input[ 0 ] || input[ 1 ] )
			{
				cursor = engine_cursor_manager_get_cursor( menu_type_option );
				if( actor_type_pro == cursor )
				{
					engine_gamer_manager_image();
					print_gamer();
				}
				else
				{
					enemy = cursor - 1;
					engine_enemy_manager_image( enemy );
					print_enemy( enemy );
				}
			}
		}
	}


	// Draw sprites last.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	input[ 0 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 0 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_accept );
		st->state_object_next_screen = screen_type_select;
		event_stage = event_stage_pause;
		return;
	}

	input[ 1 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 1 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_reset );
		st->state_object_next_screen = screen_type_begin;
		event_stage = event_stage_pause;
		return;
	}

	/*struct_state_object *st = &global_state_object;
	unsigned char input;

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		st->state_object_exits_type = 1 - st->state_object_exits_type;
		engine_board_manager_toggle();
	}

	input = engine_input_manager_hold( input_type_fire2 );
	if( input )
	{
		st->state_object_trees_type = 1 - st->state_object_trees_type;
		engine_board_manager_border( border_type_game );
	}*/

	

	//*screen_type = screen_type_select;
	*screen_type = st->state_object_curr_screen;
}

// TODO delete!!
//static void print_names()
//{
//	struct_gamer_object *go = &global_gamer_object;
//	struct_enemy_object *eo;
//	unsigned char enemy;
//	unsigned char index;
//
//	// Gamer.
//	index = 2 + actor_type_pro * 3;
//	index += go->image + 1;
//	engine_cursor_manager_draw_option( index, go->tileX * 2 - 4, go->tileY * 2 + 1 );
//
//	// Enemy.
//	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
//	{
//		eo = &global_enemy_objects[ enemy ];
//		index = 2 + enemy * 3;
//		index += eo->image + 1;
//		engine_cursor_manager_draw_option( index, eo->tileX * 2 - 2, eo->tileY * 2 + 1 );
//	}
//}

//static void print_title()
//{
//	devkit_SMS_mapROMBank( FIXED_BANK );
//	engine_font_manager_draw_text( locale_object_option[ 0 ], TEXT_X, TEXT0_Y + 0 );
//	engine_font_manager_draw_text( locale_object_option[ 1 ], TEXT_X, TEXT0_Y + 1 );
//}

static void print_gamer()
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char delta;

	// Gamer.
	delta = 2 + actor_type_pro * 3;
	delta += go->image + 1;
	//engine_cursor_manager_draw_option1( index, go->tileX * 2 - 2, go->tileY * 2 + 1 );
	//engine_cursor_manager_draw_option2( delta, actor_type_pro );

	engine_cursor_manager_draw_grant1( menu_type_option, delta, go->tileX * 2 - 1, go->tileY * 2 + 1 );
	engine_cursor_manager_draw_grant2( menu_type_option, delta, actor_type_pro );

	//engine_cursor_manager_draw_grant1( menu_type_select, delta, go->tileX * 2 - 1, go->tileY * 2 + 1 );
	//engine_cursor_manager_draw_grant2( menu_type_select, delta, actor_type_pro );
}

static void print_enemy( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char delta;
	unsigned char actor = enemy + 1;

	delta = 2 + actor * 3;
	delta += eo->image + 1;
	//engine_cursor_manager_draw_option1( index, eo->tileX * 2 - 2, eo->tileY * 2 + 1 );
	//engine_cursor_manager_draw_option2( index, actor );

	engine_cursor_manager_draw_grant1( menu_type_option, delta, eo->tileX * 2 - 1, eo->tileY * 2 + 1 );
	engine_cursor_manager_draw_grant2( menu_type_option, delta, actor );

	//engine_cursor_manager_draw_grant1( menu_type_select, delta, eo->tileX * 2 - 1, eo->tileY * 2 + 1 );
	//engine_cursor_manager_draw_grant2( menu_type_select, delta, actor );
}