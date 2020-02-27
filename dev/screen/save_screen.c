#include "save_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"

void screen_save_screen_load()
{
	engine_font_manager_draw_text( "SAVE SCREEN...!!", 4, 1 );
}

void screen_save_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_save;
}