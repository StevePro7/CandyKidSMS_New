#include "title_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"

static unsigned char first_time;

void screen_title_screen_load()
{
	//engine_font_manager_draw_text( "TITLE SCREEN!!!", 4, 0 );

	//engine_command_manager_init();
	engine_delay_manager_load( 0 );
	engine_delay_manager_load( 0 );
	//engine_delay_manager_draw();
	//engine_frame_manager_draw();

	engine_board_manager_main_full();
	first_time = 1;
}

void screen_title_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_title;
}