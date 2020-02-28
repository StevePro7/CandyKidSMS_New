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
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"

#define DEAD_SCREEN_DELAY		150

static unsigned char death_frame;

void screen_dead_screen_load()
{
	engine_audio_manager_music_stop();

	// TODO play death sound FX
	engine_font_manager_draw_text( "DEAD SCREEN...!", 4, 10 );

	engine_delay_manager_load( DEAD_SCREEN_DELAY );

	death_frame = 0;
}

void screen_dead_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_enemy_object *eo;
	unsigned char enemy_direction = direction_type_none;
	unsigned char input;
	unsigned char enemy;
	unsigned int frame = fo->frame_count;

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		death_frame = 1 - death_frame;
	}

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw_death( death_frame );


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
	*screen_type = screen_type_dead;
}
