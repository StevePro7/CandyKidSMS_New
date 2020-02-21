#include "move_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "level_manager.h"
#include "mask_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"
#include <stdlib.h>

#define EXIT_SPOT1		2
#define EXIT_SPOT2		4
#define EXIT_SPOT3		9
#define EXIT_SPOT4		11

//unsigned char engine_move_manager_find_direction( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char enemy_direction, unsigned char dir_fours )
//unsigned char engine_move_manager_find_direction( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char enemy_direction )
//{
//	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
//	unsigned char move_direction = direction_type_none;
//	unsigned char oppX_direction = direction_type_none;
//	unsigned char test_direction = direction_type_none;
//	unsigned char collision = direction_type_none;
//	unsigned char index = 0;
//	//unsigned char byte = 0;
//	unsigned char list = 0;
//	unsigned char half = 0;
//	unsigned char flip = 0;
//
//	// Get the list of 4x possible directions in the order depending on tiles.
//	engine_move_manager_get_directions( srceX, srceY, destX, destY, &list, &half );
//
//	// TODO randomly flip the half = 1 - half??
//	//if( 15 == dir_fours )
//	//{
//	//	list = rand() % NUM_DIRECTIONS;	// 0 or 1
//	//	//half = 1 - half;
//	//}
//	//flip = rand() % 2;	// 0 or 1
//	//if( 0 == flip )
//	//{
//	//	half = 1 - half;
//	//}
//	// TODO randomly flip the half = 1 - half??
//
//	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;
//
//	// TODO fixed bank - change to data bank!!
//	devkit_SMS_mapROMBank( FIXED_BANK );
//	directions[ 0 ] = enemy_object_directions[ index + 0 ];
//	directions[ 1 ] = enemy_object_directions[ index + 1 ];
//	directions[ 2 ] = enemy_object_directions[ index + 2 ];
//	directions[ 3 ] = enemy_object_directions[ index + 3 ];
//
//	//engine_font_manager_draw_data( directions[ 0 ], 10, 13 );
//	//engine_font_manager_draw_data( directions[ 1 ], 10, 14 );
//	//engine_font_manager_draw_data( directions[ 2 ], 10, 15 );
//	//engine_font_manager_draw_data( directions[ 3 ], 10, 16 );
//
//	oppX_direction = engine_move_manager_opposite_direction( enemy_direction );
//	for( index = 0; index < NUM_DIRECTIONS; index++ )
//	{
//		test_direction = directions[ index ];
//		if( oppX_direction != test_direction )
//		{
//			collision = engine_level_manager_get_collision( srceX, srceY, test_direction, offset_type_one );
//			if( coll_type_empty == collision )
//			{
//				move_direction = test_direction;
//				break;
//			}
//		}
//	}
//
//	// Enemy in cul de sac so must be able to go in opposite direction!
//	if( direction_type_none == move_direction )
//	{
//		collision = engine_level_manager_get_collision( srceX, srceY, oppX_direction, offset_type_one );
//		if( coll_type_empty == collision )
//		{
//			move_direction = oppX_direction;
//		}
//	}
//
//	return move_direction;
//}

void engine_move_manager_get_directions( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char *list, unsigned char *half )
{
	unsigned char deltaX = 0;
	unsigned char deltaY = 0;
	unsigned char minusY = 0;
	unsigned char plusX = 0;

	// Determine which directions...
	if( srceX > destX )
	{
		deltaX = srceX - destX;
	}
	else if( srceX < destX )
	{
		deltaX = destX - srceX;
		plusX = 1;
	}

	if( srceY > destY )
	{
		deltaY = srceY - destY;
		minusY = 1;
	}
	else if( srceY < destY )
	{
		deltaY = destY - srceY;
	}

	// Determine which direction index to use.
	if( deltaX > deltaY )
	{
		if( plusX )
		{
			*list = 0;
		}
		else
		{
			*list = 1;
		}
	}
	else
	{
		if( plusX )
		{
			*list = 2;
		}
		else
		{
			*list = 3;
		}
	}

	*half = minusY ? 0 : 1;
}

