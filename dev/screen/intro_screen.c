#include "intro_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_intro_screen_load()
{
	engine_board_manager_main_full();
	engine_font_manager_draw_text( "INTRO SCREEN....!!", 4, 0 );
}

void screen_intro_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_intro;
}
