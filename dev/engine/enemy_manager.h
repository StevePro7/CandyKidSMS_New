#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

//#include "global_manager.h"
#include "..\object\enemy_object.h"

// Global variables.
extern struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

// Methods.
void engine_enemy_manager_init();
void engine_enemy_manager_update( unsigned char enemy );
void engine_enemy_manager_draw();
void engine_enemy_manager_move( unsigned char enemy, unsigned char direction );
void engine_enemy_manager_stop( unsigned char enemy );

unsigned char engine_enemy_manager_find_direction( unsigned char enemy, unsigned char gamerX, unsigned char gamerY );
//unsigned char engine_enemy_manager_what_direction( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char enemy_direction );

#endif//_ENEMY_MANAGER_H_