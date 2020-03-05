#include "play_screen.h"
#include "..\engine\actor_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\collision_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
//#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"
//#include <stdbool.h>

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
static unsigned char frame_spot;

void screen_play_screen_load()
{
	//struct_enemy_object *eo;
	unsigned char actor_mover[ MAX_ACTORS ];
	//unsigned char actor_tileX[ MAX_ACTORS ];
	//unsigned char actor_tileY[ MAX_ACTORS ];
	unsigned char actor_tileZ[ MAX_ACTORS ];

	engine_delay_manager_load( 0 );

	engine_gamer_manager_load();
	engine_enemy_manager_load();
	//get_actor_data( actor_mover, actor_tileZ );
	engine_actor_manager_get_data( actor_mover, actor_tileZ );

	// Must draw score first for Level which is currently 5x characters.
	state_object_round_data = 1;
	engine_score_manager_load();
	//engine_score_manager_draw_all();

	// Draw functions.
	//engine_board_manager_debugger();
	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	//engine_level_manager_load_level( 0, 0 );
	
	engine_level_manager_load_level( state_object_world_data, state_object_round_data );
	//engine_level_manager_load_level( 8, 7 );
	//engine_level_manager_load_level( 9, 4 );
	engine_level_manager_update_level( state_object_round_data, actor_mover, actor_tileZ );
	engine_level_manager_draw_level();



	engine_frame_manager_draw();
	engine_delay_manager_draw();

	engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//engine_font_manager_draw_data( level_object_candy_count, 14, 11 );
	engine_audio_manager_music_play( music_type_game03 );
	//engine_audio_manager_music_play( music_type_beatgame );
	//engine_audio_manager_music_play( music_type_candykid );
	first_time = 1;
	frame_spot = 0;
}

void screen_play_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char process_boost = 0;
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
	//input = engine_input_manager_move( input_type_fire1 );
	//if( input )
	//{
	//	engine_font_manager_draw_text( "DEAD TREE", 9, 9 );
	//	//state_object_actor_kill = actor_type_tree;

	//	engine_enemy_manager_dead( actor_type_pro );
	//	state_object_actor_kill = actor_type_pro;
	//	*screen_type = screen_type_dead;
	//	return;
	//}

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

		// Check boost for next cycle.
		process_boost = engine_gamer_manager_input_boost( go->direction );
		if( pace_type_none != process_boost )
		{
			//engine_font_manager_draw_data( process_boost, 10, 18 );
			engine_command_manager_add( frame, command_type_gamer_speed, process_boost );
		}
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
			//gamer_boost = engine_score_manager_get_value( score_type_boost );
			//gamer_boost = engine_gamer_manager_input_boost( gamer_boost );
			//gamer_boost = engine_gamer_manager_input_boost();
			
			//if( pace_type_none != gamer_boost )
			//{
			//	//engine_font_manager_draw_text( "BOOST", 15, 15 );
			//	engine_font_manager_draw_data( gamer_boost, 15, 15 );
			//}

			//if( pace_type_slow == gamer_boost )
			//{
			//	engine_font_manager_draw_text( "SLOW", 15, 17 );
			//	engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
			//}

			gamer_direction = engine_gamer_manager_input_direction();
			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );

			//process_boost = engine_gamer_manager_input_boost( gamer_direction );
			//if( pace_type_none != process_boost )
			//{
			//	engine_font_manager_draw_data( process_boost, 10, 17 );
			//	engine_command_manager_add( frame, command_type_gamer_speed, process_boost );
			//}
			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );

				process_boost = engine_gamer_manager_input_boost( gamer_direction );
				if( pace_type_none != process_boost )
				{
					//engine_font_manager_draw_data( process_boost, 10, 17 );
					engine_command_manager_add( frame, command_type_gamer_speed, process_boost );
				}

				//if( go->prev_boost != go->curr_boost )
				//{
				//	engine_font_manager_draw_text( "FAST", 15, 16 );
				//	engine_command_manager_add( frame, command_type_gamer_speed, go->curr_boost );
				//}
			}
			//else
			//{
			//	if( go->prev_boost != go->curr_boost )
			//	{
			//		engine_font_manager_draw_text( "FAST", 15, 16 );
			//		engine_command_manager_add( frame, command_type_gamer_speed, go->curr_boost );
			//	}
			//}
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
					engine_enemy_manager_reset_mode( enemy, enemymove_type_tour );
					//eo->action = enemymove_type_tour;
				}
			}

			if( enemymove_type_tour == eo->action )
			{
				enemy_direction = engine_enemy_manager_scatter_direction( enemy );
				//eo->action = enemymove_type_kill;
			}
			else if( enemymove_type_kill == eo->action )
			{
				enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY );
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



	// Check candy collision before sprite collision as we want to test if all candy eaten = level complete
	if( coll_type_candy == gamer_collision )
	{
		// TODO update correct screen.
		unsigned char candy_count = engine_score_manager_get_candy();
		if( level_object_candy_count == candy_count )
		{
			*screen_type = screen_type_pass;
			return;
		}
	}

	// Kid invincible thus don't check for death collisions.
	if( state_object_invincibie )
	{
		*screen_type = screen_type_play;
		return;
	}

	// Kid collide with death tree?
	if( state_object_trees_type == tree_type_death )
	{
		if( actor_type_kid != state_object_actor_kill )
		{
			*screen_type = screen_type_dead;
			return;
		}
	}

	// Kid collide with Candy Mama?
	gamer_collision = devkit_isCollisionDetected();
	if( 0 != gamer_collision )
	{
		state_object_actor_kill = engine_collision_manager_sprite_collision();
		if( actor_type_kid != state_object_actor_kill )
		{
			engine_enemy_manager_dead( state_object_actor_kill );
			*screen_type = screen_type_dead;
			return;
		}
	}

	*screen_type = screen_type_play;
}