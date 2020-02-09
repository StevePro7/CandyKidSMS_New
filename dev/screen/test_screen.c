#include "test_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

void screen_test_screen_load()
{
	int bob;
	//bob = foo[ 0 ];
	//bob = 8;
	bob = data_bank_bar;
	engine_font_manager_draw_data( bob, 10, 4 );
	devkit_SMS_mapROMBank( FIXED_BANK );
	bob = foo[ 10 ];
	devkit_SMS_mapROMBank( 2 );
	engine_font_manager_draw_data( bob, 10, 6 );
	//engine_font_manager_draw_char( bob, 10, 5 );
	engine_font_manager_draw_text( "TEST SCREEN....!!", 10, 10 );
}

void screen_test_screen_update( unsigned char *screen_type )
{
	//unsigned char test;
	//unsigned char data;

	//devkit_SMS_mapROMBank( 15 );
	//data = bank15_txt[ 0 ];

	//test = engine_input_manager_hold( input_type_fire1 );
	//if( test )
	//{
	//	bar++;
	//	//devkit_SMS_mapROMBank( bank15_txt_bank );
	//	//data = bank15_txt[ 0 ];

	//	//engine_font_manager_draw_data( bank15_txt[ 0 ], 10, 14 );
	//	engine_font_manager_draw_data( bar, 10, 15 );
	//	//bank15_txt[ 0 ]++;
	//	//data++;
	//	//engine_font_manager_draw_text( "FIRE", 10, 12 );
	//	//engine_font_manager_draw_data( bank15_txt[ 0 ], 10, 16 );
	//	//engine_font_manager_draw_data( data, 10, 17 );
	//}

	*screen_type = screen_type_test;
}
