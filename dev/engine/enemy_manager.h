#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

//#include "global_manager.h"
#include "..\object\enemy_object.h"

// Global variables.
extern struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

// Methods.
void engine_enemy_manager_init();
void engine_enemy_manager_load();
void engine_enemy_manager_dohand( unsigned char enemy );
void engine_enemy_manager_update( unsigned char enemy );
void engine_enemy_manager_draw();
void engine_enemy_manager_move( unsigned char enemy, unsigned char direction );
void engine_enemy_manager_stop( unsigned char enemy );
void engine_enemy_manager_dead( unsigned char enemy );
void engine_enemy_manager_reset_all( unsigned char mode );
void engine_enemy_manager_reset_home();
void engine_enemy_manager_reset_mode( unsigned char enemy, unsigned char mode );


unsigned char engine_enemy_manager_scatter_direction( unsigned char enemy );
unsigned char engine_enemy_manager_gohome_direction( unsigned char enemy );
unsigned char engine_enemy_manager_attack_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY, unsigned char gamer_direction );
unsigned char engine_enemy_manager_what_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY );

#endif//_ENEMY_MANAGER_H_