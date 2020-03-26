#ifndef _ENEMY_OBJECT_H_
#define _ENEMY_OBJECT_H_

#include "..\engine\global_manager.h"

typedef struct tag_struct_enemy_object
{
	unsigned char actor;
	unsigned char posnX;		// PositionX during movement.
	unsigned char posnY;		// PositionY during movement.
	unsigned char tileX;		// Posn tileX on enemy stops. 
	unsigned char tileY;		// Posn tileY on enemy stops.
	unsigned char tileZ;		// Posn tile stored as R x C.
	unsigned char waiter;		// Wait time when level load.
	unsigned char toggle[ 2 ];	// Track scatter mode attack.
	unsigned char ticker;		// Count no. moves when swap.
	unsigned char action;		// Current action: W / T / K.
	unsigned char scatter[ NUM_DIRECTIONS ];
	unsigned char paths;		// Track enemy scatter paths.
	//unsigned char velocity[ 2 ];
	//unsigned char boost;
	unsigned char speeds[ 2 ];
	unsigned char delays[ 2 ];
	unsigned char speed;
	unsigned char delay;
	unsigned char timer;
	unsigned char delta;
	unsigned char total;
	unsigned char mover;		// Flag when enemy can moves.
	unsigned char hands;		// Delay when swap hand over.
	unsigned char swaps;
	unsigned char loops;
	unsigned char lifecycle;
	//unsigned char prev_moves[ 4 ];	// Previous direction moved.
	unsigned char prev_move;	// Previous direction moved.
	unsigned char direction;	// Current  direction moved.
	//unsigned char dir_fours;
	unsigned char dir_count;
	unsigned char image;
	unsigned char frame;
	unsigned int calcd;
	unsigned char images[ NUM_ENTITY_IMAGE ][ NUM_ENTITY_FRAME ];

} struct_enemy_object;

// DATA bank.
// Enemy Manager.
extern const unsigned char enemy_object_directions[];

#endif//_ENEMY_OBJECT_H_