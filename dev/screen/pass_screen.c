#include "pass_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"

void screen_pass_screen_load()
{
	//engine_board_manager_draw_full();
	//engine_board_manager_draw_exit();
	//engine_board_manager_side_tile();

	//engine_level_manager_load_level( 0, 1 );
	////engine_level_manager_load_level( 7, 4 );
	//engine_level_manager_draw_level();
	engine_font_manager_draw_text( "PASS SCREEN!", 4, 10 );
	engine_audio_manager_music_stop();
}

void screen_pass_screen_update( unsigned char *screen_type )
{
	//unsigned char input;
	//input = engine_input_manager_hold( input_type_fire1 );
	//if( input )
	//{
	//	engine_board_manager_midd_text();
	//}

	//input = engine_input_manager_hold( input_type_fire2 );
	//if( input )
	//{
	//	engine_level_manager_draw_middle();
	//}

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_pass;
}
