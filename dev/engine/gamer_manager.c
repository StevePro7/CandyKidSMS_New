#include "gamer_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "input_manager.h"
#include "level_manager.h"
#include "move_manager.h"
#include "score_manager.h"
#include "sprite_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"
#include <stdlib.h>

#define SPRITE_TILES_GAMER	256 + 96

// Global variable.
struct_gamer_object global_gamer_object;

static void calcd_frame();
static void calcd_spots();

void engine_gamer_manager_init()
{
	struct_gamer_object *go = &global_gamer_object;

	// Kid images.
	unsigned char images[ NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME + 2 ] = { 0, 2, 4, 12, 14, 16 };		// Allow extra image for death.
	
	go->tileX = board_object_homeX[ actor_type_kid ];
	go->tileY = board_object_homeY[ actor_type_kid ];

	// Speed:	1, 2, 4, 8
	// Delay:	1, 2, 4, 8
	go->speeds[ 0 ] = 2;
	go->delays[ 0 ] = 1;
	go->speeds[ 1 ] = 4;
	go->delays[ 1 ] = 1;
	//go->boost = pace_type_slow;
	//engine_gamer_manager_pace( go->boost );
	go->prev_boost = pace_type_slow;
	go->curr_boost = pace_type_slow;
	engine_gamer_manager_pace( go->curr_boost );
	
	//go->speed = 1;
	//go->delay = 1;

	go->timer = 0;
	go->delta = 0;
	go->total = 0;
	

	go->lifecycle = lifecycle_type_idle;
	go->direction = direction_type_none;
	go->prev_move = direction_type_none;

	go->image = 0;					// TODO select may change this!
	go->frame = frame_type_stance;
	go->images[ 0 ][ 0 ] = images[ 0 ];
	go->images[ 0 ][ 1 ] = images[ 1 ];
	go->images[ 1 ][ 0 ] = images[ 2 ];
	go->images[ 1 ][ 1 ] = images[ 3 ];
	go->images[ 2 ][ 0 ] = images[ 4 ];
	go->images[ 2 ][ 1 ] = images[ 5 ];

	calcd_frame();
	calcd_spots();
}

void engine_gamer_manager_load()
{
	struct_gamer_object *go = &global_gamer_object;
	//go->velocity[ 0 ] = 4;
	//go->velocity[ 1 ] = 6;
	go->prev_boost = pace_type_slow;
	go->curr_boost = pace_type_slow;
	//go->curr_boost = pace_type_fast;
	engine_gamer_manager_pace( go->curr_boost );
	//go->boost = pace_type_slow;
	//engine_gamer_manager_pace( go->boost );
}

void engine_gamer_manager_update()
{
	struct_gamer_object *go = &global_gamer_object;
	if( lifecycle_type_move != go->lifecycle )
	{
		return;
	}

	go->timer++;
	if( go->timer < go->delay )
	{
		return;
	}

	go->timer = 0;
	go->delta += go->speed;
	go->total += go->speed;

	// Update position.
	if( direction_type_upxx == go->direction )
	{
		go->posnY -= go->speed;
	}
	else if( direction_type_down == go->direction )
	{
		go->posnY += go->speed;
	}
	else if( direction_type_left == go->direction )
	{
		go->posnX -= go->speed;
	}
	else if( direction_type_rght == go->direction )
	{
		go->posnX += go->speed;
	}

	// Update lifecycle.
	if( go->total >= TILE_SIZE )
	{
		if( direction_type_upxx == go->direction )
		{
			go->tileY--;
		}
		else if( direction_type_down == go->direction )
		{
			go->tileY++;
		}
		else if( direction_type_left == go->direction )
		{
			go->tileX--;
		}
		else if( direction_type_rght == go->direction )
		{
			go->tileX++;
		}

		calcd_spots();

		go->lifecycle = lifecycle_type_idle;
		go->delta = 0;
		go->total = 0;
	}

	// Swap frame half way.
	if( go->delta > TILE_HALF )
	{
		go->frame = 1 - go->frame;
		go->delta = 0;
		calcd_frame();
	}
}

void engine_gamer_manager_draw()
{
	struct_gamer_object *go = &global_gamer_object;
	engine_sprite_manager_draw_entity( go->posnX, go->posnY, go->calcd );
}

void engine_gamer_manager_hide()
{
	struct_gamer_object *go = &global_gamer_object;
	if( go->posnX > 60 && go->posnX < 148 && go->posnY > 60 && go->posnY < 116 )
	{
		return;
	}

	engine_sprite_manager_draw_entity( go->posnX, go->posnY, go->calcd );
}

void engine_gamer_manager_draw_death( unsigned char frame )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char death = 2;
	unsigned char calcd = SPRITE_TILES_GAMER + go->images[ death ][ frame ];
	engine_sprite_manager_draw_entity( go->posnX, go->posnY, calcd );
}

void engine_gamer_manager_move( unsigned char direction )
{
	struct_gamer_object *go = &global_gamer_object;
	go->direction = direction;
	go->lifecycle = lifecycle_type_move;
	go->frame = frame_type_toggle;
	calcd_frame();

	if( !state_object_full_boost )
	{
		if( pace_type_fast == go->curr_boost )
		{
			engine_score_manager_update_boost();
		}
	}
}

