#include "over_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\timer_manager.h"

#define OVER_SCREEN_DELAY		275

void screen_over_screen_load()
{
	unsigned char x = SCREEN_TILE_LEFT + LFT_SIDE_X + 8;
	unsigned char y = TOP_SIDE_Y + 10;

	// TODO play game over music.
	engine_audio_manager_music_stop();
	engine_delay_manager_load( OVER_SCREEN_DELAY );
	//engine_memo_manager_draw( 24, 25 );

	engine_locale_manager_draw_text( 24, x, y + 1 );
	engine_locale_manager_draw_text( 25, x, y + 2 );

	engine_audio_manager_music_play_norepeat( music_type_over );
}

void screen_over_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	unsigned char delay;
	unsigned char index;
	unsigned char sides[] = { 6, 7, 16, 17 };

	input = engine_input_manager_hold( input_type_fire1 );
	delay = engine_delay_manager_update();
	if( delay || input )
	{
		engine_audio_manager_music_stop();

		// Not sure why have to do this here but ensures Title screen works!
		for( index = 0; index < 4; index++ )
		{
			engine_font_manager_draw_text( LOCALE_SELECT_SPACE, SCREEN_TILE_LEFT - 1, sides[ index ] );
		}

		*screen_type = screen_type_begin;
		return;
	}

	// Draw sprites last.
	engine_enemy_manager_hide();
	engine_gamer_manager_hide_death();


	*screen_type = screen_type_over;
}
