#include "pass_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"

#define PASS_SCREEN_DELAY	50
//#define PASS_SCREEN_DELAY	250

void screen_pass_screen_load()
{
	engine_delay_manager_load( PASS_SCREEN_DELAY );
	engine_audio_manager_music_stop();

	engine_memo_manager_pass();
}

void screen_pass_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_pass;
}
