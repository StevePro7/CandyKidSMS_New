#include "ready_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

#define READY_SCREEN_DELAY	0
//#define READY_SCREEN_DELAY	15
//#define READY_SCREEN_DELAY	1

void screen_ready_screen_load()
{
	state_object_curr_screen = screen_type_ready;
	state_object_next_screen = screen_type_play;

	engine_delay_manager_load( READY_SCREEN_DELAY );

	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();
}

void screen_ready_screen_update( unsigned char *screen_type )
{
	unsigned char delay;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	// TODO - detect movement U / D / L / R as input to move this along to play screen.
	delay = engine_delay_manager_update();
	if( delay )
	{
		// TODO stevepro hardcode
		//devkit_SMS_mapROMBank( 7 );
		engine_audio_manager_music_resume();
		//engine_audio_manager_music_play( music_type_title );
		//engine_audio_manager_music_play( music_type_game03 );
		*screen_type = state_object_next_screen;
		return;
	}

	*screen_type = state_object_curr_screen;
}
