#include "load_screen.h"
#include "..\engine\board_manager.h"
//#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
//#include "..\engine\hack_manager.h"
//#include "..\engine\gamer_manager.h"
//#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
//#include "..\engine\level_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"

// LOAD screen - test level manager load.
void screen_load_screen_load()
{
	engine_font_manager_draw_text( "LOAD SCREEN..!!", 10, 10 );

	//engine_tile_manager_draw_gamer( 4, 4 );
	//engine_tile_manager_main_trees( 0, 4, 4 );
	//engine_tile_manager_main_trees( 1, 8, 4 );
	//engine_tile_manager_main_bonus( tile_type_bonusA, 4, 6 );
	//engine_tile_manager_main_bonus( tile_type_bonusB, 8, 6 );
	//engine_tile_manager_main_bonus( tile_type_bonusC, 12, 6 );
	//engine_tile_manager_draw_sides( 8, 8 );
}

void screen_load_screen_update( unsigned char *screen_type )
{
	unsigned char test;
	//unsigned char data;

	//devkit_SMS_mapROMBank( 15 );
	//data = bank15_txt[ 0 ];

	engine_sprite_manager_draw_entity( 56, 64, 352 );

	test = engine_input_manager_hold( input_type_right );
	if( test )
	{
		engine_font_manager_draw_text( "HOLD", 14, 14 );
	}

	*screen_type = screen_type_load;
}