#include "func_screen.h"
//#include "..\engine\board_manager.h"
//#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
//#include "..\engine\level_manager.h"
//#include "..\engine\memo_manager.h"
#include "..\engine\sprite_manager.h"
//#include "..\engine\tile_manager.h"
//#include "..\devkit\_sms_manager.h"
//#include "..\banks\databank.h"
//#include "..\banks\fixedbank.h"

static void test_fixed();

void screen_func_screen_load()
{
	engine_font_manager_draw_text( "FUNC SCREEN.!!!", 10, 2 );
}

// TODO - in order for this to work I must have an overload for draw trees
// 	draw_tile_priority( offset, x, y );
void screen_func_screen_update( unsigned char *screen_type )
{
	unsigned char direction = direction_type_none;
	//unsigned char input[ 4 ] = { 0, 0, 0, 0 };
	unsigned char upxx;
	unsigned char down;
	unsigned char left;
	unsigned char rght;

	upxx = engine_input_manager_move( input_type_up );
	down = engine_input_manager_move( input_type_down );
	left = engine_input_manager_move( input_type_left );
	rght = engine_input_manager_move( input_type_right );

	engine_font_manager_draw_text( "    ", 10, 10 );
	engine_font_manager_draw_text( "    ", 10, 11 );
	engine_font_manager_draw_text( "    ", 10, 12 );
	engine_font_manager_draw_text( "    ", 10, 13 );
	engine_font_manager_draw_text( "    ", 10, 15 );

	if( upxx )
	{
		engine_font_manager_draw_text( "UPXX", 10, 10 );
	}
	if( down )
	{
		engine_font_manager_draw_text( "DOWN", 10, 11 );
	}
	if( left )
	{
		engine_font_manager_draw_text( "LEFT", 10, 12 );
	}
	if( rght )
	{
		engine_font_manager_draw_text( "RGHT", 10, 13 );
	}

	//if ((input[0] && input[3] ) ||
	if( ( upxx && left ) || ( down && left ) || ( upxx && rght ) || ( down && rght ) )
	{
		engine_font_manager_draw_text( "BOTH", 10, 15 );
	}

	*screen_type = screen_type_func;
}


static void test_fixed()
{
	//unsigned char x = 64;
	//unsigned char y = 56;
	// minX = 60
	// minY = 60
	// maxX = 148
	// maxY = 116
	unsigned char x = 128;
	unsigned char y = 116;
	//devkit_SMS_addSprite( x, y + 8, 256 );
	engine_sprite_manager_draw_entity( x, y, 256 + 96 );
	engine_sprite_manager_draw_entity( x, 60, 256 + 96 );

	engine_sprite_manager_draw_entity( 60, 100, 256 + 96 );
	engine_sprite_manager_draw_entity( 148, 100, 256 + 96 );

	//unsigned char enemy = actor_type_suz;
	//unsigned char index;
	//unsigned char speed;

	////index = 4 * actor + pace * 2 + diff;
	//// There are 4x permutations: Easy + Slow, 
	//index = 4 * enemy + state_object_difficulty * 2 + state_object_pace_speed;

	//devkit_SMS_mapROMBank( FIXED_BANK );
	//speed = enemy_object_speed[ index ];

	//engine_font_manager_draw_data( index, 10, 3 );
	//engine_font_manager_draw_data( speed - 1, 10, 4 );

	//engine_font_manager_draw_text( "FUNC SCREEN!", 10, 2 );

	//engine_memo_manager_option();
}