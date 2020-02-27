#include "play_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\collision_manager.h"
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
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
static unsigned char frame_spot;

//static unsigned char process_collision( unsigned char tile_type );

//static void print( unsigned char dir );
static void get_actor_data( unsigned char *mover, unsigned char *tileZ );

void screen_play_screen_load()
{
	//struct_enemy_object *eo;
	unsigned char actor_mover[ MAX_ACTORS ];
	unsigned char actor_tileZ[ MAX_ACTORS ];
	unsigned char round = 4;

	engine_delay_manager_load( 0 );

	engine_enemy_manager_load();
	get_actor_data( actor_mover, actor_tileZ );
	
	// Put in init screen
	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();

	// Draw functions.
	//engine_board_manager_debugger();
	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 0, round );
	//engine_level_manager_load_level( 8, 7 );
	//engine_level_manager_load_level( 9, 4 );
	engine_level_manager_update_level( round, actor_mover, actor_tileZ );
	engine_level_manager_draw_level();

	engine_frame_manager_draw();
	engine_delay_manager_draw();

	engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//engine_font_manager_draw_data( level_object_candy_count, 14, 11 );
	engine_audio_manager_music_play( music_type_game03 );
	//engine_audio_manager_music_play( music_type_candykid );
	//engine_audio_manager_music_play( music_type_beatgame );
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
	//unsigned char input;
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

	// TODO delete
	//input = engine_input_manager_hold( input_type_fire1 );
	//if( input )
	//{
	//	frame_spot = 1 - frame_spot;
	//	if( 0 == frame_spot )
	//	{
	//		engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//	}
	//	else
	//	{
	//		engine_font_manager_draw_text( "ATTACK", 26, 21 );
	//		//engine_font_manager_draw_text( "GOHOME", 26, 21 );
	//	}
	//}

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
			gamer_direction = engine_gamer_manager_input_direction();
			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );

			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
			}
		}
	}




	// Move enemies.
	//for( enemy = 0; enemy < 1; enemy++ )
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Swap hands first if enemy moving and not dead.
		if( eo->mover && lifecycle_type_dead != eo->lifecycle )
		{
			engine_enemy_manager_dohand( enemy );
		}

		// If enemy not moving then skip all movement code.
		if( !eo->mover )
		{
			continue;
		}

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

			//engine_font_manager_draw_data( frame, 19, 6 );
			//engine_font_manager_draw_data( eo->action, 19, 7 );
			//engine_font_manager_draw_data( eo->ticker, 19, 8 );

			//if( 0 == eo->action )
			//{
			//	engine_font_manager_draw_text( "SCATTR", 26, 21 );
			//}
			//if( 1 == eo->action )
			//{
			//	engine_font_manager_draw_text( "ATTACK", 26, 21 );
			//}
			
		}
		// For continuity we want to check if actor can move immediately after stopping.
		if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			//engine_font_manager_draw_data( eo->action, 30, 21 );
			if( enemymove_type_wait == eo->action )
			{
				if( frame >= eo->waiter )
				{
					eo->action = enemymove_type_tour;
				}
			}

			if( enemymove_type_tour == eo->action )
			{
				enemy_direction = engine_enemy_manager_scatter_direction( enemy );
				//eo->action = enemymove_type_kill;
			}
			else if( enemymove_type_kill == eo->action )
			{
				enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY, go->direction );
				//eo->action = enemymove_type_home;
			}

			if( direction_type_none != enemy_direction )
			{
				engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
			}

			//enemy_direction = engine_enemy_manager_find_direction( enemy, go->tileX, go->tileY, go->direction );
			//if( frame < 288 )
			//if( 0 == frame_spot )
			//{
			//	enemy_direction = engine_enemy_manager_scatter_direction( enemy );
			//}
			//else if( 1 == frame_spot )
			//{
			//	//enemy_direction = engine_enemy_manager_gohome_direction( enemy );
			//	enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY, go->direction );
			//}
		}
	}

	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;


	// TODO tidy up this temp sprite collision
	gamer_collision = devkit_isCollisionDetected();
	//engine_font_manager_draw_data( gamer_collision, 16, 12 );
	//if( 0 != gamer_collision )

	// TODO tidy up this temp sprite collision


	if( actor_type_kid != state_object_actor_kill )
	{
		*screen_type = screen_type_dead;
		return;
	}

	//if( frame_spot )
	//{
	//	//engine_font_manager_draw_data( frame, 11, 6 );
	//	frame_spot = 0;
	//}
	*screen_type = screen_type_play;
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