#include "title_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

static void draw_tiles();

void screen_title_screen_load()
{
	unsigned char row;
	devkit_SMS_displayOff();

	// TODO tweak this as needed... i.e. run on real hardware and look for any graphics glitches...!!
	for( row = 6; row < 22; row++ )
	{
		engine_font_manager_draw_text( LOCALE_BLANK_WIDTH, SCREEN_TILE_LEFT + 2, row );
	}

	engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 6 );
	engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 7 );
	engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 16 );
	engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 17 );

	//engine_locale_manager_draw_text( LOCALE_BUILD_VERSION, SCREEN_TILE_LEFT + 24, 21 );
	engine_locale_manager_draw_text( 0, SCREEN_TILE_LEFT + 24, 21 );
	//engine_font_manager_draw_text( LOCALE_BUILD_VERSION, SCREEN_TILE_LEFT + 24, 21 );

	engine_content_manager_load_tiles_main();
	engine_board_manager_main_full();
	engine_board_manager_main_exit();
	engine_tile_manager_main_title( 2, 2 );

	

	//devkit_SMS_mapROMBank( 2 );
	draw_tiles();
	devkit_SMS_displayOn();
}

void screen_title_screen_update( unsigned char *screen_type )
{
	unsigned char input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		*screen_type = screen_type_init;
		return;
	}

	*screen_type = screen_type_title;
	//*screen_type = screen_type_option;
}

static void draw_tiles()
{
	const unsigned char multiplier = 1;
	engine_tile_manager_draw_trees( tree_type_avoid, 10, 8 );
	engine_tile_manager_draw_trees( tree_type_death, 10, 10 );

	engine_tile_manager_draw_bonus( tile_type_bonusA, 10, 12, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusB, 10, 14, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusC, 10, 16, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusD, 10, 18, multiplier );
}