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

#define OVER_SCREEN_DELAY		250

void screen_over_screen_load()
{
	// TODO play game over music.
	engine_delay_manager_load( OVER_SCREEN_DELAY );
	engine_memo_manager_draw( 27, 28 );
}

void screen_over_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	unsigned char delay;

	input = engine_input_manager_hold( input_type_fire1 );
	delay = engine_delay_manager_update();
	if( delay || input )
	{
		engine_audio_manager_music_stop();
		*screen_type = screen_type_title;
		return;
	}

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw_death( 0 );


	*screen_type = screen_type_over;
}
