#include "move_manager.h"
#include "enum_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "level_manager.h"
#include "mask_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

// Private helper methods.
//static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction );

unsigned char engine_move_manager_find_direction( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char enemy_direction )
{
	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
	unsigned char move_direction = direction_type_none;
	unsigned char oppX_direction = direction_type_none;
	unsigned char collision = direction_type_none;
	unsigned char index = 0;
	unsigned char byte = 0;
	unsigned char list = 0;
	unsigned char half = 0;

	// Get the list of 4x possible directions in the order depending on tiles.
	byte = engine_move_manager_get_directions( srceX, srceY, destX, destY );
	engine_function_manager_convertByteToNibbles( byte, &list, &half );

	// TODO randomly flip the half = 1 - half

	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;
	directions[ 0 ] = enemy_object_directions[ index + 0 ];
	directions[ 1 ] = enemy_object_directions[ index + 1 ];
	directions[ 2 ] = enemy_object_directions[ index + 2 ];
	directions[ 3 ] = enemy_object_directions[ index + 3 ];

	oppX_direction = engine_move_manager_opposite_direction( enemy_direction );
	for( index = 0; index < NUM_DIRECTIONS; index++ )
	{
		move_direction = directions[ index ];
		if( oppX_direction != move_direction )
		{
			collision = engine_level_manager_get_collision( srceX, srceY, move_direction, offset_type_one );
			if( coll_type_empty == collision )
			{
				break;
			}
		}
	}

	return move_direction;
}

unsigned char engine_move_manager_get_directions( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY )
{
	unsigned char deltaX = 0;
	unsigned char deltaY = 0;
	unsigned char minusY = 0;
	unsigned char plusX = 0;

	unsigned char list = 0;
	unsigned char half = 0;
	unsigned char byte = 0;

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
			list = 0;
		}
		else
		{
			list = 1;
		}
	}
	else
	{
		if( plusX )
		{
			list = 2;
		}
		else
		{
			list = 3;
		}
	}

	half = minusY ? 0 : 1;

	// Upper nibble sets list index.
	// Lower nibble sets half value.
	engine_function_manager_convertNibblesToByte( list, half, &byte );
	return byte;
}

//unsigned char engine_move_manager_test_direction( unsigned char row, unsigned char col )
//{
//	unsigned char direction_type = direction_type_none;
//
//	// Check UP.
//	if( 0 != row )
//	{
//		unsigned char test_type = test_direction( ( col + 0 ), ( row - 1 ), direction_type_upxx );
//		direction_type |= test_type;
//	}
//
//	// Check DOWN.
//	if( MAZE_ROWS - 1 != row )
//	{
//		unsigned char test_type = test_direction( ( col + 0 ), ( row + 1 ), direction_type_down );
//		direction_type |= test_type;
//	}
//
//	// Check LEFT.
//	if( 0 != col )
//	{
//		unsigned char test_type = test_direction( ( col - 1 ), ( row + 0 ), direction_type_left );
//		direction_type |= test_type;
//	}
//
//	// Check RIGHT.
//	if( MAZE_COLS - 1 != col )
//	{
//		unsigned char test_type = test_direction( ( col + 1 ), ( row + 0 ), direction_type_rght );
//		direction_type |= test_type;
//	}
//
//	return direction_type;
//}

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

//static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction )
//{
//	unsigned char index;
//	unsigned char tile;
//	unsigned char coll;
//	unsigned char test_type = direction_type_none;
//
//	index = y * MAZE_COLS + x;
//	tile = level_object_tiles_array[ index ];
//
//	coll = COLL_TYPE_MASK == ( tile & COLL_TYPE_MASK );
//	if( coll_type_empty == coll )
//	{
//		test_type = input_direction;
//	}
//
//	return test_type;
//}