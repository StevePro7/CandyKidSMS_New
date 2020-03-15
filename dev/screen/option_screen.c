#include "option_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\devkit\_sms_manager.h"

void screen_option_screen_load()
{
	//devkit_SMS_displayOff();

	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();

	engine_font_manager_draw_text( "OPTION SCREEN....!!", 2, 10 );

	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	//devkit_SMS_displayOn();
}

void screen_option_screen_update( unsigned char *screen_type )
{
	//*screen_type = screen_type_init;
	*screen_type = screen_type_select;
	//*screen_type = screen_type_option;
}