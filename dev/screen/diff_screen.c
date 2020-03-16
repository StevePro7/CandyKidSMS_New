#include "diff_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"

//static unsigned char cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };
//static void display_cursor();

static unsigned char difficulty;
static unsigned char event_stage;

void screen_diff_screen_load()
{
	//engine_font_manager_draw_data( difficulty, 10, 15 );
	//engine_font_manager_draw_data( state_object_difficulty, 10, 10 );

	difficulty = state_object_difficulty;
	event_stage = event_stage_start;

	//engine_font_manager_draw_data( difficulty, 10, 16 );
	//devkit_SMS_mapROMBank( FIXED_BANK );

	engine_cursor_manager_draw1( 0 );
	//engine_cursor_manager_cursor1( state_object_difficulty );
	engine_cursor_manager_cursor1( difficulty );

	engine_delay_manager_load( SOUND_SCREEN_DELAY );
}

void screen_diff_screen_update( unsigned char *screen_type )
{
	unsigned char input[ 4 ] = { 0, 0, 0, 0 };
	unsigned char delay;

	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			*screen_type = screen_type_title;
			return;
		}
	}

	input[ 0 ] = engine_input_manager_hold( input_type_left );
	input[ 1 ] = engine_input_manager_hold( input_type_right );
	if( input[ 0 ] || input[ 1 ] )
	{
		//state_object_difficulty = 1 - state_object_difficulty;
		difficulty = 1 - difficulty;
		//engine_cursor_manager_cursor1( state_object_difficulty );
		engine_cursor_manager_cursor1( difficulty );
	}

	input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 2 ] )
	{
		engine_audio_manager_sfx_play( sound_type_accept );
		state_object_difficulty = difficulty;
		//*screen_type = screen_type_pace;
		//*screen_type = screen_type_init;
		//*screen_type = screen_type_option;
		//*screen_type = screen_type_intro;
		*screen_type = screen_type_fast;
		return;
	}

	input[ 3 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 3 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_reset );
		state_object_difficulty = difficulty;
		event_stage = event_stage_pause;
		//*screen_type = screen_type_title;
		return;
	}

	*screen_type = screen_type_diff;
}


//static void display_cursor()
//{
//	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, TYPE1_OPT1_X, TYPE1_TEXT_Y + 1 );
//	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, TYPE1_OPT2_X, TYPE1_TEXT_Y + 1 );
//	engine_font_manager_draw_text( LOCALE_SELECT_ARROW, cursorX[ state_object_pace_speed ], TYPE1_TEXT_Y + 1 );
//}