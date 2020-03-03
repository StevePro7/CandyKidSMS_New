#include "bonus_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"

//#define BONUS_SCREEN_DELAY	50
#define BONUS_SCREEN_DELAY	250

void screen_bonus_screen_load()
{
	state_object_curr_screen = screen_type_pass;
	state_object_next_screen = screen_type_bonus;

	engine_delay_manager_load( BONUS_SCREEN_DELAY );
	engine_audio_manager_music_stop();
}

void screen_bonus_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_bonus;
}
