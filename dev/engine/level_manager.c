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
static void draw_tiles( unsigned char x, unsigned char y, unsigned char multipler );
//
//void engine_level_manager_init_board()
//{
//	struct_level_object *lo = &global_level_object;
//	unsigned char index, row, col;
//
//	// Initialize 14x14 maze.
//	for( row = 0; row < MAZE_ROWS; row++ )
//	{
//		for( col = 0; col < MAZE_COLS; col++ )
//		{
//			index = row * MAZE_COLS + col;
//
//			lo->drawtiles_array[ index ] = tile_type_blank;
//			lo->collision_array[ index ] = coll_type_empty;
//			lo->direction_array[ index ] = direction_type_none;
//		}
//	}
//
//	// Calculate 12x12 outside tree border.
//	for( col = 0; col < TREE_COLS; col++ )
//	{
//		index = MAZE_ROWS * 1 + (col + 1);
//		lo->drawtiles_array[ index ] = tile_type_trees;
//		lo->collision_array[ index ] = coll_type_block;
//
//		index = MAZE_ROWS * ( MAZE_ROWS - 2 ) + ( col + 1 );
//		lo->drawtiles_array[ index ] = tile_type_trees;
//		lo->collision_array[ index ] = coll_type_block;
//	}
//	for( row = 1; row < TREE_ROWS - 1; row++ )
//	{
//		index = ( row + 1 ) * MAZE_COLS + 1;
//		lo->drawtiles_array[ index ] = tile_type_trees;
//		lo->collision_array[ index ] = coll_type_block;
//
//		index = (row + 1) * MAZE_COLS + ( MAZE_COLS - 2 );
//		lo->drawtiles_array[ index ] = tile_type_trees;
//		lo->collision_array[ index ] = coll_type_block;
//	}
//}
//
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
	//devkit_SMS_mapROMBank( FIXEDBANKSLOT );
	changeBank( FIXED_BANK );
	if( level < halve )
	{
		const unsigned char *data = level_object_AAdata[ index ];
		const unsigned char size = level_object_AAsize[ index ];
		const unsigned char bank = level_object_AAbank[ index ];
		
		// TODO implement changeBank so not hard coding
		//devkit_SMS_mapROMBank( 2 );
		//engine_font_manager_draw_data( *data, 20, 19 );
		//engine_font_manager_draw_data( size, 20, 20 );
		//engine_font_manager_draw_data( bank, 20, 21 );
		
		load_level( data, size, bank, mult );
	}
//	else
//	{
//		const unsigned char *data = levelBBdata[ index ];
//		const unsigned char bank = levelBBbank[ index ];
//		const unsigned char size = levelBBsize[ index ];
	//load_level( data, size, bank, mult );
//	}
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
			//draw_tiles( col, row, lo->multiplier );
			draw_tiles( col, row, 2 );
		}
	}
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
//unsigned char engine_level_manager_get_next_tile( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
//{
//	struct_level_object *lo = &global_level_object;
//	unsigned char tile;
//
//	// Note: x and y can never go out-of-bounds: if gamer in exits then there will be no collision checks.
//	if( direction_type_upxx == direction )
//	{
//		y -= offset;
//	}
//	else if( direction_type_down == direction )
//	{
//		y += offset;
//	}
//	else if( direction_type_left == direction )
//	{
//		x -= offset;
//	}
//	else if( direction_type_rght == direction )
//	{
//		x += offset;
//	}
//
//	engine_board_manager_calc_tileSpot( x, y, &tile );
//	return tile;
//}
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
	unsigned char directions[] = { direction_type_upxx, direction_type_down, direction_type_left, direction_type_rght };
	//struct_level_object *lo = &global_level_object;

	const unsigned char *o = data;
	unsigned char row, col;
	unsigned char tile_data;

	unsigned int index;
	unsigned char tile_type;
	unsigned char coll_type;
//	unsigned char dirX_type;
//	unsigned char direction;

	unsigned char load_cols;
	unsigned char draw_cols;
	load_cols = size / MAX_ROWS;
	draw_cols = load_cols - CRLF;
	//lo->load_cols = size / MAX_ROWS;
	//lo->draw_cols = lo->load_cols - CRLF;

	//lo->candyCount = 0;
	//lo->bonusCount = 0;
	//lo->multiplier = mult;

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

				//lo->drawtiles_array[ index ] = tile_type;
				

				//if( tile_type_candy == tile_type )
				//{
				//	//lo->candyCount++;
				//}
				//if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
				//{
				//	//lo->bonusCount++;
				//}

				// TODO read from game object. 
				engine_tile_manager_load_coll( &coll_type, tile_data );
				if( coll_type_block == coll_type )
				{
					tile_type |= COLL_TYPE_MASK;
				}

				level_object_drawtiles_array[ index ] = tile_type;
				//lo->collision_array[ index ] = coll_type;
			}

			o++;
		}
	}

	// Subtract candy count if enemy(s) not move and candy or their board spot.
	index = 0;

	// TODO now that level loaded pre-calculate the "next" tiles for each tile.
	//for( row = 0; row < MAX_ROWS; row++ )
	//{
	//	for( col = 0; col < MAX_COLS; col++ )
	//	{
	//		unsigned char x = col + 2;
	//		unsigned char y = row + 2;

	//		dirX_type = direction_type_none;
	//		for( index = 0; index < NUM_DIRECTIONS; index++ )
	//		{
	//			direction = directions[ index ];
	//			coll_type = engine_level_manager_get_next_coll( x, y, direction );
	//			if( coll_type_empty == coll_type )
	//			{
	//				dirX_type |= direction;
	//			}
	//		}

	//		index = y * MAZE_COLS + x;
	//		lo->direction_array[ index ] = dirX_type;
	//	}
	//}

	//devkit_SMS_mapROMBank( 2 );
}

static void draw_tiles( unsigned char x, unsigned char y, unsigned char multipler )
{
	//struct_level_object *lo = &global_level_object;
	unsigned char index;
	unsigned char tile;

	index = ( y + 2 ) * MAZE_COLS + ( x + 2 );
	//tile = lo->drawtiles_array[ index ];
	tile = level_object_drawtiles_array[ index ];

	engine_tile_manager_draw_tile( tile, multipler, SCREEN_TILE_LEFT + ( x + 1 ) * 2, ( y + 1 ) * 2 );
}