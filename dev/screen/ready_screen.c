#include "ready_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_ready_screen_load()
{
	engine_font_manager_draw_text( "READY SCREEN!!", 2, 10 );

	// TODO reset all ghosts to their home positions
}

void screen_ready_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_ready;
}
