#include "intro_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

void screen_intro_screen_load()
{
	unsigned char row;
	//devkit_SMS_displayOff();

	// TODO tweak this as needed... i.e. run on real hardware and look for any graphics glitches...!!

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( row = 6; row < 22; row++ )
	{
		//engine_font_manager_draw_text( LOCALE_BLANK_WIDTH, SCREEN_TILE_LEFT + 2, row );
		//engine_font_manager_draw_text( locale_object_blank26, SCREEN_TILE_LEFT + 2, row );
	}

	engine_content_manager_load_tiles_main();
	//engine_board_manager_border( border_type_main );
	engine_board_manager_border( border_type_game );
	//engine_font_manager_draw_text( "INTRO SCREEN..!!", 4, 0 );
}

void screen_intro_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_intro;
}
