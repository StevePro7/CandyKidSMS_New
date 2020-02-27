#include "board_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "level_manager.h"
#include "locale_manager.h"
#include "mask_manager.h"
#include "tile_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"

#define TOP_SIDE_Y		0
#define BOT_SIDE_Y		22

#define LFT_SIDE_X		0
#define MID_SIDE_X		22
#define RGT_SIDE_X		28

#define TOP_EXIT_Y		6
#define BOT_EXIT_Y		16

static void draw_side( unsigned char wide, unsigned char right );
static void draw_gaps( unsigned char left, unsigned char midd, unsigned char right );

// Methods.
void engine_board_manager_init()
{
	unsigned char borders[] = { 0, 1, MAZE_ROWS - 2, MAZE_ROWS - 1 };
	unsigned char row, col;
	unsigned char test_type;
	unsigned char direction;
	unsigned char index;
	unsigned char loop;

	// Initialize 14x14 board.
	for( row = 0; row < MAZE_ROWS; row++ )
	{
		//for( col = 0; col < lo->load_cols; col++ )
		for( col = 0; col < MAZE_COLS; col++ )
		{
			index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
			level_object_tiles_array[ index ] = coll_type_empty;
		}
	}

	// Calculate 12x12 outside tree border.
	// Set border to tree and collision = 1
	test_type = tile_type_trees | COLL_TYPE_MASK;
	for( col = 0; col < TREE_COLS; col++ )
	{
		index = MAZE_ROWS * 1 + (col + 1);
		level_object_tiles_array[ index ] = test_type;
	
		index = MAZE_ROWS * ( MAZE_ROWS - 2 ) + ( col + 1 );
		level_object_tiles_array[ index ] = test_type;
	}
	for( row = 1; row < TREE_ROWS - 1; row++ )
	{
		index = ( row + 1 ) * MAZE_COLS + 1;
		level_object_tiles_array[ index ] = test_type;

		index = ( row + 1 ) * MAZE_COLS + ( MAZE_COLS - 2 );
		level_object_tiles_array[ index ] = test_type;
	}

	// Calculate 2px border movement options.
	// Horizontal.
	for( loop = 0; loop < NUM_DIRECTIONS; loop++ )
	{
		row = borders[ loop ];
		for( col = 0; col < MAZE_COLS; col++ )
		{
			direction = engine_level_manager_test_direction( row, col );

			index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
			test_type = level_object_tiles_array[ index ];

			engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
			level_object_tiles_array[ index ] = test_type;
		}
	}

	// Vertical.
	for( loop = 0; loop < NUM_DIRECTIONS; loop++ )
	{
		col = borders[ loop ];
		for( row = 2; row < MAZE_ROWS - 2; row++ )
		{
			direction = engine_level_manager_test_direction( row, col );

			index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
			test_type = level_object_tiles_array[ index ];

			engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
			level_object_tiles_array[ index ] = test_type;
		}
	}
}

void engine_board_manager_draw_full()
{
	draw_side( TREE_COLS, MID_SIDE_X );
}
void engine_board_manager_draw_exit()
{
	draw_gaps( TOP_EXIT_Y, BOT_EXIT_Y, MID_SIDE_X );
}

void engine_board_manager_main_full()
{
	draw_side( SCREEN_TILE_WIDE - 1, RGT_SIDE_X );
}
void engine_board_manager_main_exit()
{
	draw_gaps( 8, 20, RGT_SIDE_X );
}

// This is the function that draws opaque tile to hide Kid when moving through exit!
void engine_board_manager_side_tile()
{
	engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, TOP_EXIT_Y );
	engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, BOT_EXIT_Y );

	engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, BOT_EXIT_Y );
	engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, TOP_EXIT_Y );
}

void engine_board_manager_midd_text()
{
	unsigned char type = state_object_trees_type;
	unsigned char loop;

	for( loop = 0; loop < 6; loop++ )
	{
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 6 + loop * 2, TOP_SIDE_Y + 8 );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 6 + loop * 2, TOP_SIDE_Y + 14 );
	}

	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 6, TOP_SIDE_Y + 10 );
	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 6, TOP_SIDE_Y + 12 );
	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 16, TOP_SIDE_Y + 10 );
	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + 16, TOP_SIDE_Y + 12 );

	for( loop = 0; loop < 4; loop++ )
	{
		engine_font_manager_draw_text( LOCALE_BLANK_SIZE8, SCREEN_TILE_LEFT + LFT_SIDE_X + 8, TOP_SIDE_Y + 10 + loop );
	}
}

// TODO - delete!!
void engine_board_manager_debugger()
{
	unsigned char type = state_object_trees_type;

	unsigned char spot[] = { 1, 2, 4, 7, 9, 10 };
	unsigned char loop;
	for( loop = 0; loop < 6; loop++ )
	//for( loop = 0; loop < 2; loop++ )
	{
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + spot[ loop ] * 2, 0 );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + spot[ loop ] * 2, 22 );

		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT, spot[ loop ] * 2 );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + 22, spot[ loop ] * 2 );
	}
}
// TODO - delete!!

static void draw_side( unsigned char wide, unsigned char right )
{
	unsigned char type = state_object_trees_type;
	unsigned char loop;

	for( loop = 0; loop < wide; loop++ )
	{
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + loop * 2, TOP_SIDE_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + loop * 2, BOT_SIDE_Y );
	}
	for( loop = 1; loop < SCREEN_TILE_HIGH - 1; loop++ )
	{
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X, TOP_SIDE_Y + loop * 2 );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + right, TOP_SIDE_Y + loop * 2 );
	}
}
static void draw_gaps( unsigned char left, unsigned char midd, unsigned char right )
{
	unsigned char type = state_object_trees_type;
	if( exit_type_closed == state_object_exits_type )
	{
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + left, TOP_SIDE_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + midd, TOP_SIDE_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + left, BOT_SIDE_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + midd, BOT_SIDE_Y );

		// Hard code top and bottom exits as they never move!
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X, TOP_EXIT_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X, BOT_EXIT_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + right, TOP_EXIT_Y );
		engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + right, BOT_EXIT_Y );
		return;
	}

	// Otherwise "draw" exits as blank tiles.
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + left, TOP_SIDE_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + midd, TOP_SIDE_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + left, BOT_SIDE_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + midd, BOT_SIDE_Y );

	// Hard code top and bottom exits as they never move!
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + LFT_SIDE_X, TOP_EXIT_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + LFT_SIDE_X, BOT_EXIT_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + right, TOP_EXIT_Y );
	engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + right, BOT_EXIT_Y );
}