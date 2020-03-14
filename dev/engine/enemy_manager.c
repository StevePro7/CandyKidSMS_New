#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "level_manager.h"
#include "memo_manager.h"
#include "move_manager.h"
#include "sprite_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"
#include <stdlib.h>

#define SPRITE_TILES_ENEMY	256 + 48

// Global variables.
struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

static void calcd_frame( unsigned char enemy );
static void calcd_spots( unsigned char enemy );

// Methods.
void engine_enemy_manager_init()
{
	struct_enemy_object *eo;
	//unsigned char images[ NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME * MAX_ENEMIES ] =
	//{
	//	0, 2, 4, 12,		// Pro images.
	//	14, 16, 24, 26,		// Adi images.
	//	28, 36, 38, 40,		// Suz images.
	//};

	unsigned char frame;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		eo->actor = enemy;

		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		eo->action = enemymove_type_wait;

		eo->paths = 0;
		eo->timer = 0;
		eo->delta = 0;
		eo->total = 0;
		eo->mover = 1;		// 1=move 0=stay.
		eo->lifecycle = lifecycle_type_idle;
		eo->prev_move = direction_type_none;
		eo->direction = direction_type_none;
		eo->dir_count = 0;

		eo->image = 0;
		eo->frame = frame_type_stance;

		frame = enemy * NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME + 0;
		//devkit_SMS_mapROMBank( FIXED_BANK );
		eo->images[ 0 ][ 0 ] = enemy_object_image[ frame + 0 ];
		eo->images[ 0 ][ 1 ] = enemy_object_image[ frame + 1 ];
		eo->images[ 1 ][ 0 ] = enemy_object_image[ frame + 2 ];
		eo->images[ 1 ][ 1 ] = enemy_object_image[ frame + 3 ];
		eo->scatter[ 0 ] = enemy; eo->scatter[ 1 ] = enemy; eo->scatter[ 2 ] = enemy; eo->scatter[ 3 ] = enemy;

		calcd_frame( enemy );
		calcd_spots( enemy );
	}
}

