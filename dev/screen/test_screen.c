#include "test_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\function_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

void screen_test_screen_load()
{
	unsigned char byte = 0;
	unsigned char upper_nibble = 0;
	unsigned char lower_nibble = 0;
	engine_font_manager_draw_text( "TEST SCREEN", 4, 10 );

	engine_board_manager_init();

	// xDist = 0;	Sort = 3; Half = 1;		Byte = 49.
	byte = engine_move_manager_find_direction( 18, 14, 18, 23 );
	engine_function_manager_convertByteToNibbles( byte, &upper_nibble, &lower_nibble );
}

void screen_test_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_test;
}