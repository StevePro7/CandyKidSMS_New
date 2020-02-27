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
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

void screen_dead_screen_load()
{
	engine_font_manager_draw_text( "DEAD SCREEN!", 4, 10 );
}

void screen_dead_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	//engine_gamer_manager_draw();

	*screen_type = screen_type_dead;
}
