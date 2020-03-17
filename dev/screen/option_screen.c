#include "option_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\cursor_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\state_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

static void print_names();

void screen_option_screen_load()
{
	devkit_SMS_displayOff();

	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();

	//engine_font_manager_draw_text( "OPTION SCREEN....!!", 2, 10 );

	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	engine_memo_manager_option();
	engine_cursor_manager_draw_option();
	print_names();

	devkit_SMS_displayOn();
}

void screen_option_screen_update( unsigned char *screen_type )
{
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();
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

static void print_names()
{
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char enemy;
	unsigned char *actor;

	devkit_SMS_mapROMBank( FIXED_BANK );

	actor = ( unsigned char* ) locale_object_names[ actor_type_pro ];
	engine_font_manager_draw_text( actor, go->tileX * 2 - 1, go->tileY * 2 + 1 );

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		actor = ( unsigned char* ) locale_object_names[ enemy + 1 ];

		engine_font_manager_draw_text( actor, eo->tileX * 2 - 1, eo->tileY * 2 + 1 );
	}
}