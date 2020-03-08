#ifndef _GAMER_MANAGER_H_
#define _GAMER_MANAGER_H_

#include "..\object\gamer_object.h"

// Global variable.
extern struct_gamer_object global_gamer_object;

// Methods.
void engine_gamer_manager_init();
void engine_gamer_manager_load();
void engine_gamer_manager_update();
void engine_gamer_manager_draw();
void engine_gamer_manager_hide();
void engine_gamer_manager_draw_death( unsigned char frame );
void engine_gamer_manager_move( unsigned char direction );
void engine_gamer_manager_wrap( unsigned char direction );
void engine_gamer_manager_pace( unsigned char boost );
void engine_gamer_manager_stop();
void engine_gamer_manager_dead();
void engine_gamer_manager_reset();

unsigned char engine_gamer_manager_find_direction( unsigned char gamer_direction );
unsigned char engine_gamer_manager_input_direction();
//unsigned char engine_gamer_manager_input_direction2();		// TODO delete
//unsigned char engine_gamer_manager_input_direction();

unsigned char engine_gamer_manager_input_boost( unsigned char direction );
//unsigned char engine_gamer_manager_input_boost( unsigned char gamer_boost );

#endif//_GAMER_MANAGER_H_