void engine_gamer_manager_wrap( unsigned char direction )
{
	struct_gamer_object *go = &global_gamer_object;
	if( 0 == go->tileX || ( MAZE_COLS - 1 ) == go->tileX )
	{
		go->tileX = direction_type_left == direction ? MAZE_COLS - 1 : 0;
	}
	if( 0 == go->tileY || ( MAZE_COLS - 1 ) == go->tileY )
	{
		go->tileY = direction_type_upxx == direction ? MAZE_ROWS - 1 : 0;
	}

	calcd_spots();
}

void engine_gamer_manager_pace( unsigned char boost )
{
	struct_gamer_object *go = &global_gamer_object;
	//unsigned char index = go->velocity[ boost ];
	go->prev_boost = go->curr_boost;
	go->curr_boost = boost;
	//go->boost = boost;
	//go->speed = boost_object_speed[ index ];
	//go->delay = boost_object_delay[ index ];

	// TODO test this new version
	go->speed = go->speeds[ boost ];
	go->delay = go->delays[ boost ];

	if( !state_object_full_boost )
	{
		if( pace_type_fast == go->curr_boost )
		{
			engine_score_manager_update_boost();
		}
	}
}

void engine_gamer_manager_stop()
{
	struct_gamer_object *go = &global_gamer_object;
	if( lifecycle_type_dead == go->lifecycle )
	{
		return;
	}

	go->prev_move = go->direction;
	go->direction = direction_type_none;
	go->frame = frame_type_stance;
	calcd_frame();

	// TODO delete
	//engine_font_manager_draw_data( go->tileX, 13, 6 );
	//engine_font_manager_draw_data( go->tileY, 13, 7 );
	// TODO delete

	// Check if in exit then move in previous direction [and wrap game board as necessary].
	if( go->tileX <= 1 || go->tileY <= 1 || go->tileX >= ( MAZE_COLS - 2 ) || go->tileY >= ( MAZE_ROWS - 2 ) )
	{
		engine_gamer_manager_wrap( go->prev_move );
		engine_gamer_manager_move( go->prev_move );
		return;
	}
}

void engine_gamer_manager_dead()
{
	struct_gamer_object *go = &global_gamer_object;
	go->lifecycle = lifecycle_type_dead;
	go->prev_move = go->direction;
	go->direction = direction_type_none;
	go->frame = frame_type_stance;
	calcd_frame();
}

void engine_gamer_manager_reset()
{
	struct_gamer_object *go = &global_gamer_object;

	// Reset at home.
	go->tileX = board_object_homeX[ actor_type_kid ];
	go->tileY = board_object_homeY[ actor_type_kid ];

	go->lifecycle = lifecycle_type_idle;
	go->direction = direction_type_none;
	go->frame = frame_type_stance;

	calcd_frame();
	calcd_spots();
}

unsigned char engine_gamer_manager_find_direction( unsigned char gamer_direction )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char collision;
	unsigned char thru_exit;

	if( direction_type_none == gamer_direction )
	{
		return direction_type_none;
	}

	// Avoid trees.
	if( state_object_trees_type == tree_type_avoid )
	{
		collision = engine_level_manager_get_collision( go->tileX, go->tileY, gamer_direction, offset_type_one );
		if( coll_type_empty == collision )
		{
			return gamer_direction;
		}

		// Closed exits.
		if( exit_type_closed == state_object_exits_type )
		{
			return direction_type_none;
		}
		// Public exits.
		else
		{
			thru_exit = engine_move_manager_gothru_exit( go->tileX, go->tileY, gamer_direction );
			if( thru_exit )
			{
				return gamer_direction;
			}
		}
	}
	// Death trees.
	else
	{
		// Vulnerable.
		if( !state_object_invincibie )
		{
			return gamer_direction;
		}
		else
		{
			// Invincible.
			thru_exit = engine_move_manager_border_exit( go->tileX, go->tileY, gamer_direction );
			if( thru_exit )
			{
				if( exit_type_public == state_object_exits_type )
				{
					thru_exit = engine_move_manager_gothru_exit( go->tileX, go->tileY, gamer_direction );
					if( thru_exit )
					{
						return gamer_direction;
					}

					return direction_type_none;
				}
			}
			else
			{
				return gamer_direction;
			}
		}
	}

	return direction_type_none;
}
unsigned char engine_gamer_manager_input_direction()
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char direction = direction_type_none;

	unsigned char input;
	input = engine_input_manager_move( input_type_up );
	if( input )
	{
		direction = direction_type_upxx;
	}
	else
	{
		input = engine_input_manager_move( input_type_down );
		if( input )
		{
			direction = direction_type_down;
		}
		else
		{
			input = engine_input_manager_move( input_type_left );
			if( input )
			{
				direction = direction_type_left;
			}
			else
			{
				input = engine_input_manager_move( input_type_right );
				if( input )
				{
					direction = direction_type_rght;
				}
			}
		}
	}

	return direction;
}

