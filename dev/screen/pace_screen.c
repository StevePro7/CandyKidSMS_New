#include "pace_screen.h"
//#include "..\engine\audio_manager.h"
//#include "..\engine\board_manager.h"
//#include "..\engine\content_manager.h"
//#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
//#include "..\engine\global_manager.h"
//#include "..\engine\input_manager.h"
//#include "..\engine\locale_manager.h"
//#include "..\engine\memo_manager.h"
//#include "..\engine\tile_manager.h"
//#include "..\engine\timer_manager.h"
//#include "..\devkit\_sms_manager.h"
//#include "..\banks\fixedbank.h"
//#include "..\banks\databank.h"
//
////
////static unsigned char cursorX[ 2 ] = { TYPE1_OPT1_X, TYPE1_OPT2_X };
////static void display_cursor();
//
//static unsigned char pace_speed;
//
void screen_pace_screen_load()
{
//	engine_font_manager_draw_data( pace_speed, 10, 15 );
//	engine_font_manager_draw_data( state_object_pace_speed, 10, 10 );
//	pace_speed = state_object_pace_speed;
//	engine_font_manager_draw_data( pace_speed, 10, 16 );
//
//	engine_cursor_manager_draw1( 3 );
//	engine_cursor_manager_cursor1( pace_speed );
//
//
//	engine_font_manager_draw_text( "PACE SCREEN", 7, 7 );
}

void screen_pace_screen_update( unsigned char *screen_type )
{
//	//unsigned char input;
//	unsigned char input[ 4 ] = { 0, 0, 0, 0 };
//	//unsigned char steve;
//	input[ 0 ] = engine_input_manager_hold( input_type_left );
//	input[ 1 ] = engine_input_manager_hold( input_type_right );
//	if( input[ 0 ] || input[ 1 ] )
//	{
//		engine_font_manager_draw_data( pace_speed, 10, 15 );
//		pace_speed = 1 - pace_speed;
//		//state_object_pace_speed = 1 - state_object_pace_speed;
//		//engine_cursor_manager_cursor1( state_object_pace_speed );
//		engine_cursor_manager_cursor1( pace_speed );
//		engine_font_manager_draw_data( pace_speed, 10, 16 );
//	}
//
//	input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
//	if( input[ 2 ] )
//	{
//		// TODO there may need to be a slight delay going to next screen
//		// because I will clear the screen and reload game tiles...
//		engine_audio_manager_sfx_play( sound_type_accept );
//		state_object_pace_speed = pace_speed;
//		*screen_type = screen_type_option;
//		return;
//	}
//
//	input[ 3 ] = engine_input_manager_hold( input_type_fire2 );
//	if( input[ 3 ] )
//	{
//		engine_audio_manager_sfx_play( sfx_type_reset );
//		*screen_type = screen_type_diff;
//		return;
//	}
//
//	//steve = engine_input_manager_hold( input_type_fire1 );
//	//if( steve )
//	//{
//	//	engine_font_manager_draw_text( "...FIRE2...", 8, 8 );
//	//	engine_font_manager_draw_data( pace_speed, 10, 17 );
//
//	//	state_object_pace_speed = pace_speed;
//	//	engine_font_manager_draw_data( pace_speed, 10, 18 );
//	//	*screen_type = screen_type_option;
//	//	return;
//	//}
//
	*screen_type = screen_type_pace;
//	//*screen_type = screen_type_option;
}
////
////static void display_cursor()
////{
////	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, TYPE1_OPT1_X, TYPE1_TEXT_Y + 1 );
////	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, TYPE1_OPT2_X, TYPE1_TEXT_Y + 1 );
////	engine_font_manager_draw_text( LOCALE_SELECT_ARROW, cursorX[ state_object_difficulty ], TYPE1_TEXT_Y + 1 );
////}