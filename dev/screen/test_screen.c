#include "test_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\collision_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"

// TEST screen is used for automated testing - this was in the cont screen before
static unsigned char command_index;
static unsigned char command_count;
static unsigned char walking_delta;
static unsigned char walking_count;
static unsigned char first_time;

unsigned char test_walking_cmds1[] = { command_type_gamer_mover };
unsigned char test_walking_args1[] = { direction_type_down };

//unsigned char cont_walking_cmds1[] = { command_type_gamer_speed, command_type_gamer_mover };
//unsigned char cont_walking_args1[] = { pace_type_fast, direction_type_down };
unsigned char test_walking_move[] = { 1 };

void screen_test_screen_load()
{
	command_count = 1;

	engine_command_manager_load();
	engine_delay_manager_load( 0 );
	//engine_enemy_manager_load();
	//get_actor_data( actor_mover, actor_tileZ );

	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();
	engine_score_manager_update_level();

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 0, 0 );
	//engine_level_manager_update_level( 0, 0, 0);
	engine_level_manager_draw_level();

	engine_frame_manager_draw();
	engine_delay_manager_draw();

	command_index = 0;
	walking_delta = 0;
	walking_count = 0;
	first_time = 1;

	engine_font_manager_draw_text( "TEST SCREEN!!", 10, 12 );
}

void screen_test_screen_update( unsigned char *screen_type )
{
	unsigned char *test_walking_cmds = test_walking_cmds1;
	unsigned char *test_walking_args = test_walking_args1;


	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	unsigned char actor_cmds;
	unsigned char actor_args;

	unsigned char enemy_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_tile_type = tile_type_blank;

	unsigned char proceed;
	unsigned int frame = fo->frame_count;
	state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	engine_frame_manager_draw();
	engine_delay_manager_draw();
	if( !first_time )
	{
		proceed = engine_delay_manager_update();
		if( !proceed )
		{
			*screen_type = screen_type_reset;
			return;
		}

		engine_frame_manager_update();
		first_time = 1;
	}

	// Continue...
	frame = fo->frame_count;

	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		engine_gamer_manager_update();
	}
	if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	{
		// Check gamer collision.
		gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		if( tile_type_blank != gamer_tile_type )
		{
			// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
			gamer_collision = engine_collision_manager_tile_collision( gamer_tile_type );
			if( coll_type_block == gamer_collision )
			{
				engine_gamer_manager_dead();
				state_object_actor_kill = actor_type_tree;
			}
		}

		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		if( coll_type_empty == gamer_collision )
		{
			actor_args = direction_type_none;
			walking_count = 0;

			if( command_index >= command_count )
			{
				//command_index = 0;
				engine_font_manager_draw_data( frame, 12, 12 );

				engine_frame_manager_draw();
				engine_delay_manager_draw();

				*screen_type = screen_type_pass;
				return;
			}
			else
			{
				actor_cmds = test_walking_cmds[ command_index ];
				actor_args = test_walking_args[ command_index ];
				walking_count = test_walking_move[ command_index ];

				walking_delta++;
				if( walking_delta >= walking_count )
				{
					command_index++;
					walking_delta = 0;
				}

				actor_args = engine_gamer_manager_find_direction( actor_args );
				if( direction_type_none != actor_args )
				{
					engine_command_manager_add( frame, actor_cmds, actor_args );
				}
			}
		}
	}


	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;

	*screen_type = screen_type_test;
}