void engine_enemy_manager_load()
{
	struct_enemy_object *eo;
	unsigned char enemy;
	unsigned char actor;
	unsigned char check;
	unsigned char index;
	unsigned char count = MAX_ENEMIES + state_object_difficulty;
	unsigned char delta;
	unsigned char offset;
	unsigned char random = state_object_round_data + 2;

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		if( !eo->mover )
		{
			continue;
		}

		eo->loops = 0;

		// Determine scatter tiles.
		check = enemy;
		for( index = 0; index < NUM_DIRECTIONS; index++ )
		{
			while( 1 )
			{
				actor = rand() % count;
				if( 0 == index )
				{
					if( actor == enemy || actor_type_kid == actor )
					{
						continue;
					}
				}
				else
				{
					if( check == actor )
					{
						continue;
					}
				}

				eo->scatter[ index ] = actor;
				check = actor;
				break;
			}
		}

		// todo DELETE stevepro
		//eo->scatter[ 0 ] = 1;
		//eo->scatter[ 1 ] = 3;
		//eo->scatter[ 2 ] = 2;
		//eo->scatter[ 3 ] = 0;

		// TODO look up frame swaps from array in data bank that gets faster as the levels progress...!
		index = 4 * enemy + state_object_difficulty * 2 + state_object_pace_speed;

		// Determine interval that Mama hands swap.
		eo->hands = 0;
		eo->swaps = enemy_object_hands[ index ];
		delta = rand() % random;
		eo->swaps -= delta;

		index = 4 * enemy + state_object_difficulty * 2 + state_object_pace_speed;
		//eo->waiter = 64;		// 50 frames
		//eo->waiter = 80;		// 50 frames
		//eo->waiter = 0;		// 50 frames
		//eo->toggle[ 0 ] = 16;
		//eo->toggle[ 1 ] = 04;// 48;

		// Determine interval at start of level Mama waits.
		eo->waiter = enemy_object_waits[ index ];
		delta = rand() % random;
		eo->waiter -= delta;

		// Determine interval Mama toggles from scatter to attack mode.
		eo->toggle[ 0 ] = enemy_object_tours[ index ];
		eo->toggle[ 1 ] = enemy_object_kills[ index ];

		eo->ticker = 0;
		eo->action = enemymove_type_wait;

		
		// TODO - delete hard coded values used for testing.
		//eo->speed = 2;
		//eo->delay = 1;

		// Mix up the order depending on Mama enemy.
		index = 8 * enemy + state_object_difficulty * 2 + state_object_pace_speed;
		eo->speeds[ 0 ] = enemy_object_speed[ index + 0 ];
		eo->delays[ 0 ] = enemy_object_delay[ index + 0 ];
		eo->speeds[ 1 ] = enemy_object_speed[ index + 4 ];
		eo->delays[ 1 ] = enemy_object_delay[ index + 4 ];


		offset = enemy;
		if( actor_type_suz == enemy )
		{
			offset = rand() % 2;
		}

		eo->speeds[ offset ] = enemy_object_speed[ index + 0 ];
		eo->delays[ offset ] = enemy_object_delay[ index + 0 ];

		offset = 1 - offset;
		eo->speeds[ offset ] = enemy_object_speed[ index + 4 ];
		eo->delays[ offset ] = enemy_object_delay[ index + 4 ];

		eo->speed = eo->speeds[ 0 ];
		eo->delay = eo->delays[ 0 ];


		// TODO delete this - debugging
		//engine_font_manager_draw_data( eo->speed, 10, 0 );
		//engine_font_manager_draw_data( eo->delay, 10, 1 );

		//engine_font_manager_draw_data( eo->waiter, 18, 0 );
		//engine_font_manager_draw_data( eo->toggle[ 0 ], 25, 0 );
		//engine_font_manager_draw_data( eo->toggle[ 1 ], 25, 1 );
		//engine_font_manager_draw_data( eo->speeds, 20, 0 );
		//engine_font_manager_draw_data( eo->delays, 20, 1 );

		//engine_font_manager_draw_data( eo->speeds[ 0 ], 10, 0 );
		//engine_font_manager_draw_data( eo->delays[ 0 ], 10, 1 );
		//engine_font_manager_draw_data( eo->speeds[ 1 ], 20, 0 );
		//engine_font_manager_draw_data( eo->delays[ 1 ], 20, 1 );
		// TODO delete this - debugging
	}
}

void engine_enemy_manager_dohand( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->hands++;
	if( eo->hands < eo->swaps )
	{
		return;
	}

	eo->hands = 0;
	eo->frame = 1 - eo->frame;
	calcd_frame( enemy );
}

void engine_enemy_manager_update( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	if( lifecycle_type_move != eo->lifecycle )
	{
		return;
	}

	eo->timer++;
	if( eo->timer < eo->delay )
	{
		return;
	}

	eo->timer = 0;
	eo->delta += eo->speed;
	eo->total += eo->speed;

	// Update position.
	if( direction_type_upxx == eo->direction )
	{
		eo->posnY -= eo->speed;
	}
	else if( direction_type_down == eo->direction )
	{
		eo->posnY += eo->speed;
	}
	else if( direction_type_left == eo->direction )
	{
		eo->posnX -= eo->speed;
	}
	else if( direction_type_rght == eo->direction )
	{
		eo->posnX += eo->speed;
	}

	// Update lifecycle.
	if( eo->total >= TILE_SIZE )
	{
		if( direction_type_upxx == eo->direction )
		{
			eo->tileY--;
		}
		else if( direction_type_down == eo->direction )
		{
			eo->tileY++;
		}
		else if( direction_type_left == eo->direction )
		{
			eo->tileX--;
		}
		else if( direction_type_rght == eo->direction )
		{
			eo->tileX++;
		}

		calcd_spots( enemy );

		eo->lifecycle = lifecycle_type_idle;
		eo->delta = 0;
		eo->total = 0;
	}
}

