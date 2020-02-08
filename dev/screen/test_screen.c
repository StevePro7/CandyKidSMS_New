#include "test_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\banks\bank3.h"
#include "..\banks\bank15.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

void screen_test_screen_load()
{
	unsigned char bob;
	//bob = foo[ 0 ];
	devkit_SMS_mapROMBank( bank3_txt_bank );
	bob = bank3_txt[ 0 ];
	//bob = 7;
	engine_font_manager_draw_data( bob, 10, 4 );
	//engine_font_manager_draw_char( bob, 10, 5 );
	engine_font_manager_draw_text( "TEST SCREEN!!", 10, 10 );
}

void screen_test_screen_update( unsigned char *screen_type )
{
	unsigned char test;
	unsigned char data;

	//devkit_SMS_mapROMBank( 15 );
	//data = bank15_txt[ 0 ];

	test = engine_input_manager_hold_fire1();
	if( test )
	{
		devkit_SMS_mapROMBank( bank15_txt_bank );
		data = bank15_txt[ 0 ];

		engine_font_manager_draw_data( bank15_txt[ 0 ], 10, 14 );
		engine_font_manager_draw_data( data, 10, 15 );
		//bank15_txt[ 0 ]++;
		data++;
		//engine_font_manager_draw_text( "FIRE", 10, 12 );
		engine_font_manager_draw_data( bank15_txt[ 0 ], 10, 16 );
		engine_font_manager_draw_data( data, 10, 17 );
	}
	*screen_type = screen_type_test;
}
