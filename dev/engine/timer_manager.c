#include "timer_manager.h"
#include "font_manager.h"
#include "..\banks\databank.h"

#define MAX_INT_VALUE	65535

// Global variables.
struct_delay_object global_delay_object;
struct_frame_object global_frame_object;
struct_reset_object global_reset_object;


// Delay Manager.
void engine_delay_manager_load( unsigned int delay )
{
	struct_delay_object *dObj = &global_delay_object;
	dObj->delay_value = delay;
	dObj->delay_timer = 0;

	// Used for testing so no wait.
	if( state_object_delay_test )
	{
		dObj->delay_value = 0;
	}
}
unsigned char engine_delay_manager_update()
{
	struct_delay_object *dObj = &global_delay_object;
	unsigned char proceed;

	proceed = dObj->delay_timer >= dObj->delay_value;
	if( proceed )
	{
		dObj->delay_timer = 0;
	}

	dObj->delay_timer++;
	return proceed;
}
void engine_delay_manager_draw()
{
	struct_delay_object *dObj = &global_delay_object;
	engine_font_manager_draw_data( dObj->delay_timer, 31, 1 );
}


// Frame Manager.
void engine_frame_manager_load()
{
	struct_frame_object *fo = &global_frame_object;
	fo->frame_count = 0;
}
void engine_frame_manager_update()
{
	struct_frame_object *fo = &global_frame_object;
	fo->frame_count++;
	if( fo->frame_count >= MAX_INT_VALUE )
	{
		fo->frame_count = 0;
	}
}
void engine_frame_manager_draw()
{
	struct_frame_object *fo = &global_frame_object;
	engine_font_manager_draw_data( fo->frame_count, 31, 0 );
}


// Reset Manager.
void engine_reset_manager_load( unsigned char frame )
{
	struct_reset_object *ro = &global_reset_object;
	ro->reset_frame = frame;
	engine_reset_manager_reset();
}

void engine_reset_manager_reset()
{
	struct_reset_object *ro = &global_reset_object;
	ro->reset_timer = 0;
}

unsigned char engine_reset_manager_update()
{
	struct_reset_object *ro = &global_reset_object;
	unsigned char test;

	ro->reset_timer++;
	test = ro->reset_timer >= ro->reset_frame;
	if( test )
	{
		ro->reset_timer = 0;
	}

	return test;
}