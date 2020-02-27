#include "frame_manager.h"
#include "font_manager.h"

#define MAX_INT_VALUE	65535

// Global variable.
struct_frame_object global_frame_object;

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