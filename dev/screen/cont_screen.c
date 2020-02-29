#include "cont_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"

void screen_cont_screen_load()
{
	engine_font_manager_draw_text( "CONT SCREEN", 4, 0 );
	//engine_board_manager_midd_text();

	engine_memo_manager_draw( LOCALE_CONT_MESSAGE, LOCALE_CONT_YESORNO );
}

void screen_cont_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_cont;
}