#include "dead_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\tile_manager.h"
#include "..\banks\databank.h"

#define DEATH_SCREEN_DELAY		150
#define FLASH_SCREEN_DELAY		20

static unsigned char death_frame;
static unsigned char event_stage;
static unsigned char flash_count;

static void reset_death();

void screen_dead_screen_load()
{
	engine_audio_manager_music_stop();
	engine_command_manager_load();

	// TODO play death sound FX
	engine_delay_manager_load( DEATH_SCREEN_DELAY );

	event_stage = event_stage_start;
	//event_stage = event_stage_pause;
	death_frame = 0;
	flash_count = 0;

	if( state_object_mydebugger )
	{
		engine_enemy_manager_load();
	}
}

void screen_dead_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_enemy_object *eo;
	unsigned char enemy_direction = direction_type_none;
	//unsigned char input;
	unsigned char enemy;
	unsigned char delay;
	unsigned int frame = fo->frame_count;


	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw_death( death_frame );


	engine_frame_manager_draw();
	engine_delay_manager_draw();

	engine_frame_manager_update();
	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			flash_count++;
			death_frame = 1 - death_frame;
			if( flash_count >= 7 )
			{
				reset_death();
				*screen_type = screen_type_ready;
				return;
			}
		}
	}


	// Move enemies.
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Swap hands first if enemy moving and not dead.
		if( eo->mover && lifecycle_type_dead != eo->lifecycle )
		{
			engine_enemy_manager_dohand( enemy );
		}

		// If enemy not moving then skip all movement code.
		if( !eo->mover )
		{
			continue;
		}

		// Move enemy.
		if( direction_type_none != eo->direction && lifecycle_type_move == eo->lifecycle )
		{
			//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
			engine_enemy_manager_update( enemy );
		}
		if( direction_type_none != eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			engine_enemy_manager_stop( enemy );
		}
		// For continuity we want to check if actor can move immediately after stopping.
		if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			enemy_direction = engine_enemy_manager_gohome_direction( enemy );
			if( direction_type_none != enemy_direction )
			{
				engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
			}
		}
	}

	// Execute all commands for this frame.
	engine_command_manager_execute( frame );


	if( event_stage_start == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			engine_delay_manager_load( FLASH_SCREEN_DELAY );
			event_stage = event_stage_pause;
		}
	}

	*screen_type = screen_type_dead;
}

static void reset_death()
{
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char enemy;

	// Kid collided with death tree on border so redraw.
	if( !state_object_invincibie && state_object_trees_type == tree_type_death )
	{
		if( actor_type_tree == state_object_actor_kill )
		{
			if( 1 == go->tileX || 1 == go->tileY || ( MAZE_COLS - 2 ) == go->tileX || ( MAZE_ROWS - 2 ) == go->tileY )
			{
				
				engine_tile_manager_draw_trees( state_object_trees_type, SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );
			}
		}
	}

	// If Kid collided with Mama then will be reset from dead to idle below...

	// Reset all enemies back to scatter mode.
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_enemy_manager_reset( enemy, enemymove_type_tour );
	}
}