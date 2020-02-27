#include "demo_screen.h"
#include "..\engine\board_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
//#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
//#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\score_manager.h"

// DEMO screen - was prototyping command playback but FUNC is better. 
static unsigned char first_time;

void screen_demo_screen_load()
{
	engine_font_manager_draw_text( "DEMO SCREEN", 10, 2 );
}

void screen_demo_screen_update( unsigned char *screen_type )
{
	
	*screen_type = screen_type_demo;
}