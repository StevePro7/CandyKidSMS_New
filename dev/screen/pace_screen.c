#include "pace_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_pace_screen_load()
{
	engine_font_manager_draw_text( "PACE SCREEN", 7, 7 );
}

void screen_pace_screen_update( unsigned char *screen_type )
{

	*screen_type = screen_type_pace;
}