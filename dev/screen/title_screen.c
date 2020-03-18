#include "title_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

#define TITLE_FLASH_DELAY	50
#define LOCAL_CHEAT_TOTAL	5
#define COIN_TEXT_X			6
#define COIN_TEXT_Y			18

//static void draw_tiles();
static unsigned char flash_count;
static unsigned char cheat_count;

void screen_title_screen_load()
{
	struct_state_object *st = &global_state_object;

	engine_locale_manager_draw_text( 28, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y );
	engine_font_manager_draw_text( locale_object_blank18, SCREEN_TILE_LEFT + COIN_TEXT_X, COIN_TEXT_Y + 1 );
	engine_font_manager_draw_text( locale_object_blank18, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );

	st->state_object_localcheat = 0;
	if( st->state_object_invincibie )
	{
		engine_locale_manager_draw_text( 29, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
		st->state_object_localcheat = 1;
	}

	engine_delay_manager_load( TITLE_FLASH_DELAY );
	flash_count = 0;
	cheat_count = 0;
}

void screen_title_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input;
	unsigned char delay;

	delay = engine_delay_manager_update();
	if( delay )
	{
		if( !st->state_object_delay_test )
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
		engine_audio_manager_sfx_play( sfx_type_accept );
		*screen_type = screen_type_hard;
		return;
	}

	if( !st->state_object_invincibie )
	{
		input = engine_input_manager_hold( input_type_fire2 );
		if( input )
		{
			cheat_count++;
			if( cheat_count >= LOCAL_CHEAT_TOTAL )
			{
				engine_audio_manager_sfx_play( sfx_type_power );
				engine_locale_manager_draw_text( 29, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
				st->state_object_localcheat = 1;
			}
		}
	}

	*screen_type = screen_type_title;
}