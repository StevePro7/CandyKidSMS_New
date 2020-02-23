#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "level_manager.h"
#include "move_manager.h"
#include "sprite_manager.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"
#include <stdlib.h>

#define SPRITE_TILES_ENEMY	256 + 48

// Global variables.
struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

static void calcd_frame( unsigned char enemy );
static void calcd_spots( unsigned char enemy );

// Methods.
void engine_enemy_manager_init()
{
	struct_enemy_object *eo;
	unsigned char images[ NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME * MAX_ENEMIES ] =
	{
		0, 2, 4, 12,		// Pro images.
		14, 16, 24, 26,		// Adi images.
		28, 36, 38, 40,		// Suz images.
	};

	unsigned char frame;
	//unsigned char homeX;
	//unsigned char homeY;

	unsigned char enemy;
	devkit_SMS_mapROMBank( FIXED_BANK );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		//homeX = board_homeX[ enemy ];
		//homeY = board_homeY[ enemy ];

		//eo->homeX = homeX;
		//eo->homeY = homeY;
		//engine_board_manager_calc_tileSpot( eo->homeX, eo->homeY, &eo->homeZ );
		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		eo->delay = 1;		// TODO hardcoded - inject!
		eo->timer = 0;
		eo->delta = 0;
		eo->total = 0;
		eo->speed = 1;		// TODO hardcoded - inject!
		eo->mover = 1;		// 1=move 0=stay.
		eo->lifecycle = lifecycle_type_idle;
		eo->prev_move = direction_type_none;
		//eo->prev_move[ 0 ] = direction_type_none;
		//eo->prev_move[ 1 ] = direction_type_none;
		//eo->prev_move[ 2 ] = direction_type_none;
		//eo->prev_move[ 3 ] = direction_type_none;

		eo->direction = direction_type_none;
		//eo->dir_fours = direction_type_none;
		//eo->dir_half2 = direction_type_none;
		eo->dir_count = 0;

		eo->image = frame_type_stance;
		eo->frame = 0;

		frame = enemy * NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME + 0;

		eo->images[ 0 ][ 0 ] = images[ frame + 0 ];
		eo->images[ 0 ][ 1 ] = images[ frame + 1 ];
		eo->images[ 1 ][ 0 ] = images[ frame + 2 ];
		eo->images[ 1 ][ 1 ] = images[ frame + 3 ];

		/*
		image = images[ frame + 0 ];
		eo->images[ 0 ][ 0 ] = image;

		image = images[ frame + 1 ];
		eo->images[ 0 ][ 1 ] = image;

		image = images[ frame + 2 ];
		eo->images[ 1 ][ 0 ] = image;

		image = images[ frame + 3 ];
		eo->images[ 1 ][ 1 ] = image;
		*/
		calcd_frame( enemy );
		calcd_spots( enemy );


		// TODO delete
		eo->mover = 1;
		eo->delay = 1;
		if( 0 != enemy )
		{
			eo->delay = 2;		// TODO hardcoded - inject!
			eo->speed = 1;		// 1=move 0=stay.
			eo->mover = 0;
		}
		//if( 1 == enemy )
		//{
		//	eo->delay = 2;		// TODO hardcoded - inject!
		//	eo->speed = 2;		// 1=move 0=stay.
		//	eo->mover = 0;
		//}
		// TODO delete
	}
}

void engine_enemy_manager_update( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	if( lifecycle_type_move != eo->lifecycle )
	{
		return;
	}

	eo->timer++;
	if( eo->timer < eo->delay )
	{
		return;
	}

	eo->timer = 0;
	eo->delta += eo->speed;
	eo->total += eo->speed;

	// Update position.
	if( direction_type_upxx == eo->direction )
	{
		eo->posnY -= eo->speed;
	}
	else if( direction_type_down == eo->direction )
	{
		eo->posnY += eo->speed;
	}
	else if( direction_type_left == eo->direction )
	{
		eo->posnX -= eo->speed;
	}
	else if( direction_type_rght == eo->direction )
	{
		eo->posnX += eo->speed;
	}

	// Update lifecycle.
	if( eo->total >= TILE_SIZE )
	{
		if( direction_type_upxx == eo->direction )
		{
			eo->tileY--;
		}
		else if( direction_type_down == eo->direction )
		{
			eo->tileY++;
		}
		else if( direction_type_left == eo->direction )
		{
			eo->tileX--;
		}
		else if( direction_type_rght == eo->direction )
		{
			eo->tileX++;
		}

		calcd_spots( enemy );

		eo->lifecycle = lifecycle_type_idle;
		eo->delta = 0;
		eo->total = 0;
	}

	if( eo->delta > TILE_HALF )
	{
		// TODO do the enemy hands.
		eo->frame = 1 - eo->frame;
		eo->delta = 0;
		calcd_frame( enemy );
	}
}

