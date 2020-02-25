#include "intro_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\banks\databank.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

// PLAY screen - is the main command add + execute driver
static unsigned char first_time;
//static unsigned char frame_spot;

void screen_intro_screen_load()
{
	engine_command_manager_init();
	engine_delay_manager_load( 0 );

	engine_board_manager_init();
	engine_gamer_manager_init();
	engine_enemy_manager_init();
	//engine_enemy_manager_load();
	//get_actor_data( actor_mover, actor_tileZ );

	engine_font_manager_draw_text( "INTRO SCREEN...!!", 2, 10 );
	first_time = 1;
}

void screen_intro_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	//struct_enemy_object *eo;
	unsigned char gamer_direction = direction_type_none;
	//unsigned char enemy_direction = direction_type_none;
	//unsigned char gamer_collision = coll_type_empty;
	//unsigned char gamer_tile_type = tile_type_blank;

	unsigned char proceed;
	//unsigned char enemy;
	//unsigned char input;
	unsigned int frame = fo->frame_count;
	//state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	engine_frame_manager_draw();
	engine_delay_manager_draw();
	if( !first_time )
	{
		proceed = engine_delay_manager_update();
		if( !proceed )
		{
			*screen_type = screen_type_play;
			return;
		}

		engine_frame_manager_update();
		first_time = 1;
	}

	// Continue...
	frame = fo->frame_count;

	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		engine_gamer_manager_update();
	}
	if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	{
		// Check gamer collision.
		//engine_font_manager_draw_data( frame, 11, 16 );

		//gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		//if( tile_type_blank != gamer_tile_type )
		//{
		//	// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
		//	gamer_collision = process_collision( gamer_tile_type );
		//	if( coll_type_block == gamer_collision )
		//	{
		//		engine_gamer_manager_dead();
		//		state_object_actor_kill = actor_type_tree;
		//	}
		//}

		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		//if( coll_type_empty == gamer_collision )
		//{
			gamer_direction = engine_gamer_manager_input_direction();
			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );

			if( direction_type_none != gamer_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
			}
		//}
	}

	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;


	*screen_type = screen_type_intro;
}
