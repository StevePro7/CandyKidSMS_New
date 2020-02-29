#include "ready_screen.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"

void screen_ready_screen_load()
{
	engine_font_manager_draw_text( "READY SCREEN!!", 2, 10 );

	// TODO reset all ghosts to their home positions

	// TODO delete
	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();
}

void screen_ready_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_ready;
}
