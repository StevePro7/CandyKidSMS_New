#include "diff_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"

static unsigned char event_stage;
	
void screen_diff_screen_load()
{
	struct_state_object *st = &global_state_object;

	engine_cursor_manager_draw1( 0 );
	engine_cursor_manager_update1( st->state_object_difficulty );

	engine_delay_manager_load( SOUND_SCREEN_DELAY );

	st->state_object_curr_screen = screen_type_diff;
	st->state_object_next_screen = screen_type_diff;
	event_stage = event_stage_start;

	engine_font_manager_draw_text( "DIFF SCREEN!!", 2, 10 );
}

void screen_diff_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input[ 4 ] = { 0, 0, 0, 0 };
	unsigned char delay;

	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			*screen_type = st->state_object_next_screen;
			return;
		}
	}

	input[ 0 ] = engine_input_manager_hold( input_type_left );
	input[ 1 ] = engine_input_manager_hold( input_type_right );
	if( input[ 0 ] || input[ 1 ] )
	{
		st->state_object_difficulty = 1 - st->state_object_difficulty;
		engine_cursor_manager_update1( st->state_object_difficulty );
	}

	input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 2 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_accept );
		st->state_object_next_screen = screen_type_slow;
		event_stage = event_stage_pause;
		return;
	}

	input[ 3 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 3 ] )
	{
		engine_audio_manager_sfx_play( sfx_type_reset );
		st->state_object_next_screen = screen_type_title;
		event_stage = event_stage_pause;
		return;
	}

	*screen_type = st->state_object_curr_screen;
}