void engine_enemy_manager_draw()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_hide()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		if( eo->posnX > 60 && eo->posnX < 148 && eo->posnY >60 && eo->posnY < 116 )
		{
			continue;
		}

		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_move( unsigned char enemy, unsigned char direction )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->lifecycle = lifecycle_type_move;
	eo->direction = direction;
}

void engine_enemy_manager_pace( unsigned char enemy, unsigned char boost )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->speed = eo->speeds[ boost ];
	eo->delay = eo->delays[ boost ];
}

void engine_enemy_manager_stop( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//unsigned char toggle;

	//eo->prev_move[ 3 ] = eo->prev_move[ 2 ];
	//eo->prev_move[ 2 ] = eo->prev_move[ 1 ];
	//eo->prev_move[ 1 ] = eo->prev_move[ 0 ];
	//eo->prev_move[ 0 ] = eo->direction;
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
	eo->ticker++;
	//eo->frame = 0;		// TODO remove as this is done in gohands()
	calcd_frame( enemy );


	// Detect to swap scatter to attack and vice versa.
	//toggle = eo->toggle[ eo->action ];
	//if( eo->ticker >= toggle )
	//{
	//	eo->action = 1 - eo->action;
	//	eo->ticker = 0;

	//	//TODO delete
	//	if( 0 == eo->action )
	//	{
	//		engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//	}
	//	if( 1 == eo->action )
	//	{
	//		engine_font_manager_draw_text( "ATTACK", 26, 21 );
	//	}
	//}


	// Every 4x moves check if enemy moved any combination of: U, D, L, R
	// e.g. if U + D + L + R = 15 then is caught in endless loop so change
	//eo->dir_fours |= eo->prev_move;
	//eo->dir_count++;
	//if( eo->dir_count > NUM_DIRECTIONS )
	//{
	//	eo->dir_count = 0;
	//	eo->dir_fours = eo->prev_move;
	//}
}

void engine_enemy_manager_dead( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->lifecycle = lifecycle_type_dead;
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
	//eo->frame = frame_type_stance;
	//calcd_frame( enemy );
}

//void engine_enemy_manager_reset_all( unsigned char mode )
//{
//	unsigned char enemy;
//	engine_enemy_manager_reset_home();
//	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
//	{
//		engine_enemy_manager_reset_mode( enemy, mode );
//	}
//}

void engine_enemy_manager_reset_home()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Reset at home.
		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		calcd_spots( enemy );

		eo->lifecycle = lifecycle_type_idle;
		eo->direction = direction_type_none;
		eo->frame = frame_type_stance;
		eo->delta = 0;
		eo->total = 0;
		calcd_frame( enemy );
	}
}

void engine_enemy_manager_reset_mode( unsigned char enemy, unsigned char mode )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo = &global_enemy_objects[ enemy ];
	eo->action = mode;


	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode
	//eo->image = mode;
	//calcd_frame( enemy );
	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode


	// TODO delete used for debugging
	//engine_memo_manager_debugging( enemy, eo->action );
	//if( 0 == eo->action )
	//{
	//	engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//}
	//if( 1 == eo->action )
	//{
	//	engine_font_manager_draw_text( "ATTACK", 26, 21 );
	//}
}


// TODO delete!!
void engine_enemy_manager_debug()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// TODO delete as this will be replaced by menu selection.
		eo->mover = state_object_enemy_move[ enemy ];
		// TODO delete as this will be replaced by menu selection.
	}
}

