#ifndef _MOVE_MANAGER_H_
#define _MOVE_MANAGER_H_

unsigned char engine_move_manager_find_direction( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char enemy_direction );
unsigned char engine_move_manager_get_directions( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY );

//unsigned char engine_move_manager_test_direction( unsigned char row, unsigned char col );
unsigned char engine_move_manager_actor_direction( unsigned char direction );
unsigned char engine_move_manager_opposite_direction( unsigned char direction );

#endif//_MOVE_MANAGER_H_