void engine_enemy_manager_draw()
{
	struct_enemy_object *eo;
	unsigned char enemy;
	//for( idx = 0; idx < MAX_ENEMIES; idx++ )
	//TODO revert to draw all enemies
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_move( unsigned char enemy, unsigned char direction )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->direction = direction;
	eo->lifecycle = lifecycle_type_move;

	// TODO do the enemy hands.
	eo->frame = frame_type_toggle;
	calcd_frame( enemy );
}

void engine_enemy_manager_stop( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//eo->prev_move[ 3 ] = eo->prev_move[ 2 ];
	//eo->prev_move[ 2 ] = eo->prev_move[ 1 ];
	//eo->prev_move[ 1 ] = eo->prev_move[ 0 ];
	//eo->prev_move[ 0 ] = eo->direction;
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
	eo->frame = 0;
	calcd_frame( enemy );

	// Every 4x moves check if enemy moved any combination of: U, D, L, R
	// e.g. if U + D + L + R = 15 then is caught in endless loop so change
	//eo->dir_fours |= eo->prev_move;
	//eo->dir_count++;
	//if( eo->dir_count > NUM_DIRECTIONS )
	//{
	//	eo->dir_count = 0;
	//	eo->dir_fours = eo->prev_move;
	//}
}

unsigned char engine_enemy_manager_find_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY, unsigned char gamer_direction )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	struct_enemy_object *eo0;

	unsigned char enemy_direction = direction_type_none;
	//signed char deltaX, deltaY;

	// This enemy does not move!
	if( !eo->mover )
	{
		return direction_type_none;
	}

	// TODO decide whether scatter or attack...!

	// ATTACK.
	if( actor_type_pro == enemy )
	{
		//enemy_direction = engine_move_manager_find_direction( eo->tileX, eo->tileY, targetX, targetY, eo->prev_move );
		//enemy_direction = engine_move_manager_find_direction( eo->tileX, eo->tileY, targetX, targetY, eo->prev_move );// , eo->dir_fours );

		// TODO  stevepro adriana actually put this method in the enemy manager
		// Like Blinky
		//gamer_direction = engine_move_manager_actor_direction( gamer_direction );
		//engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, 0 );

		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );

		//engine_font_manager_draw_text( "AFTER.....!!", 10, 13 );
		//engine_font_manager_draw_data( enemy_direction, 10, 14 );
	}
	else if( actor_type_adi == enemy )
	{
		// Like Pinky
		gamer_direction = engine_move_manager_actor_direction( gamer_direction );
		
		// Look two tiles in front on Candy Kid.
		engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, 4 );
		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	}
	else if( actor_type_suz == enemy )
	{
		unsigned char coin = rand() % 3;
		// COP OUT algorithm - works but Suz ALWAYS goes away from Kid.
		//enemy_direction = engine_enemy_manager_what_direction( enemy, ( MAZE_ROWS - 1 ) - targetX, ( MAZE_ROWS - 1 ) - targetY );

		// Try Pacman algorithm based off Blinky [Pro]
		eo0 = &global_enemy_objects[ coin ];
		
		// TODO while loop if Pro not moving then don't add AND if Adi not moving then don't add
		if( 2 != coin )
		{
			targetX = eo0->tileX;
			targetY = eo0->tileY;
		}
		//gamer_direction = engine_move_manager_actor_direction( gamer_direction );

		// Look two tiles in front on Candy Kid.
		// TODO - maybe make value 2 variable for Eash vs. Hard?
		//engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move[0], 0 );
		engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move, 0 );
		//enemy_direction = engine_enemy_manager_what_direction( enemy, ( MAZE_ROWS - 1 ) - targetX, ( MAZE_ROWS - 1 ) - targetY );
		enemy_direction = engine_enemy_manager_what_direction( enemy, ( 4 - 1 ) - targetX, ( 4 - 1 ) - targetY );

		//deltaX = eo0->tileX - targetX;
		//deltaY = eo0->tileY - targetY;
		//engine_font_manager_draw_data( deltaX, 31, 2 );
		//engine_font_manager_draw_data( deltaX, 31, 3 );
		//deltaX /= 2;
		//deltaX /= 2;
		//engine_font_manager_draw_data( deltaX, 31, 5 );
		//engine_font_manager_draw_data( deltaX, 31, 6 );

		//if( targetX < eo0->tileX )
		//{
		//	deltaX = eo0->tileX - targetX;
		//}
		//else
		//{
		//	deltaX = targetX - eo0->tileX;
		//}

		//if( targetY < eo0->tileY )
		//{
		//	deltaY = eo0->tileY - targetY;
		//}
		//else
		//{
		//	deltaY = targetY - eo0->tileY;
		//}

		//engine_font_manager_draw_data( deltaX, 31, 2 );
		//engine_font_manager_draw_data( deltaX, 31, 3 );
		////deltaX *= -1;
		////deltaY *= -1;
		////engine_font_manager_draw_data( deltaX, 31, 5 );
		////engine_font_manager_draw_data( deltaX, 31, 6 );


		//if( targetX < eo0->tileX )
		//{
		//	targetX = eo->tileX - deltaX;
		//}
		//else
		//{
		//	targetX = eo->tileX + deltaX;
		//}

		//if( targetY < eo0->tileY )
		//{
		//	targetY = eo->tileY - deltaY;
		//}
		//else
		//{
		//	targetY = eo->tileY + deltaY;
		//}

		//targetX = eo->tileX + deltaX;
		//targetY = eo->tileY + deltaY;

		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );

		//gamer_direction = engine_move_manager_actor_direction( gamer_direction );
		//engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, -4 );
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	}

	return enemy_direction;
}

