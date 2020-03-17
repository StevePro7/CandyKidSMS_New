#include "fast_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"

static unsigned char pace_speed;
static unsigned char event_stage;

void screen_fast_screen_load()
{
	//struct_state_object *st = &global_state_object;
	////engine_font_manager_draw_data( pace_speed, 10, 15 );
	////engine_font_manager_draw_data( state_object_pace_speed, 10, 10 );
	//pace_speed = state_object_pace_speed;
	//event_stage = event_stage_start;
	////engine_font_manager_draw_data( pace_speed, 10, 16 );

	//engine_cursor_manager_draw1( 3 );
	//engine_cursor_manager_cursor1( pace_speed );
	////unsigned char row;
	//////devkit_SMS_displayOff();

	////// TODO tweak this as needed... i.e. run on real hardware and look for any graphics glitches...!!

	////devkit_SMS_mapROMBank( FIXED_BANK );
	////for( row = 6; row < 22; row++ )
	////{
	////	//engine_font_manager_draw_text( LOCALE_BLANK_WIDTH, SCREEN_TILE_LEFT + 2, row );
	////	//engine_font_manager_draw_text( locale_object_blank26, SCREEN_TILE_LEFT + 2, row );
	////}

	////
	////engine_content_manager_load_tiles_main();
	////engine_content_manager_load_tiles_screen();
	////engine_content_manager_load_sprites_game();
	//////engine_memo_manager_clear();

	////engine_board_manager_border( border_type_main );

	////engine_board_manager_border( border_type_game );
	////engine_font_manager_draw_text( "INTRO SCREEN..!!", 4, 0 );

	engine_delay_manager_load( SOUND_SCREEN_DELAY );
}

void screen_fast_screen_update( unsigned char *screen_type )
{
	//struct_state_object *st = &global_state_object;

	////unsigned char input;
	//unsigned char input[ 4 ] = { 0, 0, 0, 0 };
	//unsigned char delay;

	//if( event_stage_pause == event_stage )
	//{
	//	delay = engine_delay_manager_update();
	//	if( delay )
	//	{
	//		*screen_type = screen_type_option;
	//		return;
	//	}
	//}

	////unsigned char steve;
	//input[ 0 ] = engine_input_manager_hold( input_type_left );
	//input[ 1 ] = engine_input_manager_hold( input_type_right );
	//if( input[ 0 ] || input[ 1 ] )
	//{
	//	//engine_font_manager_draw_data( pace_speed, 10, 15 );
	//	pace_speed = 1 - pace_speed;
	//	//state_object_pace_speed = 1 - state_object_pace_speed;
	//	//engine_cursor_manager_cursor1( state_object_pace_speed );
	//	engine_cursor_manager_cursor1( pace_speed );
	//	//engine_font_manager_draw_data( pace_speed, 10, 16 );
	//}

	//input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
	//if( input[ 2 ] )
	//{
	//	// TODO there may need to be a slight delay going to next screen
	//	// because I will clear the screen and reload game tiles...
	//	engine_audio_manager_sfx_play( sound_type_accept );
	//	state_object_pace_speed = pace_speed;
	//	event_stage = event_stage_pause;
	//	//*screen_type = screen_type_option;
	//	return;
	//}

	//input[ 3 ] = engine_input_manager_hold( input_type_fire2 );
	//if( input[ 3 ] )
	//{
	//	engine_audio_manager_sfx_play( sfx_type_reset );
	//	state_object_pace_speed = pace_speed;
	//	*screen_type = screen_type_diff;
	//	return;
	//}

	////steve = engine_input_manager_hold( input_type_fire1 );
	////if( steve )
	////{
	////	engine_font_manager_draw_text( "...FIRE2...", 8, 8 );
	////	engine_font_manager_draw_data( pace_speed, 10, 17 );

	////	state_object_pace_speed = pace_speed;
	////	engine_font_manager_draw_data( pace_speed, 10, 18 );
	////	*screen_type = screen_type_option;
	////	return;
	////}

	*screen_type = screen_type_fast;
}
