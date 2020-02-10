#include "board_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "mask_manager.h"
#include "move_manager.h"
//#include "tile_manager.h"
#include "..\banks\databank.h"
//#include <stdio.h>
//
////#define TOP_EXIT_Y		6
////#define BOT_EXIT_Y		16
//// Global variable.
////struct_board_object global_board_object;
//
//static void draw_side( unsigned char wide, unsigned char right );
//static void draw_gaps( unsigned char left, unsigned char midd, unsigned char right );
//
// Methods.
void engine_board_manager_init()
{
	//struct_board_object *bo = &global_board_object;
	unsigned char row, col;
	unsigned char test_type;
	unsigned char direction;
	unsigned char index;

	// Initialize 14x14 board.
	for( row = 0; row < MAZE_ROWS; row++ )
	{
		//for( col = 0; col < lo->load_cols; col++ )
		for( col = 0; col < MAZE_COLS; col++ )
		{
			index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
			level_object_drawtiles_array[ index ] = coll_type_empty;
		}
	}

	// Calculate 12x12 outside tree border.
	// Set border to tree and collision = 1
	test_type = tile_type_trees | COLL_TYPE_MASK;
	for( col = 0; col < TREE_COLS; col++ )
	{
		index = MAZE_ROWS * 1 + (col + 1);
		level_object_drawtiles_array[ index ] = test_type;
	
		index = MAZE_ROWS * ( MAZE_ROWS - 2 ) + ( col + 1 );
		level_object_drawtiles_array[ index ] = test_type;
	}
	for( row = 1; row < TREE_ROWS - 1; row++ )
	{
		index = ( row + 1 ) * MAZE_COLS + 1;
		level_object_drawtiles_array[ index ] = test_type;

		index = ( row + 1 ) * MAZE_COLS + ( MAZE_COLS - 2 );
		level_object_drawtiles_array[ index ] = test_type;
	}


	index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
	test_type = level_object_drawtiles_array[ index ];
	engine_font_manager_draw_data( test_type, 10, 4 );

	// Calculate 2px border movement options.
	row = 1;
	col = 1;

	// Calculate any direction around this tile.
	direction = engine_move_manager_test_direction( row, col );


	index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
	test_type = level_object_drawtiles_array[ index ];

	engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
	level_object_drawtiles_array[ index ] = test_type;
	

	index = ( row + 0 ) * MAZE_COLS + ( col + 0 );
	test_type = level_object_drawtiles_array[ index ];
	engine_font_manager_draw_data( test_type, 10, 6 );

	//for( col = 0; col < MAZE_COLS; col++ )
}
//
//void engine_board_manager_set_exit_type( unsigned char exit_type )
//{
//	//struct_board_object *bo = &global_board_object;
//	//bo->save_exit_type = exit_type;
//}
//
//void engine_board_manager_set_tree_type( unsigned char tree_type )
//{
//	//struct_board_object *bo = &global_board_object;
//	//bo->save_tree_type = tree_type;
//}
//
//void engine_board_manager_calc_position( unsigned char *tileX, unsigned char *tileY, unsigned char tileZ )
//{
//	//*tileX = tileZ % MAZE_COLS;
//	//*tileY = tileZ / MAZE_ROWS;
//}
//void engine_board_manager_calc_tileSpot( unsigned char tileX, unsigned char tileY, unsigned char *tileZ )
//{
//	//*tileZ = tileY * MAZE_ROWS + tileX;
//}
//
//void engine_board_manager_draw_full()
//{
//	//struct_board_object *bo = &global_board_object;
//	//draw_side( TREE_COLS, bo->right2 );
//}
//void engine_board_manager_draw_exit()
//{
//	//struct_board_object *bo = &global_board_object;
//	//draw_gaps( TOP_EXIT_Y, BOT_EXIT_Y, bo->right2 );
//}
//
//void engine_board_manager_main_full()
//{
//	//struct_board_object *bo = &global_board_object;
//	//draw_side( SCREEN_TILE_WIDE - 1, bo->right );
//}
//void engine_board_manager_main_exit()
//{
//	//struct_board_object *bo = &global_board_object;
//	//draw_gaps( 8, 20, bo->right );
//}
//
//// This is the function that draws opaque tile to hide Kid when moving thru exit!
//void engine_board_manager_side_tile()
//{
//	//engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, TOP_EXIT_Y );
//	//engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, BOT_EXIT_Y );
//
//	//engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, BOT_EXIT_Y );
//	//engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, TOP_EXIT_Y );
//}
//
//// TODO - delete!!
//void engine_board_manager_debugger()
//{
//	//struct_board_object *bo = &global_board_object;
//	//unsigned char type = bo->save_tree_type;
//
//	//unsigned char spot[] = { 1, 2, 4, 7, 9, 10 };
//	//unsigned char loop;
//	//for( loop = 0; loop < 6; loop++ )
//	////for( loop = 0; loop < 2; loop++ )
//	//{
//	//	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + spot[ loop ] * 2, 0 );
//	//	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + spot[ loop ] * 2, 22 );
//
//	//	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT, spot[ loop ] * 2 );
//	//	engine_tile_manager_main_trees( type, SCREEN_TILE_LEFT + 22, spot[ loop ] * 2 );
//	//}
//}
//// TODO - delete!!
//
//static void draw_side( unsigned char wide, unsigned char right )
//{
//	//struct_board_object *bo = &global_board_object;
//	//unsigned char type = bo->save_tree_type;
//	//unsigned char loop;
//
//	//for( loop = 0; loop < wide; loop++ )
//	//{
//	//	engine_tile_manager_main_trees( type, bo->left + loop * 2, bo->top );
//	//	engine_tile_manager_main_trees( type, bo->left + loop * 2, bo->bottom );
//	//}
//	//for( loop = 1; loop < SCREEN_TILE_HIGH - 1; loop++ )
//	//{
//	//	engine_tile_manager_main_trees( type, bo->left, bo->top + loop * 2 );
//	//	engine_tile_manager_main_trees( type, right, bo->top + loop * 2 );
//	//}
//}
//static void draw_gaps( unsigned char left, unsigned char midd, unsigned char right )
//{
//	//struct_board_object *bo = &global_board_object;
//	//unsigned char type = bo->save_tree_type;
//	//if( exit_type_closed == bo->save_exit_type )
//	//{
//	//	engine_tile_manager_main_trees(  type,SCREEN_TILE_LEFT + left, bo->top );
//	//	engine_tile_manager_main_trees(  type,SCREEN_TILE_LEFT + midd, bo->top );
//	//	engine_tile_manager_main_trees(  type,SCREEN_TILE_LEFT + left, bo->bottom );
//	//	engine_tile_manager_main_trees(  type,SCREEN_TILE_LEFT + midd, bo->bottom );
//
//	//	// Hard code top and bottom exits as they never move!
//	//	engine_tile_manager_main_trees(  type,bo->left, 6 );
//	//	engine_tile_manager_main_trees(  type,bo->left, 16 );
//	//	engine_tile_manager_main_trees(  type,right, 6 );
//	//	engine_tile_manager_main_trees(  type,right, 16 );
//
//	//	return;
//	//}
//
//	//// Otherwise "draw" exits as blank tiles.
//	//engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + left, bo->top );
//	//engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + midd, bo->top );
//	//engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + left, bo->bottom );
//	//engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + midd, bo->bottom );
//
//	//// Hard code top and bottom exits as they never move!
//	//engine_tile_manager_draw_blank( bo->left, TOP_EXIT_Y );
//	//engine_tile_manager_draw_blank( bo->left, BOT_EXIT_Y );
//	//engine_tile_manager_draw_blank( right, TOP_EXIT_Y );
//	//engine_tile_manager_draw_blank( right, BOT_EXIT_Y );
//}