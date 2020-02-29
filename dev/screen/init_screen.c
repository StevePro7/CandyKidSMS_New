#include "init_screen.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"

void screen_init_screen_load()
{
	engine_font_manager_draw_text( "INIT SCREEN!!", 2, 10 );

	engine_enemy_manager_reset_all( enemymove_type_wait );
}

void screen_init_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_init;
}
