#include "record_screen.h"
//#include "..\engine\command_manager.h"
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
	}

	engine_font_manager_draw_data( test, 22, 7 );
	//my_command = 1;
}

void screen_record_screen_update( unsigned char *screen_type )
{
	//first_time = 0;
	*screen_type = screen_type_record;
}