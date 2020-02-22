#include "cont_screen.h"
#include "..\banks\databank.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"

static unsigned char command_index;
static unsigned char command_count;
static unsigned char walking_delta;
static unsigned char walking_count;
static unsigned char first_time;

unsigned char cont_walking_cmds1[] = { direction_type_upxx, direction_type_rght, direction_type_upxx };
unsigned char cont_walking_cmds2[] = { direction_type_upxx, direction_type_upxx, direction_type_upxx };
unsigned char cont_walking_cmds3[] = { direction_type_rght, direction_type_rght, direction_type_rght };
//unsigned char cont_walking_move[] = { 7, 7, 7, 7 };
unsigned char cont_walking_move[] = { 1, 1, 1 };

static unsigned char process_collision( unsigned char tile_type );

void screen_cont_screen_load()
{
	command_count = 3;


	engine_board_manager_init();

	engine_command_manager_init();
	engine_gamer_manager_init();

	engine_delay_manager_load( 0 );

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 0, 0 );
	engine_level_manager_draw_level();

	engine_frame_manager_draw();
	engine_delay_manager_draw();

	command_index = 0;
	walking_delta = 0;
	walking_count = 0;
	first_time = 1;
}

void screen_cont_screen_update( unsigned char *screen_type )
{
	unsigned char *cont_walking_cmds = cont_walking_cmds1;

	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_direction;
	unsigned char enemy_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_tile_type = tile_type_blank;
	//unsigned char gamer_collactor = actor_type_kid;
	
	//unsigned char gamer_collision;

	unsigned char proceed;
	////unsigned char input;
	unsigned int frame = fo->frame_count;

	state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_gamer_manager_draw();

	engine_frame_manager_draw();
	engine_delay_manager_draw();
	if( !first_time )
	{
		proceed = engine_delay_manager_update();
		if( !proceed )
		{
			*screen_type = screen_type_cont;
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
		engine_font_manager_draw_data( frame, 12, 16 );

		// Check gamer collision with death tree.
		//if( !state_object_invincibie && state_object_trees_type == tree_type_death )
		//{
		//	//gamer_collision = foo();
		//	if( coll_type_block == gamer_collision )
		//	{
		//		engine_gamer_manager_dead();
		//		state_object_actor_kill = actor_type_tree;
		//	}
		//}

		// Check gamer collision with death tree.
		//gamer_collision = foo();
		//if( coll_type_block == gamer_collision )
		//{
		//	state_object_actor_kill = actor_type_tree;
		//}

		gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		if( tile_type_blank != gamer_tile_type )
		{
			// Collide with [death] tree, candy, bonus, one up therefore process...
			gamer_collision = process_collision( gamer_tile_type );
			if( coll_type_block == gamer_collision )
			{
				engine_gamer_manager_dead();
				state_object_actor_kill = actor_type_tree;
			}
		}

		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		if( coll_type_empty == gamer_collision )
		{
			gamer_direction = direction_type_none;
			walking_count = 0;

			if( command_index >= command_count )
			{
				//command_index = 0;
			}
			else
			{
				gamer_direction = cont_walking_cmds[ command_index ];
				walking_count = cont_walking_move[ command_index ];

				walking_delta++;
				if( walking_delta >= walking_count )
				{
					command_index++;
					walking_delta = 0;
				}

				gamer_direction = engine_gamer_manager_find_direction( gamer_direction );
				engine_font_manager_draw_data( gamer_direction, 15, 20 );
				if( direction_type_none != gamer_direction )
				{
					engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
				}
			}
		}
	}


	//// Execute all commands for this frame.
	engine_command_manager_execute( frame );

	first_time = 0;

	if( actor_type_kid != state_object_actor_kill )
	{
		*screen_type = screen_type_dead;
		return;
	}

	*screen_type = screen_type_cont;
}


static unsigned char process_collision( unsigned char tile_type )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_collision = coll_type_empty;

	// Check gamer collision with candy.
	
	// Check gamer collision with bonus.

	// Check gamer collision with death tree.
	if( tile_type_trees == tile_type )
	{
		if( !state_object_invincibie && state_object_trees_type == tree_type_death )
		{
			gamer_collision = engine_level_manager_get_collision( go->tileX, go->tileY, go->direction, offset_type_none );
			if( coll_type_block == gamer_collision )
			{
				// Edge case : vulnerable Kid inside open exit with death trees
				gamer_collision = engine_move_manager_inside_exit( go->tileX, go->tileY );
			}
		}
	}

	return gamer_collision;
}