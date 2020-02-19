#ifndef _GAMER_MANAGER_H_
#define _GAMER_MANAGER_H_

#include "..\object\gamer_object.h"

// Global variable.
extern struct_gamer_object global_gamer_object;

// Methods.
void engine_gamer_manager_init();
void engine_gamer_manager_update();
void engine_gamer_manager_draw();
void engine_gamer_manager_move( unsigned char direction );
void engine_gamer_manager_wrap( unsigned char direction );
void engine_gamer_manager_stop();
void engine_gamer_manager_dead();
unsigned char engine_gamer_manager_input_direction();
// TODO delete
//unsigned char engine_gamer_manager_mover_direction();

#endif//_GAMER_MANAGER_H_