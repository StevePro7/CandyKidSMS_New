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

// Private helper methods.
static void print_title();
static void print_gamer();
static void print_enemy( unsigned char enemy );

void screen_option_screen_load()
{
	unsigned char enemy;

	// Reset actors home.
	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();


	devkit_SMS_displayOff();
	engine_content_manager_load_tiles_game();
	engine_content_manager_load_tiles_screen();

	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	//. Display text.
	engine_cursor_manager_draw_titles();
	print_title();
	print_gamer();
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		print_enemy( enemy );
	}

	engine_memo_manager_option();
	engine_cursor_manager_draw2( menu_type_option );
	devkit_SMS_displayOn();
}

void screen_option_screen_update( unsigned char *screen_type )
{
	//unsigned char input;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();


	engine_cursor_manager_update2( menu_type_option );

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
	unsigned char index;

	// Gamer.
	index = 2 + actor_type_pro * 3;
	index += go->image + 1;
	engine_cursor_manager_draw_option( index, go->tileX * 2 - 1, go->tileY * 2 + 1 );

	// Enemy.
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		index = 2 + enemy * 3;
		index += eo->image + 1;
		engine_cursor_manager_draw_option( index, eo->tileX * 2 - 1, eo->tileY * 2 + 1 );
	}
}

static void print_title()
{
	devkit_SMS_mapROMBank( FIXED_BANK );

	engine_font_manager_draw_text( locale_object_option[ 0 ], TEXT_X, TEXT0_Y + 0 );
	engine_font_manager_draw_text( locale_object_option[ 1 ], TEXT_X, TEXT0_Y + 1 );
}

static void print_gamer()
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char index;

	// Gamer.
	index = 2 + actor_type_pro * 3;
	index += go->image + 1;
	engine_cursor_manager_draw_option( index, go->tileX * 2 - 1, go->tileY * 2 + 1 );
	engine_cursor_manager_draw_option2( index, actor_type_pro );
}

static void print_enemy( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char index;
	unsigned char actor = enemy + 1;

	index = 2 + actor * 3;
	index += eo->image + 1;
	engine_cursor_manager_draw_option( index, eo->tileX * 2 - 1, eo->tileY * 2 + 1 );
	engine_cursor_manager_draw_option2( index, actor );
}