unsigned char engine_move_manager_actor_direction( unsigned char direction )
{
	unsigned char loop;
	unsigned char time;

	// If actor already traveling in direction then return that direction,
	if( direction_type_none != direction )
	{
		return direction;
	}

	// Otherwise calculate random direction for further game code function.
	direction = 1;
	time = rand() % 4;

	// Algorithm will give 1, 2, 4, 8	that is : Up / Down / Left / Right.
	for( loop = 0; loop < time; loop++ )
	{
		direction *= 2;
	}

	return direction;
}

unsigned char engine_move_manager_gothru_exit( unsigned char tileX, unsigned char tileY, unsigned char direction )
{
	unsigned char can_go_thru_exit = coll_type_empty;
	//if( exit_type_closed == state_object_exits_type )
	//{
	//	return collision;
	//}

	// Vertical.
	if( EXIT_SPOT2 == tileX || EXIT_SPOT3 == tileX )
	{
		if( ( EXIT_SPOT1 == tileY && direction_type_upxx == direction ) || ( EXIT_SPOT4 == tileY && direction_type_down == direction ) )
		{
			can_go_thru_exit = exit_type_closed == state_object_exits_type ? coll_type_empty : coll_type_block;
		}
	}

	// Horizontal.
	if( EXIT_SPOT2 == tileY || EXIT_SPOT3 == tileY )
	{
		if( ( EXIT_SPOT1 == tileX && direction_type_left == direction ) || ( EXIT_SPOT4 == tileX && direction_type_rght == direction ) )
		{
			can_go_thru_exit = exit_type_closed == state_object_exits_type ? coll_type_empty : coll_type_block;
		}
	}

	return can_go_thru_exit;
}

unsigned char engine_move_manager_border_exit( unsigned char tileX, unsigned char tileY, unsigned char direction )
{
	unsigned char can_go_thru_exit = coll_type_empty;

	// Vertical.
	if( ( EXIT_SPOT1 == tileY && direction_type_upxx == direction ) || ( EXIT_SPOT4 == tileY && direction_type_down == direction ) )
	{
		can_go_thru_exit = coll_type_block;
	}

	// Horizontal.
	if( ( EXIT_SPOT1 == tileX && direction_type_left == direction ) || ( EXIT_SPOT4 == tileX && direction_type_rght == direction ) )
	{
		can_go_thru_exit = coll_type_block;
	}

	return can_go_thru_exit;
}

unsigned char engine_move_manager_inside_exit( unsigned char tileX, unsigned char tileY )
{
	unsigned char collision = coll_type_block;
	if( exit_type_closed == state_object_exits_type )
	{
		return collision;
	}

	// Vertical.
	if( EXIT_SPOT2 == tileX || EXIT_SPOT3 == tileX )
	{
		if( ( ( EXIT_SPOT1 - 1 ) == tileY ) || ( ( EXIT_SPOT4 + 1 ) == tileY ) )
		{
			collision = coll_type_empty;
		}
	}

	// Horizontal.
	if( EXIT_SPOT2 == tileY || EXIT_SPOT3 == tileY )
	{
		if( ( ( EXIT_SPOT1 - 1 ) == tileX ) || ( ( EXIT_SPOT4 + 1 ) == tileX ) )
		{
			collision = coll_type_empty;
		}
	}

	return collision;
}

unsigned char engine_move_manager_opposite_direction( unsigned char direction )
{
	if( direction_type_left == direction )
	{
		return direction_type_rght;
	}
	else if( direction_type_rght == direction )
	{
		return direction_type_left;
	}
	else if( direction_type_upxx == direction )
	{
		return direction_type_down;
	}
	else if( direction_type_down == direction )
	{
		return direction_type_upxx;
	}

	return direction_type_none;
}