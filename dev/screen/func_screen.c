#include "func_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\memo_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

static unsigned char first_time;

void screen_func_screen_load()
{
	//unsigned char diff = diff_type_easy;
	////unsigned char diff = diff_type_hard;
	////unsigned char pace = pace_type_slow;
	//unsigned char pace = pace_type_fast;

	unsigned char enemy = actor_type_suz;
	unsigned char index;
	unsigned char speed;

	//index = 4 * actor + pace * 2 + diff;
	// There are 4x permutations: Easy + Slow, 
	index = 4 * enemy + state_object_difficulty * 2 + state_object_pace_speed;

	devkit_SMS_mapROMBank( FIXED_BANK );
	speed = enemy_object_speed[ index ];

	engine_font_manager_draw_data( index, 10, 3 );
	engine_font_manager_draw_data( speed - 1, 10, 4 );

	engine_font_manager_draw_text( "FUNC SCREEN!", 10, 2 );

	engine_memo_manager_option();
}

void screen_func_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_func;
}