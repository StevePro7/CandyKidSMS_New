#include "select_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_select_screen_load()
{
	engine_font_manager_draw_text( "SELECT SCREEN!!", 2, 10 );
}

void screen_select_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_select;
}
