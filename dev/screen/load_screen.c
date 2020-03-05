#include "load_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

#define LOAD_SCREEN_DELAY	250

void screen_load_screen_load()
{
	engine_delay_manager_load( 0 );

	devkit_SMS_displayOff();

	// Reset all score data.
	engine_score_manager_load();

	devkit_SMS_displayOn();


	engine_score_manager_load();

	engine_level_manager_load_level( state_object_world_data, state_object_round_data );
	engine_level_manager_draw_level();
}

void screen_load_screen_update( unsigned char *screen_type )
{
	

	*screen_type = screen_type_load;
}