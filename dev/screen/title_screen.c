#include "title_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
//#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\tile_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"

void screen_title_screen_load()
{
	devkit_SMS_displayOff();
	engine_content_manager_load_tiles_main();
	engine_board_manager_main_full();
	engine_board_manager_main_exit();
	engine_tile_manager_main_title( 2, 2 );
	devkit_SMS_displayOn();
}

void screen_title_screen_update( unsigned char *screen_type )
{
	//unsigned char input;
	//input = engine_input_manager_hold( input_type_fire1 );
	//if( input )
	//{
	//	state_object_trees_type = 1 - state_object_trees_type;
	//	engine_board_manager_main_full();
	//	engine_board_manager_main_exit();
	//}
	//input = engine_input_manager_hold( input_type_fire2 );
	//if( input )
	//{
	//	state_object_exits_type = 1 - state_object_exits_type;
	//	engine_board_manager_main_exit();
	//}

	*screen_type = screen_type_title;
}