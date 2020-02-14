#include "test_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\function_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

void screen_test_screen_load()
{
	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
	unsigned char index = 0;
	unsigned char byte = 0;
	unsigned char list = 0;
	unsigned char half = 0;
	unsigned char upper_nibble = 0;
	unsigned char lower_nibble = 0;
	engine_font_manager_draw_text( "TEST SCREEN", 4, 10 );

	engine_board_manager_init();

	// xDist = 0;	List = 3; Half = 1;		Byte = 49.
	//byte = engine_move_manager_find_direction( 18, 14, 18, 23 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// yDist = 0;	List = 0; Half = 1;		Byte = 1.
	//byte = engine_move_manager_find_direction( 15, 23, 18, 23 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// Index = 0;	List = 0; Half = 0;		Byte = 0.
	//byte = engine_move_manager_find_direction( 18, 11, 27, 7 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );
	

	// Index = 1;	List = 0; Half = 1;		Byte = 1.
	//byte = engine_move_manager_find_direction( 21, 1, 26, 1 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// Index = 2;	List = 1; Half = 0;		Byte = 16.
	//byte = engine_move_manager_find_direction( 18, 11, 6, 5 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );

	// Index = 3;	List = 1; Half = 1;		Byte = 17.
	//byte = engine_move_manager_find_direction( 26, 5, 21, 5 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// Index = 4;	List = 2; Half = 0;		Byte = 32.
	//byte = engine_move_manager_find_direction( 18, 14, 21, 5 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );

	// Index = 5;	List = 2; Half = 1;		Byte = 33.
	//byte = engine_move_manager_find_direction( 9, 11, 13, 23 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// Index = 6;	List = 3; Half = 0;		Byte = 48.
	//byte = engine_move_manager_find_direction( 21, 14, 21, 5 );
	//engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );

	// Index = 7;	List = 3; Half = 1;		Byte = 49.
	byte = engine_move_manager_find_direction( 18, 11, 13, 23 );
	engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );


	// Print out results.
	engine_font_manager_draw_data( upper_nibble, 20, 8 );
	engine_font_manager_draw_data( lower_nibble, 20, 9 );

	//engine_font_manager_draw_data( directions[ 0 ], 20, 11 );
	//engine_font_manager_draw_data( directions[ 1 ], 20, 12 );
	//engine_font_manager_draw_data( directions[ 2 ], 20, 13 );
	//engine_font_manager_draw_data( directions[ 3 ], 20, 14 );

	list = upper_nibble;
	half = lower_nibble;

	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;
	devkit_SMS_mapROMBank( FIXED_BANK );
	directions[ 0 ] = enemy_object_directions[ index + 0 ];
	directions[ 1 ] = enemy_object_directions[ index + 1 ];
	directions[ 2 ] = enemy_object_directions[ index + 2 ];
	directions[ 3 ] = enemy_object_directions[ index + 3 ];

	engine_font_manager_draw_data( directions[ 0 ], 20, 11 );
	engine_font_manager_draw_data( directions[ 1 ], 20, 12 );
	engine_font_manager_draw_data( directions[ 2 ], 20, 13 );
	engine_font_manager_draw_data( directions[ 3 ], 20, 14 );

	//engine_font_manager_draw_data( directions[ 0 ], 20, 16 );
	//engine_font_manager_draw_data( directions[ 1 ], 20, 17 );
	//engine_font_manager_draw_data( directions[ 2 ], 20, 18 );
	//engine_font_manager_draw_data( directions[ 3 ], 20, 19 );
}

void screen_test_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_test;
}