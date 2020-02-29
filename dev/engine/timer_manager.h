#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include "..\object\delay_object.h"
#include "..\object\frame_object.h"

// Global variable.
extern struct_delay_object global_delay_object;
extern struct_frame_object global_frame_object;

// Delay Manager.
void engine_delay_manager_load( unsigned int delay );
unsigned char engine_delay_manager_update();
void engine_delay_manager_draw();

// Frame Manager.
void engine_frame_manager_load();
void engine_frame_manager_update();
void engine_frame_manager_draw();

#endif//_TIMER_MANAGER_H_`