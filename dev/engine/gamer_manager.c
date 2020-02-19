#include "gamer_manager.h"
//#include "board_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "input_manager.h"
#include "sprite_manager.h"
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
	//unsigned char homeX;
	//unsigned char homeY;

	//homeX = board_homeX[ actor_type_kid ];
	//homeY = board_homeY[ actor_type_kid ];

	//go->homeX = homeX;
	//go->homeY = homeY;
	//engine_board_manager_calc_tileSpot( go->homeX, go->homeY, &go->homeZ );
	devkit_SMS_mapROMBank( FIXED_BANK );
	go->tileX = board_object_homeX[ actor_type_kid ];
	go->tileY = board_object_homeY[ actor_type_kid ];

	// Delay:	1, 2, 4, 8
	go->delay = 1;
	go->timer = 0;
	go->delta = 0;
	go->total = 0;
	go->speed = 1;
	// Speed:	1, 2, 4, 8

	go->prev_move = direction_type_none;
	go->direction = direction_type_none;
	go->lifecycle = lifecycle_type_idle;

	go->image = 0;
	go->frame = frame_type_stance;
	go->images[ 0 ][ 0 ] = images[ 0 ];
	go->images[ 0 ][ 1 ] = images[ 1 ];
	go->images[ 1 ][ 0 ] = images[ 2 ];
	go->images[ 1 ][ 1 ] = images[ 3 ];
	go->images[ 2 ][ 0 ] = images[ 4 ];
	go->images[ 2 ][ 1 ] = images[ 5 ];

	calcd_frame();

	calcd_frame();
	calcd_spots();

	//TODO delete
	//engine_font_manager_draw_data( go->tileX, 16, 2 );
	//engine_font_manager_draw_data( go->tileY, 16, 3 );
	//engine_font_manager_draw_data( go->posnX, 16, 5 );
	//engine_font_manager_draw_data( go->posnY, 16, 6 );
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

void engine_gamer_manager_move( unsigned char direction )
{
	struct_gamer_object *go = &global_gamer_object;
	go->direction = direction;
	go->lifecycle = lifecycle_type_move;
	go->frame = frame_type_toggle;
	calcd_frame();
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

void engine_gamer_manager_stop()
{
	struct_gamer_object *go = &global_gamer_object;
	go->prev_move = go->direction;
	go->direction = direction_type_none;
	go->frame = frame_type_stance;
	calcd_frame();

	// TODO delete
	//engine_font_manager_draw_data( go->tileX, 12, 8 );
	//engine_font_manager_draw_data( go->tileY, 12, 9 );
	// TODO delete

	// Check if in exit then move in previous direction [and wrap game board as necessary].
	if( go->tileX <= 1 || go->tileY <= 1 || go->tileX >= ( MAZE_COLS - 2 ) || go->tileY >= ( MAZE_ROWS - 2 ) )
	{
		engine_gamer_manager_wrap( go->prev_move );
		engine_gamer_manager_move( go->prev_move );
		return;
	}

	// TODO calc possible tiles actor can move in to.
}

void engine_gamer_manager_dead()
{

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

// TODO delete
//unsigned char engine_gamer_manager_mover_direction()
//{
//	struct_gamer_object *go = &global_gamer_object;
//	unsigned char dirX;
//	unsigned char loop;
//	unsigned char time;
//
//	// If gamer already traveling in direction return that direction,
//	if( direction_type_none != go->direction )
//	{
//		return go->direction;
//	}
//
//	// Otherwise calculate random direction for enemy to target.
//	dirX = 1;
//	time = rand() % 4;
//	for( loop = 0; loop < time; loop++ )
//	{
//		dirX *= 2;
//	}
//
//	return dirX;
//}

static void calcd_frame()
{
	struct_gamer_object *go = &global_gamer_object;
	go->calcd = SPRITE_TILES_GAMER + go->images[ go->image ][ go->frame ];
}
static void calcd_spots()
{
	struct_gamer_object *go = &global_gamer_object;
	//struct_board_object *bo = &global_board_object;
	devkit_SMS_mapROMBank( FIXED_BANK );
	go->posnX = board_object_posnX[ go->tileX ];
	go->posnY = board_object_posnY[ go->tileY ];
	// Calculate exact tile as 1x byte.
	engine_function_manager_convertXYtoZ( MAZE_ROWS, go->tileX, go->tileY, &go->tileZ );
}