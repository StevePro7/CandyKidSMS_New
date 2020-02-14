#ifndef _LEVEL_MANAGER_H_
#define _LEVEL_MANAGER_H_
//
////#include "..\object\level_object.h"
//
//// Global variable.
////extern struct_level_object global_level_object;
//
//void engine_level_manager_init_exits();
void engine_level_manager_load_level( const unsigned char world, const unsigned char round );
void engine_level_manager_beat_level( const unsigned char *data, const unsigned char size, const unsigned char bank );
void engine_level_manager_draw_level();
//
//unsigned char engine_level_manager_get_tile_type( unsigned char x, unsigned char y );
////unsigned char engine_level_manager_get_collision( unsigned char x, unsigned char y );
//unsigned char engine_level_manager_get_next_tile( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset );
//unsigned char engine_level_manager_get_next_coll( unsigned char x, unsigned char y, unsigned char direction );
//
#endif//_LEVEL_MANAGER_H_