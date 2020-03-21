#include "begin_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
//#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
//#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\tile_manager.h"
//#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
//#include "..\banks\fixedbank.h"
//#include "..\banks\databank.h"

static void draw_tiles();

void screen_begin_screen_load()
{
	devkit_SMS_displayOff();
	engine_asm_manager_clear_VRAM();
	engine_content_manager_load_tiles_font();
	engine_content_manager_load_tiles_main();
	engine_content_manager_load_tiles_screen();
	engine_content_manager_load_sprites_game();

	engine_tile_manager_main_title( 2, 2 );
	engine_board_manager_border( border_type_main );

	draw_tiles();

	engine_locale_manager_draw_text( 0, SCREEN_TILE_LEFT + 24, BOTT_TEXT_Y );
	devkit_SMS_displayOn();
}

void screen_begin_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_title;
}

static void draw_tiles()
{
	const unsigned char multiplier = 1;
	engine_tile_manager_draw_trees( tree_type_avoid, SCREEN_TILE_LEFT + 10, 8 );
	engine_tile_manager_draw_trees( tree_type_death, SCREEN_TILE_LEFT + 10, 10 );

	engine_tile_manager_draw_bonus( tile_type_bonusA, SCREEN_TILE_LEFT + 15, 8, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusB, SCREEN_TILE_LEFT + 15, 10, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusC, SCREEN_TILE_LEFT + 15, 12, multiplier );
	engine_tile_manager_draw_bonus( tile_type_bonusD, SCREEN_TILE_LEFT + 15, 14, multiplier );
}