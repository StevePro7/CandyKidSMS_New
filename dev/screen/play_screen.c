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

static unsigned char process_collision( unsigned char tile_type );

static void print( unsigned char dir );
static void get_actor_data( unsigned char *mover, unsigned char *tileZ );

void screen_play_screen_load()
{
	unsigned char actor_mover[ MAX_ACTORS ];
	unsigned char actor_tileZ[ MAX_ACTORS ];
	unsigned char round = 1;

	engine_command_manager_init();
	engine_delay_manager_load( 0 );

	engine_board_manager_init();
	engine_gamer_manager_init();
	engine_enemy_manager_init();
	engine_enemy_manager_load();
	get_actor_data( actor_mover, actor_tileZ );
	
	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();

	// Draw functions.
	//engine_board_manager_debugger();
	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 0, 0 );
	engine_level_manager_update_level( round, actor_mover, actor_tileZ );
	engine_level_manager_draw_level();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();

	//engine_font_manager_draw_text( "PLAY SCREEN!", 4, 10 );
	//engine_font_manager_draw_data( level_object_candy_count, 14, 11 );
	//engine_audio_manager_music_play( 3 );
	first_time = 1;
	frame_spot = 0;
}

void screen_play_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char gamer_direction = direction_type_none;
	unsigned char enemy_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_tile_type = tile_type_blank;

	unsigned char proceed;
	unsigned char enemy;
	unsigned int frame = fo->frame_count;
	state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();
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
		// Check gamer collision.
		//engine_font_manager_draw_data( frame, 11, 16 );

		gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		if( tile_type_blank != gamer_tile_type )
		{
			// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
			gamer_collision = process_collision( gamer_tile_type );
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
			gamer_direction = engine_gamer_manager_input_direction();
			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );
			
			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
			}
		}
	}


	// Move enemies.
	//enemy = actor_type_adi;
	for( enemy = 0; enemy < 1; enemy++ )
	//for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
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
				
				engine_enemy_manager_stop( enemy );
				frame_spot = 1;
				//engine_command_manager_add( frame, command_type_end_gamer, 0 );

				//frame_spot = 1;
				//engine_font_manager_draw_data( frame, 11, 6 );
			}
			// For continuity we want to check if actor can move immediately after stopping.
			if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
			{
				if( eo->mover )
				{
					//engine_font_manager_draw_text( "DIRECTION!!", 10, 12 );
					//enemy_direction = engine_enemy_manager_find_direction( enemy, go->tileX, go->tileY, go->direction );
					if( frame < 288 )
					{
						enemy_direction = engine_enemy_manager_scatter_direction( enemy );
					}
					else
					{
						enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY, go->direction );
					}

					//enemy_direction = direction_type_left;
					//engine_font_manager_draw_data( enemy_direction, 10, 13 );
					//print( enemy_direction );
					if( direction_type_none != enemy_direction )
					{
						engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
					}
				}
			}
		}
	}

	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;

	if( actor_type_kid != state_object_actor_kill )
	{
		*screen_type = screen_type_dead;
		return;
	}

	if( frame_spot )
	{
		engine_font_manager_draw_data( frame, 11, 6 );
		frame_spot = 0;
	}
	*screen_type = screen_type_play;
}

static unsigned char process_collision( unsigned char tile_type )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_collision = coll_type_empty;

	// Check gamer collision with candy.

	// Check gamer collision with bonus.

	// Check gamer collision with death tree.
	if( tile_type_trees == tile_type )
	{
		if( !state_object_invincibie && state_object_trees_type == tree_type_death )
		{
			gamer_collision = engine_level_manager_get_collision( go->tileX, go->tileY, go->direction, offset_type_none );
			if( coll_type_block == gamer_collision )
			{
				// Edge case : vulnerable Kid inside open exit with death trees
				gamer_collision = engine_move_manager_inside_exit( go->tileX, go->tileY );
			}
		}
	}

	return gamer_collision;
}

// TODO delete or put in debugger??
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

static void get_actor_data( unsigned char *mover, unsigned char *tileZ )
{
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char enemy;
	unsigned char index;

	mover[ 0 ] = 1;
	tileZ[ 0 ] = go->tileZ;
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		index = enemy + 1;
		mover[ index ] = eo->mover;
		tileZ[ index ] = eo->tileZ;
	}
}