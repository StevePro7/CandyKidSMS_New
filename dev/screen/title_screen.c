#include "title_screen.h"
#include "..\engine\audio_manager.h"
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
#include "..\banks\databank.h"

#define TITLE_FLASH_DELAY	50
#define LOCAL_CHEAT_TOTAL	5
#define COIN_TEXT_X			6
#define COIN_TEXT_Y			18
//#define BOTT_TEXT_Y			21

//static void draw_tiles();
static unsigned char flash_count;
static unsigned char cheat_count;

void screen_title_screen_load()
{
	//unsigned char row;
	//devkit_SMS_displayOff();

	//// TODO tweak this as needed... i.e. run on real hardware and look for any graphics glitches...!!

	//devkit_SMS_mapROMBank( FIXED_BANK );
	//for( row = 6; row < 22; row++ )
	//{
	//	//engine_font_manager_draw_text( LOCALE_BLANK_WIDTH, SCREEN_TILE_LEFT + 2, row );
	//	//engine_font_manager_draw_text( locale_object_blank26, SCREEN_TILE_LEFT + 2, row );
	//}

	////for( idx = 0; idx < 4; idx++ )
	////{
	////	row = sides[ idx ];
	////	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, SCREEN_TILE_LEFT - 1, row );
	////	//engine_font_manager_draw_text( "X", SCREEN_TILE_LEFT - 1, row );
	////}



	////engine_locale_manager_draw_text( LOCALE_BUILD_VERSION, SCREEN_TILE_LEFT + 24, 21 );
	//
	////engine_font_manager_draw_text( LOCALE_BUILD_VERSION, SCREEN_TILE_LEFT + 24, 21 );

	//engine_content_manager_load_tiles_main();
	//engine_content_manager_load_tiles_screen();
	////engine_content_manager_load_sprites_game();

	////engine_board_manager_main_full();
	////engine_board_manager_main_exit();
	//engine_tile_manager_main_title( 2, 2 );
	//engine_board_manager_border( border_type_main );
	////devkit_SMS_mapROMBank( 2 );
	//draw_tiles();

	////engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 6 );
	////engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 7 );
	////engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 16 );
	////engine_font_manager_draw_text( " ", SCREEN_TILE_LEFT - 1, 17 );

	////for( idx = 0; idx < 4; idx++ )
	////{
	////	row = sides[ idx ];
	////	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, SCREEN_TILE_LEFT - 1, row );
	////	engine_font_manager_draw_text( "X", SCREEN_TILE_LEFT - 1, row );
	////}

	//engine_locale_manager_draw_text( 0, SCREEN_TILE_LEFT + 24, BOTT_TEXT_Y );
	engine_locale_manager_draw_text( 28, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y );
	engine_font_manager_draw_text( locale_object_blank18, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y + 1 );
	engine_font_manager_draw_text( locale_object_blank18, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
	//if( state_object_invincibie )
	//{
	//	engine_locale_manager_draw_text( 29, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
	//}

	//devkit_SMS_displayOn();

	engine_delay_manager_load( TITLE_FLASH_DELAY );
	state_object_localcheat = 0;
	flash_count = 0;
	cheat_count = 0;
}

void screen_title_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	unsigned char delay;

	delay = engine_delay_manager_update();
	if( delay )
	{
		if( !state_object_delay_test )
		{
			flash_count = 1 - flash_count;
		}

		if( flash_count )
		{
			devkit_SMS_mapROMBank( FIXED_BANK );
			engine_font_manager_draw_text( locale_object_blank18, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y );
		}
		else
		{
			engine_locale_manager_draw_text( 28, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y );
		}
	}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		//engine_audio_manager_sound_play( sound_type_accept );
		engine_audio_manager_sfx_play( sound_type_accept );
		//*screen_type = screen_type_select;
		//*screen_type = screen_type_diff;
		*screen_type = screen_type_intro;
		return;
	}

	if( !state_object_invincibie )
	{
		input = engine_input_manager_hold( input_type_fire2 );
		if( input )
		{
			cheat_count++;
			if( cheat_count >= LOCAL_CHEAT_TOTAL )
			{
				engine_audio_manager_sfx_play( sfx_type_power );
				engine_locale_manager_draw_text( 29, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
				state_object_localcheat = 1;
			}
		}
	}

	*screen_type = screen_type_title;
	//*screen_type = screen_type_diff;
}

//static void draw_tiles()
//{
//	const unsigned char multiplier = 1;
//	engine_tile_manager_draw_trees( tree_type_avoid, SCREEN_TILE_LEFT + 10, 8 );
//	engine_tile_manager_draw_trees( tree_type_death, SCREEN_TILE_LEFT + 10, 10 );
//
//	engine_tile_manager_draw_bonus( tile_type_bonusA, SCREEN_TILE_LEFT + 15, 8, multiplier );
//	engine_tile_manager_draw_bonus( tile_type_bonusB, SCREEN_TILE_LEFT + 15, 10, multiplier );
//	engine_tile_manager_draw_bonus( tile_type_bonusC, SCREEN_TILE_LEFT + 15, 12, multiplier );
//	engine_tile_manager_draw_bonus( tile_type_bonusD, SCREEN_TILE_LEFT + 15, 14, multiplier );
//}