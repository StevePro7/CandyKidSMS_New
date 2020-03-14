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
#include "..\engine\memo_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
static unsigned char frame_spot;
static unsigned char nextr_direction;

void screen_play_screen_load()
{
	//struct_enemy_object *eo;
	engine_delay_manager_load( 0 );

	engine_command_manager_load();
	engine_frame_manager_load();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();

	//engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//eo = &global_enemy_objects[ actor_type_pro ];	engine_memo_manager_debugging( actor_type_pro, eo->action );
	//eo = &global_enemy_objects[ actor_type_adi ];	engine_memo_manager_debugging( actor_type_adi, eo->action );
	//eo = &global_enemy_objects[ actor_type_suz ];	engine_memo_manager_debugging( actor_type_suz, eo->action );
	first_time = 1;
	frame_spot = 0;
	nextr_direction = direction_type_none;
}

void screen_play_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	//unsigned char process_boost = 0;
	unsigned char gamer_boost = 0;
	unsigned char enemy_boost = 0;
	unsigned char gamer_direction = direction_type_none;
	unsigned char enemy_direction = direction_type_none;
	unsigned char input_direction = direction_type_none;
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


	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		input_direction = engine_gamer_manager_input_direction();
		if( direction_type_none != input_direction && gamer_direction != input_direction )
		{
			nextr_direction = gamer_direction;
			//engine_font_manager_draw_data( nextr_direction, 30, 20 );		// stevepro pre-empt direction
		}

		engine_gamer_manager_update();

		// Check boost for next cycle.
		gamer_boost = engine_gamer_manager_input_boost( go->direction );
		if( pace_type_none != gamer_boost )
		{
			//engine_font_manager_draw_data( gamer_boost, 10, 18 );
			engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
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

		input_direction = engine_gamer_manager_input_direction();
		if( direction_type_none != input_direction && gamer_direction != input_direction )
		{
			nextr_direction = gamer_direction;
			//engine_font_manager_draw_data( nextr_direction, 30, 20 );		// stevepro pre-empt direction
		}

		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		if( coll_type_empty == gamer_collision )
		{
			if( direction_type_none != nextr_direction )
			{
				gamer_direction = nextr_direction;
				//engine_font_manager_draw_data( gamer_direction, 30, 21 );		// stevepro pre-empt direction
				nextr_direction = direction_type_none;
				//engine_font_manager_draw_data( nextr_direction, 30, 20 );		// stevepro pre-empt direction
			}
			else
			{
				gamer_direction = engine_gamer_manager_input_direction();
				//engine_font_manager_draw_data( gamer_direction, 30, 21 );		// stevepro pre-empt direction
			}

			//engine_font_manager_draw_data( nextr_direction, 30, 20 );
			//engine_font_manager_draw_data( gamer_direction, 30, 22 );			// stevepro pre-empt direction
			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );
			//engine_font_manager_draw_data( gamer_direction, 30, 23 );			// stevepro pre-empt direction

			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );

				gamer_boost = engine_gamer_manager_input_boost( gamer_direction );
				if( pace_type_none != gamer_boost )
				{
					//engine_font_manager_draw_data( gamer_boost, 10, 17 );
					engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
				}
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
					//engine_enemy_manager_reset_mode( enemy, enemymove_type_kill );		// stevepro
				}
			}

			if( enemymove_type_tour == eo->action || enemymove_type_kill == eo->action )
			{
				enemy_boost = engine_enemy_manager_input_boost( enemy );
				if( pace_type_none != enemy_boost )
				{
					engine_command_manager_add( frame, command_type_enemy_speed, ( enemy | ( enemy_boost << 4 ) ) );
				}

				if( enemymove_type_tour == eo->action )
				{
					enemy_direction = engine_enemy_manager_scatter_direction( enemy );
				}
				else if( enemymove_type_kill == eo->action )
				{
					enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY );
				}

				if( direction_type_none != enemy_direction )
				{
					engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
				}
			}
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