unsigned char engine_enemy_manager_scatter_direction( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char enemy_direction = direction_type_none;
	unsigned char targetX;
	unsigned char targetY;
	unsigned char actor;

	// This enemy does not move!
	//if( !eo->mover )
	//{
	//	return direction_type_none;
	//}

	// SCATTER.
	actor = eo->scatter[ eo->paths ];
	targetX = board_object_homeX[ actor ];
	targetY = board_object_homeY[ actor ];

	if( targetX == eo->tileX && targetY == eo->tileY )
	{
		eo->paths++;
		if( eo->paths >= NUM_DIRECTIONS )
		{
			eo->paths = 0;
		}

		actor = eo->scatter[ eo->paths ];
		targetX = board_object_homeX[ actor ];
		targetY = board_object_homeY[ actor ];
	}

	enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	return enemy_direction;
}

unsigned char engine_enemy_manager_gohome_direction( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char enemy_direction = direction_type_none;

	unsigned char targetX;
	unsigned char targetY;

	// This enemy does not move!
	//if( !eo->mover )
	//{
	//	return direction_type_none;
	//}

	// GO HOME.
	targetX = board_object_homeX[ enemy ];
	targetY = board_object_homeY[ enemy ];

	// If enemy at home tile then just stop.
	if( targetX == eo->tileX && targetY == eo->tileY )
	{
		return direction_type_none;
	}

	enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	return enemy_direction;
}

unsigned char engine_enemy_manager_attack_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	struct_enemy_object *eo0;

	unsigned char enemy_direction = direction_type_none;

	//// ATTACK.
	if( actor_type_pro == enemy )
	{
		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	}
	//else 
	else if( actor_type_adi == enemy )
	{
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );

		// Like Pinky
		//gamer_direction = engine_move_manager_actor_direction( gamer_direction );
		//gamer_direction = engine_move_manager_actor_direction( eo->prev_move );

		// Look two tiles in front on Candy Kid.
		//engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, offset_type_two );
		engine_level_manager_get_next_index( &targetX, &targetY, eo->prev_move, offset_type_two );
		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
	}
	//else
	else if( actor_type_suz == enemy )
	{
		// TODO delete - this is just used for testing...!!
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );

		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
		//unsigned char coin = rand() % 3;
		////unsigned char coin = 2;

		//// Try Pacman algorithm based off Blinky [Pro]
		eo0 = &global_enemy_objects[ actor_type_pro ];

		//// TODO while loop if Pro not moving then don't add AND if Adi not moving then don't add
		//if( 2 != coin )
		//{
		targetX = eo0->tileX;
		targetY = eo0->tileY;
		//}

		//// Look two tiles in front on Candy Kid.
		//// TODO - maybe make value 2 variable for Eash vs. Hard?
		////engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move[0], 0 );
		engine_level_manager_get_next_index( &targetX, &targetY, direction_type_none, offset_type_none );
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
		enemy_direction = engine_enemy_manager_what_direction( enemy, ( offset_type_four - 1 ) - targetX, ( offset_type_four - 1 ) - targetY );
	}

	return enemy_direction;
}

//unsigned char engine_enemy_manager_attack_direction2( unsigned char enemy, unsigned char targetX, unsigned char targetY, unsigned char gamer_direction )
//{
//	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
//	struct_enemy_object *eo0;
//
//	unsigned char enemy_direction = direction_type_none;
//
//	//// This enemy does not move!
//	////if( !eo->mover )
//	////{
//	////	return direction_type_none;
//	////}
//
//	//// TODO decide whether scatter or attack...!
//
//	//// ATTACK.
//	if( actor_type_pro == enemy )
//	{
//		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//	}
//	//else 
//	else if( actor_type_adi == enemy )
//	{
//		// Like Pinky
//		//gamer_direction = engine_move_manager_actor_direction( gamer_direction );
//
//		// Look two tiles in front on Candy Kid.
//		engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, offset_type_two );
//		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//	}
//	//else
//	else if( actor_type_suz == enemy )
//	{
//		// TODO delete - this is just used for testing...!!
//		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//
//		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//		//unsigned char coin = rand() % 3;
//		////unsigned char coin = 2;
//
//		//// Try Pacman algorithm based off Blinky [Pro]
//		eo0 = &global_enemy_objects[ actor_type_pro ];
//
//		//// TODO while loop if Pro not moving then don't add AND if Adi not moving then don't add
//		//if( 2 != coin )
//		//{
//		targetX = eo0->tileX;
//		targetY = eo0->tileY;
//		//}
//
//		//// Look two tiles in front on Candy Kid.
//		//// TODO - maybe make value 2 variable for Eash vs. Hard?
//		////engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move[0], 0 );
//		engine_level_manager_get_next_index( &targetX, &targetY, direction_type_none, offset_type_none );
//		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//		enemy_direction = engine_enemy_manager_what_direction( enemy, ( offset_type_four - 1 ) - targetX, ( offset_type_four - 1 ) - targetY );
//	}
//
//	return enemy_direction;
//}

