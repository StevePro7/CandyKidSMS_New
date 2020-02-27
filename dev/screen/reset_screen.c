#include "reset_screen.h"
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
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"

// RESET screen is used for automated testing - this was in the cont screen before
static unsigned char command_index;
static unsigned char command_count;
static unsigned char walking_delta;
static unsigned char walking_count;
static unsigned char first_time;

unsigned char cont_walking_cmds1[] = { direction_type_upxx, direction_type_rght, direction_type_upxx };
unsigned char cont_walking_cmds2[] = { direction_type_down, direction_type_left, direction_type_none };
unsigned char cont_walking_cmds3[] = { direction_type_rght, direction_type_rght, direction_type_rght };
unsigned char cont_walking_cmds4[] = { direction_type_down, direction_type_rght, direction_type_rght };
unsigned char cont_walking_cmds5[] = { direction_type_left, direction_type_down, direction_type_none };
//unsigned char cont_walking_move[] = { 7, 7, 7, 7 };
unsigned char cont_walking_move[] = { 1, 1, 1 };

static unsigned char process_collision( unsigned char tile_type );

void screen_reset_screen_load()
{
	command_count = 3;


	engine_command_manager_load();
	engine_delay_manager_load( 0 );

	//engine_enemy_manager_init();
	//engine_enemy_manager_load();
	//get_actor_data( actor_mover, actor_tileZ );

	engine_score_manager_load();
	engine_score_manager_draw_text();
	engine_score_manager_draw_all();
	engine_score_manager_update_level();

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
	engine_board_manager_side_tile();

	engine_level_manager_load_level( 0, 0 );
	//engine_level_manager_update_level( 0, 0, 0);
	engine_level_manager_draw_level();

	engine_frame_manager_draw();
	engine_delay_manager_draw();

	command_index = 0;
	walking_delta = 0;
	walking_count = 0;
	first_time = 1;
}

void screen_reset_screen_update( unsigned char *screen_type )
{
	unsigned char *cont_walking_cmds = cont_walking_cmds1;


	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_direction = direction_type_none;
	unsigned char enemy_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_tile_type = tile_type_blank;

	unsigned char proceed;
	unsigned int frame = fo->frame_count;
	state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_gamer_manager_draw();
	//engine_gamer_manager_draw();

	engine_frame_manager_draw();
	engine_delay_manager_draw();
	if( !first_time )
	{
		proceed = engine_delay_manager_update();
		if( !proceed )
		{
			*screen_type = screen_type_reset;
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
		//engine_font_manager_draw_data( frame, 12, 16 );

		gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		if( tile_type_blank != gamer_tile_type )
		{
			// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
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


	// Execute all commands for this frame.
	engine_command_manager_execute( frame );
	first_time = 0;

	// Check candy collision before sprite collision as we want to test if all candy eaten = level complete
	if( coll_type_candy == gamer_collision )
	{
		// TODO update correct screen.
		unsigned char candy_count = engine_score_manager_get_candy();
		if( level_object_candy_count == candy_count )
		{
			*screen_type = screen_type_over;
			return;
		}
	}

	if( actor_type_kid != state_object_actor_kill )
	{
		*screen_type = screen_type_dead;
		return;
	}

	*screen_type = screen_type_reset;
}

static unsigned char process_collision( unsigned char tile_type )
{
	struct_gamer_object *go = &global_gamer_object;
	unsigned char gamer_collision = coll_type_empty;

	// Check gamer collision with candy.
	if( tile_type_candy == tile_type )
	{
		//engine_tile_manager_draw_blank( go->tileX, go->tileY );
		engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );
		//engine_tile_manager_main_trees( 0, SCREEN_TILE_LEFT + (x - 1) * 2, ( y - 1 ) * 2 );

		engine_score_manager_update_candy();
		// TODO sound effect...
		gamer_collision = coll_type_candy;
	}

	// Check gamer collision with trees.
	else if( tile_type_trees == tile_type )
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

	// Check gamer collision with oneup.
	else if( tile_type_oneup == tile_type )
	{
		engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );
		// TODO sound effect...
		engine_score_manager_update_lives( 1 );
	}

	// Check gamer collision with bonus.
	else if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
	{
		engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );
		//engine_tile_manager_main_trees( 0, SCREEN_TILE_LEFT + (x - 1) * 2, ( y - 1 ) * 2 );
		// TODO sound effect...
		engine_score_manager_update_bonus( tile_type );
	}

	return gamer_collision;
}