unsigned char engine_enemy_manager_what_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
	unsigned char move_direction = direction_type_none;
	unsigned char oppX_direction = direction_type_none;
	//unsigned char prev_direction = direction_type_none;
	unsigned char test_direction = direction_type_none;
	unsigned char collision = direction_type_none;

	unsigned char sourceX = eo->tileX;
	unsigned char sourceY = eo->tileY;
	unsigned char index = 0;
	//unsigned char byte = 0;
	unsigned char list = 0;
	unsigned char half = 0;
	unsigned char flip = 0;

	// Get the list of 4x possible directions in the order depending on tiles.
	engine_move_manager_get_directions( sourceX, sourceY, targetX, targetY, &list, &half );

	// TODO randomly flip the half = 1 - half??
	//if( 15 == dir_fours )
	//{
	//	list = rand() % NUM_DIRECTIONS;	// 0 or 1
	//	//half = 1 - half;
	//}
	//flip = rand() % 2;	// 0 or 1
	//if( 0 == flip )
	//{
	//	half = 1 - half;
	//}
	// TODO randomly flip the half = 1 - half??

	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;

	// TODO fixed bank - change to data bank!!
	devkit_SMS_mapROMBank( FIXED_BANK );
	directions[ 0 ] = enemy_object_directions[ index + 0 ];
	directions[ 1 ] = enemy_object_directions[ index + 1 ];
	directions[ 2 ] = enemy_object_directions[ index + 2 ];
	directions[ 3 ] = enemy_object_directions[ index + 3 ];

	//engine_font_manager_draw_data( directions[ 0 ], 10, 13 );
	//engine_font_manager_draw_data( directions[ 1 ], 10, 14 );
	//engine_font_manager_draw_data( directions[ 2 ], 10, 15 );
	//engine_font_manager_draw_data( directions[ 3 ], 10, 16 );

	//prev_direction = eo->prev_move[ 3 ];
	//oppX_direction = engine_move_manager_opposite_direction( eo->prev_move[ 0 ] );
	oppX_direction = engine_move_manager_opposite_direction( eo->prev_move );
	for( index = 0; index < NUM_DIRECTIONS; index++ )
	{
		test_direction = directions[ index ];
		if( oppX_direction != test_direction )
		{
			//if( prev_direction != test_direction )
			//{
				collision = engine_level_manager_get_collision( sourceX, sourceY, test_direction, offset_type_one );
				if( coll_type_empty == collision )
				{
					move_direction = test_direction;
					break;
				}
			//}
		}
	}

	// Enemy in cul de sac so must be able to go in opposite direction!
	if( direction_type_none == move_direction )
	{
		collision = engine_level_manager_get_collision( sourceX, sourceY, oppX_direction, offset_type_one );
		if( coll_type_empty == collision )
		{
			move_direction = oppX_direction;
		}
	}

	return move_direction;
}

static void calcd_frame( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//eo->calcd = SPRITE_TILES_ENEMY + eo->image * 8 + eo->frame * 4;
	eo->calcd = SPRITE_TILES_ENEMY + eo->images[ eo->image ][ eo->frame ];
}
static void calcd_spots( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//struct_board_object *bo = &global_board_object;

	devkit_SMS_mapROMBank( FIXED_BANK );
	eo->posnX = board_object_posnX[ eo->tileX ];
	eo->posnY = board_object_posnY[ eo->tileY ];
	// Calculate exact tile as 1x byte.
	engine_function_manager_convertXYtoZ( MAZE_ROWS, eo->tileX, eo->tileY, &eo->tileZ );
}