//unsigned char engine_enemy_manager_attack_direction_ORG( unsigned char enemy, unsigned char targetX, unsigned char targetY, unsigned char gamer_direction )
//{
//	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
//	struct_enemy_object *eo0;
//
//	unsigned char enemy_direction = direction_type_none;
//
//	// This enemy does not move!
//	//if( !eo->mover )
//	//{
//	//	return direction_type_none;
//	//}
//
//	// TODO decide whether scatter or attack...!
//
//	// ATTACK.
//	if( actor_type_pro == enemy )
//	{
//		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//	}
//	else if( actor_type_adi == enemy )
//	{
//		// Like Pinky
//		gamer_direction = engine_move_manager_actor_direction( gamer_direction );
//		
//		// Look two tiles in front on Candy Kid.
//		engine_level_manager_get_next_index( &targetX, &targetY, gamer_direction, offset_type_two );
//		enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
//	}
//	else if( actor_type_suz == enemy )
//	{
//		unsigned char coin = rand() % 3;
//		//unsigned char coin = 2;
//
//		// Try Pacman algorithm based off Blinky [Pro]
//		eo0 = &global_enemy_objects[ coin ];
//		
//		// TODO while loop if Pro not moving then don't add AND if Adi not moving then don't add
//		if( 2 != coin )
//		{
//			targetX = eo0->tileX;
//			targetY = eo0->tileY;
//		}
//
//		// Look two tiles in front on Candy Kid.
//		// TODO - maybe make value 2 variable for Eash vs. Hard?
//		//engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move[0], 0 );
//		engine_level_manager_get_next_index( &targetX, &targetY, eo0->prev_move, offset_type_one );
//		enemy_direction = engine_enemy_manager_what_direction( enemy, ( offset_type_four- 1 ) - targetX, ( offset_type_four - 1 ) - targetY );
//	}
//
//	return enemy_direction;
//}

