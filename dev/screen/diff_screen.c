#include "diff_screen.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"

//static unsigned char cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };
//static void display_cursor();

void screen_diff_screen_load()
{
	engine_cursor_manager_draw1( 0 );
	engine_cursor_manager_cursor1( state_object_pace_speed );
}

void screen_diff_screen_update( unsigned char *screen_type )
{
	unsigned char input[ 3 ] = { 0, 0, 0 };
	input[ 0 ] = engine_input_manager_hold( input_type_left );
	input[ 1 ] = engine_input_manager_hold( input_type_right );
	if( input[ 0 ] || input[ 1 ] )
	{
		state_object_difficulty = 1 - state_object_difficulty;
		engine_cursor_manager_cursor1( state_object_difficulty );
	}

	input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 2 ] )
	{
		//engine_audio_manager_sound_accept();
		*screen_type = screen_type_pace;
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