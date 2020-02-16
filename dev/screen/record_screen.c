#include "record_screen.h"
#include "..\banks\databank.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\storage_manager.h"

//static unsigned char first_time;
//static unsigned char my_command;

void screen_record_screen_load()
{
	unsigned char test;

	engine_font_manager_draw_text( "RECORD SCREEN...!!", 4, 0 );
	engine_frame_manager_draw();
	engine_delay_manager_draw();
	//first_time = 1;

	test = engine_storage_manager_available();
	if( test )
	{
		engine_storage_manager_read();

		engine_font_manager_draw_long( state_object_high_score, 22, 1 );

		engine_font_manager_draw_data( state_object_trees_type, 22, 3 );
		engine_font_manager_draw_data( state_object_exits_type, 22, 4 );
		engine_font_manager_draw_data( state_object_difficulty, 22, 5 );
		engine_font_manager_draw_data( state_object_game_speed, 22, 6 );

		engine_font_manager_draw_data( state_object_world_data, 22, 8 );
		engine_font_manager_draw_data( state_object_round_data, 22, 9 );
		engine_font_manager_draw_data( state_object_music_data, 22, 10 );
		engine_font_manager_draw_data( state_object_sound_data, 22, 11 );
	}

	engine_font_manager_draw_data( test, 22, 15 );
	//my_command = 1;
}

void screen_record_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		engine_font_manager_draw_text( "SAVING...", 4, 3 );

		state_object_high_score = 98765;

		state_object_trees_type = 1;
		state_object_exits_type = 0;
		state_object_difficulty = 2;
		state_object_game_speed = 3;

		state_object_world_data = 7;
		state_object_round_data = 8;
		state_object_music_data = 5;
		state_object_sound_data = 6;

		engine_storage_manager_write();


		engine_font_manager_draw_text( "SAVED..!!", 4, 4 );
	}
	//first_time = 0;

	*screen_type = screen_type_record;
}