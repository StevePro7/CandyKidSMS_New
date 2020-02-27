#include "over_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

void screen_over_screen_load()
{
	engine_font_manager_draw_text( "OVER SCREEN!!", 4, 11 );
}

void screen_over_screen_update( unsigned char *screen_type )
{
	//engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	*screen_type = screen_type_over;
}
