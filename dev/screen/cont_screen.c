#include "cont_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_cont_screen_load()
{
	engine_font_manager_draw_text( "CONT SCREEN", 4, 0 );
	engine_board_manager_midd_text();
}

void screen_cont_screen_update( unsigned char *screen_type )
{
	
	*screen_type = screen_type_cont;
}