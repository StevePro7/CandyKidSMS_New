#include "move_manager.h"
#include "enum_manager.h"
#include "global_manager.h"
#include "mask_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

// Private helper methods.
static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction );

unsigned char engine_move_manager_test_direction( unsigned char row, unsigned char col )
{
	unsigned char direction_type = direction_type_none;

	// Check UP.
	if( 0 != row )
	{
		unsigned char test_type = test_direction( ( col + 0 ), ( row - 1 ), direction_type_upxx );
		direction_type |= test_type;
	}

	// Check DOWN.
	if( MAZE_ROWS - 1 != row )
	{
		unsigned char test_type = test_direction( ( col + 0 ), ( row + 1 ), direction_type_down );
		direction_type |= test_type;
	}

	// Check LEFT.
	if( 0 != col )
	{
		unsigned char test_type = test_direction( ( col - 1 ), ( row + 0 ), direction_type_left );
		direction_type |= test_type;
	}

	// Check RIGHT.
	if( MAZE_COLS - 1 != col )
	{
		unsigned char test_type = test_direction( ( col + 1 ), ( row + 0 ), direction_type_rght );
		direction_type |= test_type;
	}

	return direction_type;
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

static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction )
{
	unsigned char index;
	unsigned char tiles;
	unsigned char colls;
	unsigned char test_type = direction_type_none;

	index = y * MAZE_COLS + x;
	tiles = level_object_tiles_array[ index ];

	colls = COLL_TYPE_MASK == ( tiles & COLL_TYPE_MASK );
	if( coll_type_empty == colls )
	{
		test_type = input_direction;
	}

	return test_type;
}