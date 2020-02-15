#include "level_manager.h"
//#include "board_manager.h"
#include "global_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "mask_manager.h"
#include "move_manager.h"
#include "tile_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"
//#include <stdlib.h>

#include "..\banks\fixedbank.h"
//
//// TODO calculate based on levels
#define MULTIPLIER_LEVEL	70
//
//// Global variable.
////struct_level_object global_level_object;
//
#define CRLF	2				// char
#define CR		'\r'			// 0x0d
#define LF		'\n'			// 0x0a
//
//// Private helper methods.
static void load_level( const unsigned char *data, const unsigned char size, const unsigned char bank, unsigned char mult );
static void draw_tiles( unsigned char x, unsigned char y );

//void engine_level_manager_init_exits()
//{
//	struct_board_object *bo = &global_board_object;
//	struct_level_object *lo = &global_level_object;
//	unsigned char loop;
//	unsigned char tmpX;
//	unsigned char tmpY;
//	unsigned char index;
//
//	// TODO test this still draws correct trees!!
//	// Want to leave coll type to block for all border trees
//	unsigned char tile_type;
//	tile_type = exit_type_public != bo->save_exit_type ? tile_type_trees : tile_type_blank;
//	//unsigned char coll_type;
//	//if( exit_type_public != bo->save_exit_type )
//	//{
//	//	tile_type = tile_type_trees;
//	//	//coll_type = coll_type_block;
//	//}
//	//else
//	//{
//	//	tile_type = tile_type_blank;
//	//	//coll_type = coll_type_empty;
//	//}
//
//	index = 0;
//	for( loop = 0; loop < MAX_EXITS_PUBLIC; loop++ )
//	{
//		tmpX = board_exitX[ loop ];
//		tmpY = board_exitY[ loop ];
//
//		index = tmpY * MAZE_ROWS + tmpX;
//		lo->drawtiles_array[ index ] = tile_type;
//		//lo->collision_array[ index ] = coll_type;
//	}
//}
//
void engine_level_manager_load_level( const unsigned char world, const unsigned char round )
{
	unsigned char halve;
	unsigned char level;
	unsigned char index;
	unsigned char mult;

	halve = TOT_WORLDS / 2 * MAX_ROUNDS;
	level = world * MAX_ROUNDS + round;
	index = 0;

	mult = ( level >= MULTIPLIER_LEVEL ) + 1;
	if( level >= halve )
	{
		index = level - halve;
	}
	else
	{
		index = level;
	}
//
	devkit_SMS_mapROMBank( FIXED_BANK );
	if( level < halve )
	{
		const unsigned char *data = level_object_AAdata[ index ];
		const unsigned char size = level_object_AAsize[ index ];
		const unsigned char bank = level_object_AAbank[ index ];
		load_level( data, size, bank, mult );
	}
	else
	{
		const unsigned char *data = level_object_BBdata[ index ];
		const unsigned char size = level_object_BBsize[ index ];
		const unsigned char bank = level_object_BBbank[ index ];
		load_level( data, size, bank, mult );
	}
}
//
void engine_level_manager_draw_level()
{
	//struct_level_object *lo = &global_level_object;
	unsigned char row, col;

	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < MAX_COLS; col++ )
		{
			draw_tiles( col, row );
		}
	}
}

void engine_level_manager_beat_level( const unsigned char *data, const unsigned char size, const unsigned char bank )
{
	load_level( data, size, bank, 1 );
}

//
//unsigned char engine_level_manager_get_tile_type( unsigned char x, unsigned char y )
//{
//	struct_level_object *lo = &global_level_object;
//	unsigned char tile;
//	unsigned char type;
//
//	engine_board_manager_calc_tileSpot( x, y, &tile );
//	type = lo->drawtiles_array[ tile ];
//	return type;
//}
////unsigned char engine_level_manager_get_collision( unsigned char x, unsigned char y, unsigned char direction ) {}
//

