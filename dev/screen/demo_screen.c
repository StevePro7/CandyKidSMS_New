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
	//unsigned char test;

	//engine_command_manager_init();
	engine_delay_manager_load( 0 );
	//state_object_sound_data();

	engine_board_manager_init();
	//engine_gamer_manager_init();
	//engine_enemy_manager_init();

	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();

	//engine_board_manager_debugger();
	//engine_board_manager_side_tile();

	//engine_level_manager_init_board();
	//engine_level_manager_init_exits();

	engine_level_manager_load_level( 0, 0 );
	engine_level_manager_draw_level();
	first_time = 1;

	//test = engine_storage_manager_available();
	//if( test )
	//{
	//	engine_storage_manager_read();
	//}

	//engine_font_manager_draw_data( test, 22, 7 );
	//engine_font_manager_draw_text( "DEMO SCREEN", 10, 23 );
}

void screen_demo_screen_update( unsigned char *screen_type )
{
	//struct_frame_object *fo = &global_frame_object;
	//struct_gamer_object *go = &global_gamer_object;
	//unsigned char proceed;
	////unsigned char input;
	//
	//unsigned int frame;
	//frame = fo->frame_count;
	//
	//// Draw sprites first.
	//engine_gamer_manager_draw();
	//engine_enemy_manager_draw();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();
	//if( !first_time )
	//{
	//	proceed = engine_delay_manager_update();
	//	if( !proceed )
	//	{
	//		*screen_type = screen_type_demo;
	//		return;
	//	}

	//	engine_frame_manager_update();
	//	first_time = 1;
	//}

	//frame = fo->frame_count;

	//// Move gamer.
	//if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	//{
	//	// TODO check if there is command_type_end_gamer as this signifies the end.
	//}
	//else if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	//{
	//	//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
	//	engine_gamer_manager_update();
	//}
	//if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	//{
	//	// Check collision.
	//	engine_font_manager_draw_data( frame, 17, 18 );
	//	engine_gamer_manager_stop();
	//}

	//// Execute all commands for this frame.
	//engine_command_manager_play( frame );

	//first_time = 0;
	*screen_type = screen_type_demo;
}