unsigned char engine_gamer_manager_input_boost( unsigned char direction )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char boost;
	unsigned char input;

	input = engine_input_manager_move( input_type_fire1 );
	if( !input )
	{
		if( pace_type_fast == go->curr_boost )
		{
			return pace_type_slow;
		}

		return pace_type_none;
	}
	else if( input )
	{
		if( direction_type_none != direction )
		{
			if( !state_object_full_boost )
			{
				boost = engine_score_manager_get_value( score_type_boost );
				if( 0 == boost )
				{
					// When boost exhausted then issue slow command.
					// Subsequent attempts will result in no boosts.
					return pace_type_fast == go->curr_boost ? pace_type_slow : pace_type_none;
				}
			}

			if( pace_type_slow == go->curr_boost )
			{
				return pace_type_fast;
			}
		}
	}

	return pace_type_none;
}

//unsigned char engine_gamer_manager_input_boost2( unsigned char direction )
//{
//	struct_gamer_object *go = &global_gamer_object;
//	//unsigned char boost = pace_type_slow;
//	unsigned char input;
//	//unsigned char boost;
//
//	input = engine_input_manager_move( input_type_fire1 );
//	if( !input )
//	{
//		if( pace_type_fast == go->curr_boost )
//		{
//			return pace_type_slow;
//		}
//
//		return pace_type_none;
//	}
//	else if( input )
//	{
//		if( direction_type_none != direction )
//		{
//			if( pace_type_slow == go->curr_boost )
//			{
//				return pace_type_fast;
//			}
//			//if( go->prev_boost != go->curr_boost )
//			//{
//			//	return 0;
//			//}
//			//else if( go->prev_boost == go->curr_boost )
//			//{
//			//	go->prev_boost = go->curr_boost;		// maybe
//			//	go->curr_boost = pace_type_fast;
//			//	return 1;
//			//}
//		}
//
//		//if( !state_object_full_boost )
//		//{
//		//	boost = engine_score_manager_get_value( score_type_boost );
//		//	if( boost <= 0 )
//		//	{
//		//		go->prev_boost = go->curr_boost;
//		//		go->curr_boost = pace_type_slow;
//		//		return 1;
//		//	}
//		//	else
//		//	{
//		//		go->prev_boost = go->curr_boost;
//		//		go->curr_boost = pace_type_fast;
//		//		return;
//		//	}
//		//}
//		//else
//		//{
//		//	go->prev_boost = go->curr_boost;
//		//	go->curr_boost = pace_type_fast;
//		//	return;
//		//}
//	}
//
//	return pace_type_none;
//}

//unsigned char engine_gamer_manager_input_boostX()
//{
//	struct_gamer_object *go = &global_gamer_object;
//	unsigned char boost;
//	//unsigned char boost = pace_type_none;
//	unsigned char input;
//	input = engine_input_manager_move( input_type_fire1 );
//
//	// If not press boost still have to see if revert old boost.
//	if( !input )
//	{
//		//if( pace_type_fast == go->boost )
//		//{
//		//	return pace_type_slow;
//		//}
//		if( go->prev_boost != go->curr_boost )
//		{
//			go->curr_boost = go->prev_boost;
//			return go->curr_boost;
//		}
//		else
//		{
//			return pace_type_none;
//		}
//	}
//	else if( input )
//	{
//		if( !state_object_full_boost )
//		{
//			boost = engine_score_manager_get_value( score_type_boost );
//			if( boost <= 0 )
//			{
//				return pace_type_none;
//			}
//		}
//
//		// OK to boost.
//		if( pace_type_slow == go->boost )
//		{
//			return pace_type_fast;
//		}
//	}
//
//	return pace_type_none;
//}

// TODO delete - used for debugging
//unsigned char engine_gamer_manager_input_direction2()
//{
//	struct_gamer_object *go = &global_gamer_object;
//	unsigned char direction = direction_type_none;
//
//	unsigned char input;
//	input = engine_input_manager_hold( input_type_up );
//	if( input )
//	{
//		direction = direction_type_upxx;
//	}
//	else
//	{
//		input = engine_input_manager_hold( input_type_down );
//		if( input )
//		{
//			direction = direction_type_down;
//		}
//		else
//		{
//			input = engine_input_manager_hold( input_type_left );
//			if( input )
//			{
//				direction = direction_type_left;
//			}
//			else
//			{
//				input = engine_input_manager_hold( input_type_right );
//				if( input )
//				{
//					direction = direction_type_rght;
//				}
//			}
//		}
//	}
//
//	return direction;
//}
// TODO delete - used for debugging

static void calcd_frame()
{
	struct_gamer_object *go = &global_gamer_object;
	go->calcd = SPRITE_TILES_GAMER + go->images[ go->image ][ go->frame ];
}
static void calcd_spots()
{
	struct_gamer_object *go = &global_gamer_object;
	go->posnX = board_object_posnX[ go->tileX ];
	go->posnY = board_object_posnY[ go->tileY ];
	engine_function_manager_convertXYtoZ( MAZE_ROWS, go->tileX, go->tileY, &go->tileZ );
}