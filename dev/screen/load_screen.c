#include "load_screen.h"
//#include "..\engine\board_manager.h"
//#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
//#include "..\engine\hack_manager.h"
//#include "..\engine\gamer_manager.h"
//#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
//#include "..\engine\level_manager.h"
//#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"

// LOAD screen - test level manager load.
void screen_load_screen_load()
{
	engine_font_manager_draw_text( "LOAD SCREEN!!", 10, 10 );

	//engine_tile_manager_draw_gamer( 4, 4 );
	engine_tile_manager_main_trees( 0, 4, 4 );
	engine_tile_manager_main_bonus( tile_type_bonusC, 4, 6 );
	engine_tile_manager_draw_sides( 8, 8 );
}

void screen_load_screen_update( unsigned char *screen_type )
{
	unsigned char test;
	//unsigned char data;

	//devkit_SMS_mapROMBank( 15 );
	//data = bank15_txt[ 0 ];

	test = engine_input_manager_hold_fire1();
	if( test )
	{
		engine_tile_manager_draw_blank( 4, 4 );
	}

	*screen_type = screen_type_load;
}