//#include "delay_manager.h"
//#include "font_manager.h"
//#include "..\banks\databank.h"
//
//// Global variable.
//struct_delay_object global_delay_object;
//
//void engine_delay_manager_load( unsigned int delay )
//{
//	struct_delay_object *dObj = &global_delay_object;
//	dObj->delay_value = delay;
//	dObj->delay_timer = 0;
//
//	// Used for testing so no wait.
//	if( state_object_delay_test )
//	{
//		dObj->delay_value = 0;
//	}
//}
//
//unsigned char engine_delay_manager_update()
//{
//	struct_delay_object *dObj = &global_delay_object;
//	unsigned char proceed;
//
//	proceed = dObj->delay_timer >= dObj->delay_value;
//	if( proceed )
//	{
//		dObj->delay_timer = 0;
//	}
//
//	dObj->delay_timer++;
//	return proceed;
//}
//
//void engine_delay_manager_draw()
//{
//	struct_delay_object *dObj = &global_delay_object;
//	engine_font_manager_draw_data( dObj->delay_timer, 31, 1 );
//}