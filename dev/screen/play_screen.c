#include "play_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
//#include "..\engine\storage_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\banks\databank.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
static unsigned char frame_spot;

// TODO put into the gmaer Mgr
static unsigned char get_gamer_direction();
static unsigned char get_gamer_collision();

static void print( unsigned char dir );
static void get_enemy_data( unsigned char *mover, unsigned char *tileZ );

void screen_play_screen_load()
{
	unsigned char enemy_mover[ MAX_ENEMIES ];
	unsigned char enemy_tileZ[ MAX_ENEMIES ];
	unsigned char round = 4;

	engine_command_manager_init();
	engine_delay_manager_load( 0 );

	engine_board_manager_init();
	engine_gamer_manager_init();
	engine_enemy_manager_init();
	get_enemy_data( enemy_mover, enemy_tileZ );
	
	engine_score_manager_load();
	//sengine_score_manager_draw_all();

	// Draw functions.
	//engine_board_manager_debugger();
	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 5, round );
	engine_level_manager_update_level( round, enemy_mover, enemy_tileZ );
	engine_level_manager_draw_level();

	engine_frame_manager_draw();
	engine_delay_manager_draw();

	//engine_font_manager_draw_text( "PLAY SCREEN!", 4, 10 );
	//engine_font_manager_draw_data( level_object_candy_count, 14, 11 );
	//engine_audio_manager_music_play( 3 );
	first_time = 1;
	frame_spot = 0;

	engine_font_manager_draw_data( enemy_mover[ 0 ], 10, 10 );
}

void screen_play_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char gamer_direction = direction_type_none;
	unsigned char enemy_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_collactor = actor_type_kid;

	unsigned char proceed;
	////unsigned char input;
	unsigned char enemy;
	unsigned int frame;
	frame = fo->frame_count;

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
			*screen_type = screen_type_play;
			return;
		}

		engine_frame_manager_update();
		first_time = 1;
	}

	// Continue...
	frame = fo->frame_count;
	frame_spot = 0;

	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		engine_gamer_manager_update();
	}
	if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	{
		// Check collision.
		//engine_font_manager_draw_data( frame, 12, 16 );
		engine_gamer_manager_stop();
		//gamer_collision = get_gamer_collision();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		if( coll_type_empty == gamer_collision )
		{
			gamer_direction = get_gamer_direction();
			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
			}
		}
	}


	// Move enemies.
	//enemy = actor_type_adi;
	for( enemy = 0; enemy < 1; enemy++ )
	{
		//for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
		{
			eo = &global_enemy_objects[ enemy ];
			//enemy_direction = direction_type_upxx;

			// Move enemy.
			if( direction_type_none != eo->direction && lifecycle_type_move == eo->lifecycle )
			{
				//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
				engine_enemy_manager_update( enemy );
			}
			if( direction_type_none != eo->direction && lifecycle_type_idle == eo->lifecycle )
			{
				// Check collision.
				engine_font_manager_draw_data( frame, 12, 20 );
				engine_enemy_manager_stop( enemy );

				//engine_command_manager_add( frame, command_type_end_gamer, 0 );
				//frame_spot = 1;
			}
			// For continuity we want to check if actor can move immediately after stopping.
			if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
			{
				//if( 0 == frame )
				{
					engine_font_manager_draw_text( "DIRECTION!!", 10, 12 );
					enemy_direction = engine_enemy_manager_find_direction( enemy, go->tileX, go->tileY );
					//enemy_direction = direction_type_left;
					//engine_font_manager_draw_data( enemy_direction, 10, 13 );
					print( enemy_direction );
					if( direction_type_none != enemy_direction )
					{
						engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
					}
				}

				//if( eo->mover )
				//{
				//	enemy_direction = engine_move_manager_find_direction( eo->tileX, eo->tileY, go->tileX, go->tileY, eo->direction );
				//	//if( 0 == frame || 16 == frame || 32 == frame || 64 == frame )
				//	//{
				//	//	engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
				//	//}
				//}
			}
		}
	}

	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;

	// TODO implement
	//if( coll_type_block == gamer_collision )
	//{
	//	*screen_type = screen_type_dead;
	//	return;
	//}
	
	*screen_type = screen_type_play;
}

static unsigned char get_gamer_direction()
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_direction = engine_gamer_manager_input_direction();
	//unsigned char gamer_direction = direction_type_rght;
	//unsigned char gamer_direction = direction_type_left;
	unsigned char collision;
	if( direction_type_none == gamer_direction )
	{
		return gamer_direction;
	}

	// Death trees don't need to check...
	if( state_object_trees_type == tree_type_death )
	{
		return gamer_direction;
	}

	// Avoid trees need to check first.
	collision = engine_level_manager_get_tile_type( go->tileX, go->tileY, gamer_direction, offset_type_one );
	if( coll_type_block == collision )
	{
		// Edge case for exits public and edge of maze.
		if( exit_type_public == state_object_exits_type )
		{
			collision = engine_board_manager_near_exit( go->tileX, go->tileY, gamer_direction );
			if( coll_type_block == collision )
			{
				gamer_direction = direction_type_none;
			}
		}
		else
		{
			gamer_direction = direction_type_none;
		}
	}
	

	return gamer_direction;
}

static unsigned char get_gamer_collision()
{
	return 0;
	//return coll_type_block;
}

static void print( unsigned char dir )
{
	if( 0 == dir )
	{
		engine_font_manager_draw_text( "NONE", 10, 13 );
	}
	if( 1 == dir )
	{
		engine_font_manager_draw_text( "UPXX", 10, 13 );
	}
	if( 2 == dir )
	{
		engine_font_manager_draw_text( "DOWN", 10, 13 );
	}
	if( 4 == dir )
	{
		engine_font_manager_draw_text( "LEFT", 10, 13 );
	}
	if( 8 == dir )
	{
		engine_font_manager_draw_text( "RGHT", 10, 13 );
	}
}

static void get_enemy_data( unsigned char *mover, unsigned char *tileZ )
{
	struct_enemy_object *eo;
	unsigned char enemy;
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		mover[ enemy ] = eo->mover;
		tileZ[ enemy ] = eo->tileZ;
	}
}