#include "title_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\banks\databank.h"

void screen_title_screen_load()
{
	//engine_font_manager_draw_text( "TITLE SCREEN!!!", 4, 0 );

	//engine_command_manager_init();
	engine_delay_manager_load( 0 );
	engine_delay_manager_load( 0 );
	//engine_delay_manager_draw();
	//engine_frame_manager_draw();

	//engine_board_manager_main_full();
	//engine_board_manager_main_exit();

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
}

void screen_title_screen_update( unsigned char *screen_type )
{
	unsigned char input;
	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		state_object_exit_type = 1 - state_object_exit_type;
		engine_board_manager_draw_exit();
	}

	*screen_type = screen_type_title;
}