#include "option_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\state_manager.h"
#include "..\devkit\_sms_manager.h"

void screen_option_screen_load()
{
	devkit_SMS_displayOff();

	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();

	//engine_font_manager_draw_text( "OPTION SCREEN....!!", 2, 10 );

	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	engine_memo_manager_option();
	engine_board_manager_toggle();

	devkit_SMS_displayOn();
}

void screen_option_screen_update( unsigned char *screen_type )
{
	/*struct_state_object *st = &global_state_object;
	unsigned char input;

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		st->state_object_exits_type = 1 - st->state_object_exits_type;
		engine_board_manager_toggle();
	}

	input = engine_input_manager_hold( input_type_fire2 );
	if( input )
	{
		st->state_object_trees_type = 1 - st->state_object_trees_type;
		engine_board_manager_border( border_type_game );
	}*/

	//*screen_type = screen_type_select;
	*screen_type = screen_type_option;
}