#include "dead_screen.h"
#include "..\engine\board_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
//#include "..\engine\storage_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
static unsigned char frame_spot;
static unsigned char prevs_direction;

void screen_dead_screen_load()
{
	//engine_command_manager_init();
	//state_object_sound_data();
	//engine_delay_manager_load( 10 );

	//engine_board_manager_init();
	//engine_gamer_manager_init();
	//engine_enemy_manager_init();

	// Draw functions.
	//engine_board_manager_debugger();
	//engine_board_manager_draw_full();
	//engine_board_manager_draw_exit();
	//engine_board_manager_side_tile();

	//engine_level_manager_load_level( 0, 0 );
	//engine_level_manager_draw_level();

	//	engine_frame_manager_draw();
	//	engine_delay_manager_draw();
	engine_font_manager_draw_text( "DEAD SCREEN!", 4, 10 );

	first_time = 1;
	frame_spot = 0;
	prevs_direction = direction_type_none;
}

void screen_dead_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();


	//first_time = 0;
	*screen_type = screen_type_dead;
}