unsigned char engine_level_manager_get_collision( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns collision type for next (x, y) tile offset from direction.
	unsigned char collision;
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	collision = COLL_TYPE_MASK == ( tile & COLL_TYPE_MASK );
	return collision;
}
unsigned char engine_level_manager_get_direction( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns all directions for next (x, y) tile offset from direction.
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	return upper_nibble;
}
unsigned char engine_level_manager_get_tile_type( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns draw tile type for next (x, y) tile offset from direction.
	unsigned char tile_type;
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	tile_type = lower_nibble;
	if( COLL_TYPE_MASK == ( tile_type & COLL_TYPE_MASK ) )
	{
		tile_type = lower_nibble ^ COLL_TYPE_MASK;
	}

	return tile_type;
}
unsigned char engine_level_manager_get_next_tile( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	unsigned char index;

	// Note: x and y can never go out-of-bounds: if gamer in exits then there will be no collision checks.
	if( direction_type_upxx == direction )
	{
		y -= offset;
	}
	else if( direction_type_down == direction )
	{
		y += offset;
	}
	else if( direction_type_left == direction )
	{
		x -= offset;
	}
	else if( direction_type_rght == direction )
	{
		x += offset;
	}

	engine_function_manager_convertXYtoZ( MAZE_ROWS, x, y, &index );
	return level_object_tiles_array[ index ];
}
//
//unsigned char engine_level_manager_get_next_coll( unsigned char x, unsigned char y, unsigned char direction )
//{
//	struct_level_object *lo = &global_level_object;
//	unsigned char tile;
//	unsigned char type;
//
//	tile = engine_level_manager_get_next_tile( x, y, direction, offset_type_one );
//	type = lo->collision_array[ tile ];
//	return type;
//
//	//struct_level_object *lo = &global_level_object;
//	//unsigned char tile;
//	//unsigned char type;
//
//	//// Note: x and y can never go out-of-bounds as if gamer in exits then there will be no collision checks.
//	//if( direction_type_upxx == direction )
//	//{
//	//	y--;
//	//}
//	//else 	if( direction_type_down == direction )
//	//{
//	//	y++;
//	//}
//	//else if( direction_type_left == direction )
//	//{
//	//	x--;
//	//}
//	//else if( direction_type_rght == direction )
//	//{
//	//	x++;
//	//}
//
//	//engine_board_manager_calc_tileSpot( x, y, &tile );
//	//type = lo->collision_array[ tile ];
//	//return type;
//}
//
// Private helper methods.
static void load_level( const unsigned char *data, const unsigned char size, const unsigned char bank, unsigned char mult )
{
	//unsigned char directions[] = { direction_type_upxx, direction_type_down, direction_type_left, direction_type_rght };
	//struct_level_object *lo = &global_level_object;

	const unsigned char *o = data;
	unsigned char row, col;
	unsigned char tile_data;

	unsigned int index;
	unsigned char tile_type;
	unsigned char coll_type;
	unsigned char test_type;
	unsigned char direction;

	unsigned char load_cols;
	unsigned char draw_cols;
	load_cols = size / MAX_ROWS;
	draw_cols = load_cols - CRLF;

	level_object_bonus_count = 0;
	level_object_candy_count = 0;
	level_object_multiplier = mult;

	mult = 0;
	devkit_SMS_mapROMBank( bank );
	for( row = 0; row < MAX_ROWS; row++ )
	{
		//for( col = 0; col < lo->load_cols; col++ )
		for( col = 0; col < load_cols; col++ )
		{
			tile_data = *o;
			if( !( tile_data == CR || tile_data == LF ) )
			{
				engine_tile_manager_load_tile( &tile_type, tile_data );
				index = ( row + 2 ) * MAZE_COLS + ( col + 2 );

				if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
				{
					level_object_bonus_count++;
				}
				if( tile_type_candy == tile_type )
				{
					level_object_candy_count++;
				}

				engine_tile_manager_load_coll( &coll_type, tile_data );
				if( coll_type_block == coll_type )
				{
					tile_type |= COLL_TYPE_MASK;
				}

				level_object_tiles_array[ index ] = tile_type;
			}

			o++;
		}
	}

	// TODO Ensure no trees over exits!
	//if( exit_type_public == state_object_exits_type )
	//{
	//	for( row = 0; row < MAX_ROWS; row++ )
	//	{
	//		for( col = 0; col < MAX_COLS; col++ )
	//		{
	//			index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
	//		}
	//	}
	//}

	// Set each tile directions available.
	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < MAX_COLS; col++ )
		{
			direction = engine_move_manager_test_direction( ( row + 2 ), ( col + 2 ) );

			index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
			test_type = level_object_tiles_array[ index ];

			engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
			level_object_tiles_array[ index ] = test_type;
		}
	}

	// TODO - update if enemy not move and candy on home tile
	// TODO - update if there is free man candy on this level
}

static void draw_tiles( unsigned char x, unsigned char y )
{
	unsigned char index;
	unsigned char tile;

	index = ( y + 2 ) * MAZE_COLS + ( x + 2 );
	tile = level_object_tiles_array[ index ];
	engine_tile_manager_draw_tile( tile, level_object_multiplier, SCREEN_TILE_LEFT + ( x + 1 ) * 2, ( y + 1 ) * 2 );
}