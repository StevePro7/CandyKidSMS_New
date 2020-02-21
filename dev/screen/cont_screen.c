#include "cont_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\delay_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\frame_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"

static unsigned char command_index;
static unsigned char command_count;
static unsigned char walking_delta;
static unsigned char walking_count;
static unsigned char first_time;

unsigned char cont_walking_cmds[] = { direction_type_none, direction_type_rght };// direction_type_upxx };
//unsigned char cont_walking_cmds[] = { direction_type_upxx, direction_type_upxx };
//unsigned char cont_walking_move[] = { 7, 7, 7, 7 };
unsigned char cont_walking_move[] = { 1, 1 };

void screen_cont_screen_load()
{
	command_count = 2;


	engine_board_manager_init();

	engine_command_manager_init();
	engine_gamer_manager_init();

	engine_delay_manager_load( 0 );

	engine_board_manager_draw_full();
	engine_board_manager_draw_exit();
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
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	unsigned char the_direction;
	unsigned char proceed;
	////unsigned char input;
	unsigned int frame = fo->frame_count;

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
		// Check collision.
		engine_font_manager_draw_data( frame, 12, 16 );
		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		the_direction = direction_type_none;
		walking_count = 0;

		if( command_index >= command_count )
		{
			//command_index = 0;
		}
		else
		{
			the_direction = cont_walking_cmds[ command_index ];
			walking_count = cont_walking_move[ command_index ];

			walking_delta++;
			if( walking_delta >= walking_count )
			{
				command_index++;
				walking_delta = 0;
			}

			the_direction = engine_gamer_manager_find_direction( the_direction );
			engine_font_manager_draw_data( the_direction, 20, 20 );
			if( direction_type_none != the_direction )
			{
				engine_command_manager_add( frame, command_type_gamer_mover, the_direction );
			}
		}
	}


	//// Execute all commands for this frame.
	engine_command_manager_execute( frame );

	first_time = 0;

	*screen_type = screen_type_cont;
}
