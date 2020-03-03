#include "pass_screen.h"
#include "..\engine\audio_manager.h"
//#include "..\engine\board_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
//#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
//#include "..\engine\level_manager.h"
//#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"

//#define PASS_SCREEN_DELAY	50
#define PASS_SCREEN_DELAY	250

unsigned char perfect;

void screen_pass_screen_load()
{
	struct_score_object *so = &global_score_object;
	
	state_object_curr_screen = screen_type_pass;
	state_object_next_screen = screen_type_bonus;

	engine_delay_manager_load( PASS_SCREEN_DELAY );
	engine_audio_manager_music_stop();

	perfect = ( level_object_bonus_count + level_object_candy_count == so->bonus + so->candy );
	engine_memo_manager_pass( perfect );
}

// TODO combine pass + bonus screen
void screen_pass_screen_update( unsigned char *screen_type )
{
	unsigned char delay;
	unsigned char input;

	delay = engine_delay_manager_update();
	input = engine_input_manager_hold( input_type_fire2 );
	if( delay || input )
	{
		engine_audio_manager_music_stop();
		*screen_type = state_object_next_screen;
		return;
	}

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = state_object_curr_screen;
}