unsigned char engine_enemy_manager_what_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
	unsigned char move_direction = direction_type_none;
	unsigned char oppX_direction = direction_type_none;
	//unsigned char prev_direction = direction_type_none;
	unsigned char test_direction = direction_type_none;
	unsigned char collision = direction_type_none;
	unsigned char available = direction_type_none;

	unsigned char sourceX = eo->tileX;
	unsigned char sourceY = eo->tileY;
	unsigned char index = 0;
	//unsigned char byte = 0;
	unsigned char list = 0;
	unsigned char half = 0;
	unsigned char flip = 0;

	// Get the list of 4x possible directions in the order depending on tiles.
	engine_move_manager_get_directions( sourceX, sourceY, targetX, targetY, &list, &half );

	//if( 10 == sourceX && 3 == sourceY )
	//{
	//	flip = 2;
	//}
	// TODO randomly flip the half = 1 - half??
	//if( 15 == dir_fours )
	//{
	//	list = rand() % NUM_DIRECTIONS;	// 0 or 1
	//	//half = 1 - half;
	//}
	// IMPORTANT - this will never trigger		//flip = rand() % 0
	//flip = rand() % 2;	// 0 or 1
	//if( 0 == flip )
	//{
	//	half = 1 - half;
	//}
	// TODO randomly flip the half = 1 - half??

	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;

	// TODO fixed bank - change to data bank!!
	directions[ 0 ] = enemy_object_directions[ index + 0 ];
	directions[ 1 ] = enemy_object_directions[ index + 1 ];
	directions[ 2 ] = enemy_object_directions[ index + 2 ];
	directions[ 3 ] = enemy_object_directions[ index + 3 ];

	//prev_direction = eo->prev_move[ 3 ];
	//oppX_direction = engine_move_manager_opposite_direction( eo->prev_move[ 0 ] );
	oppX_direction = engine_move_manager_opposite_direction( eo->prev_move );
	available = engine_level_manager_get_direction( sourceX, sourceY, direction_type_none, offset_type_none );


	// TODO - fully regression test potential infinite looping.
	//test_direction = eo->prev_move;
	//if( oppX_direction != test_direction )
	//{
	//	if( test_direction == ( available & test_direction ) )
	//	{
	//		move_direction = test_direction;
	//		return move_direction;
	//	}
	//}


	for( index = 0; index < NUM_DIRECTIONS; index++ )
	{
		test_direction = directions[ index ];
		if( oppX_direction == test_direction )
		{
			continue;
		}

		if( test_direction == ( available & test_direction ) )
		{
			move_direction = test_direction;
			break;
		}

		//collision = engine_level_manager_get_collision( sourceX, sourceY, test_direction, offset_type_one );
		//if( coll_type_empty == collision )
		//{
		//	move_direction = test_direction;
		//	break;
		//}
	}

	// TODO delete as back up of the code...
	//oppX_direction = engine_move_manager_opposite_direction( eo->prev_move );
	//for( index = 0; index < NUM_DIRECTIONS; index++ )
	//{
	//	test_direction = directions[ index ];
	//	if( oppX_direction != test_direction )
	//	{
	//		//if( prev_direction != test_direction )
	//		//{
	//			collision = engine_level_manager_get_collision( sourceX, sourceY, test_direction, offset_type_one );
	//			if( coll_type_empty == collision )
	//			{
	//				move_direction = test_direction;
	//				break;
	//			}
	//		//}
	//	}
	//}

	// Enemy in cul de sac so must be able to go in opposite direction!
	if( direction_type_none == move_direction )
	{
		//collision = engine_level_manager_get_collision( sourceX, sourceY, oppX_direction, offset_type_one );
		//if( coll_type_empty == collision )
		//{
		move_direction = oppX_direction;
		//}
	}

	return move_direction;
}

unsigned char engine_enemy_manager_input_boost( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char toggle = eo->toggle[ eo->action ];
	unsigned char boost = 0;

	// Not ready to swap modes.
	if( eo->ticker < toggle  )
	{
		return pace_type_none;
	}

	eo->action = 1 - eo->action;		// stevepro disable for testing.
	eo->ticker = 0;
	boost = eo->action;

	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode
	// Swap image to indicate different mode : Scatter vs. Attack.
	//if( state_object_mydebugger )
	//{
	//	eo->image = 1 - eo->image;
	//	calcd_frame( enemy );
	//}
	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode


	//TODO delete
	//engine_memo_manager_debugging( enemy, eo->action );
	//if( 0 == eo->action )
	//{
	//	engine_font_manager_draw_text( "SCATTR", 26, 21 );
	//}
	//if( 1 == eo->action )
	//{
	//	engine_font_manager_draw_text( "ATTACK", 26, 21 );
	//}

	//return pace_type_none;
	return boost;
}

static void calcd_frame( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->calcd = SPRITE_TILES_ENEMY + eo->images[ eo->image ][ eo->frame ];
}
static void calcd_spots( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->posnX = board_object_posnX[ eo->tileX ];
	eo->posnY = board_object_posnY[ eo->tileY ];
	engine_function_manager_convertXYtoZ( MAZE_ROWS, eo->tileX, eo->tileY, &eo->tileZ );
}