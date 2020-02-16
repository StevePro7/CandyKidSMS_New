#include "enemy_manager.h"
#include "board_manager.h"
#include "enum_manager.h"
//#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "sprite_manager.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

#define SPRITE_TILES_ENEMY	256 + 48

// Global variables.
struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

static void calcd_frame( unsigned char enemy );
static void calcd_spots( unsigned char enemy );

// Methods.
void engine_enemy_manager_init()
{
	struct_enemy_object *eo;
	unsigned char images[ NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME * MAX_ENEMIES ] =
	{
		0, 2, 4, 12,		// Pro images.
		14, 16, 24, 26,		// Adi images.
		28, 36, 38, 40,		// Suz images.
	};

	unsigned char frame;
	//unsigned char homeX;
	//unsigned char homeY;

	unsigned char enemy;
	devkit_SMS_mapROMBank( FIXED_BANK );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		//homeX = board_homeX[ enemy ];
		//homeY = board_homeY[ enemy ];

		//eo->homeX = homeX;
		//eo->homeY = homeY;
		//engine_board_manager_calc_tileSpot( eo->homeX, eo->homeY, &eo->homeZ );
		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		eo->delay = 2;		// TODO hardcoded - inject!
		eo->timer = 0;
		eo->delta = 0;
		eo->total = 0;
		eo->speed = 1;		// TODO hardcoded - inject!
		eo->mover = 1;		// 1=move 0=stay.
		eo->prev_move = direction_type_none;
		eo->direction = direction_type_none;
		eo->lifecycle = lifecycle_type_idle;

		eo->image = frame_type_stance;
		eo->frame = 0;

		frame = enemy * NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME + 0;

		eo->images[ 0 ][ 0 ] = images[ frame + 0 ];
		eo->images[ 0 ][ 1 ] = images[ frame + 1 ];
		eo->images[ 1 ][ 0 ] = images[ frame + 2 ];
		eo->images[ 1 ][ 1 ] = images[ frame + 3 ];

		/*
		image = images[ frame + 0 ];
		eo->images[ 0 ][ 0 ] = image;

		image = images[ frame + 1 ];
		eo->images[ 0 ][ 1 ] = image;

		image = images[ frame + 2 ];
		eo->images[ 1 ][ 0 ] = image;

		image = images[ frame + 3 ];
		eo->images[ 1 ][ 1 ] = image;
		*/
		calcd_frame( enemy );
		calcd_spots( enemy );


		// TODO delete
		if( 0 == enemy )
		{
			eo->mover = 0;
		}
	}
}

//void engine_enemy_manager_load()
//{
//	// TODO hardcoded - inject!
//	struct_enemy_object *eo = &global_enemy_objects[ actor_type_pro ];
//	eo->posnX = 144;
//	eo->posnY = 144;
//	eo->tileX = 9;
//	eo->tileY = 9;
//}

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

	if( eo->delta > TILE_HALF )
	{
		// TODO do the enemy hands.
		eo->frame = 1 - eo->frame;
		eo->delta = 0;
		calcd_frame( enemy );
	}
}

void engine_enemy_manager_draw()
{
	struct_enemy_object *eo;
	unsigned char enemy;
	//for( idx = 0; idx < MAX_ENEMIES; idx++ )
	//TODO revert to draw all enemies
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_move( unsigned char enemy, unsigned char direction )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->direction = direction;
	eo->lifecycle = lifecycle_type_move;

	// TODO do the enemy hands.
	eo->frame = frame_type_toggle;
	calcd_frame( enemy );
}

void engine_enemy_manager_stop( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
	eo->frame = 0;
	calcd_frame( enemy );
}

static void calcd_frame( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//eo->calcd = SPRITE_TILES_ENEMY + eo->image * 8 + eo->frame * 4;
	eo->calcd = SPRITE_TILES_ENEMY + eo->images[ eo->image ][ eo->frame ];
}
static void calcd_spots( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	//struct_board_object *bo = &global_board_object;

	devkit_SMS_mapROMBank( FIXED_BANK );
	eo->posnX = board_object_posnX[ eo->tileX ];
	eo->posnY = board_object_posnY[ eo->tileY ];
	// Calculate exact tile as 1x byte.
	engine_function_manager_convertXYtoZ( MAZE_ROWS, eo->tileX, eo->tileY, &eo->tileZ );
}