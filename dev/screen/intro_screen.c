#include "intro_screen.h"
#include "..\engine\board_manager.h"
#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\move_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\sprite_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"

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
	struct_gamer_object *go = &global_gamer_object;
	engine_command_manager_init();
	engine_delay_manager_load( 0 );

	engine_board_manager_init();
	engine_gamer_manager_init();
	engine_enemy_manager_init();

	engine_font_manager_draw_text( "INTRO SCREEN...!!", 4, 0 );

	go->posnX = 136;
	first_time = 1;
}

void screen_intro_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	//struct_enemy_object *eo;
	unsigned char gamer_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;

	unsigned char proceed;
	unsigned int frame = fo->frame_count;

	unsigned char sx, sy;
	unsigned char dx, dy;
	unsigned char cx, cy;

	int res;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();
	if( !first_time )
	{
		proceed = engine_delay_manager_update();
		if( !proceed )
		{
			*screen_type = screen_type_intro;
			return;
		}

		engine_frame_manager_update();
		first_time = 1;
	}

	// Continue...
	frame = fo->frame_count;

	// Move gamer.
	gamer_direction = engine_gamer_manager_input_direction2();
	gamer_direction = engine_gamer_manager_find_direction( gamer_direction );

	if( direction_type_upxx == gamer_direction )
	{
		go->posnY--;
	}
	if( direction_type_down == gamer_direction )
	{
		go->posnY++;
	}
	if( direction_type_left == gamer_direction )
	{
		go->posnX--;
	}
	if( direction_type_rght == gamer_direction )
	{
		go->posnX++;
	}

	res = 0;
	engine_font_manager_draw_text( "       ", 10, 10 );

	eo = &global_enemy_objects[ actor_type_suz ];
	sx = go->posnX;
	sy = go->posnY;
	dx = eo->posnX;
	dy = eo->posnY;

	if( dx > sx )
	{
		cx = dx - sx;
	}
	else
	{
		cx = sx - dx;
	}

	if( dy > sy )
	{
		cy = dy - sy;
	}
	else
	{
		cy = sy - dy;
	}

	gamer_collision = devkit_isCollisionDetected();
	if( coll_type_empty != gamer_collision )
	{
		res = cx * cx + cy * cy;
		engine_font_manager_draw_text( "COLLIDE", 10, 10 );
	}

	engine_font_manager_draw_data( cx, 30, 2 );
	//engine_font_manager_draw_data( dx, 20, 2 );
	//engine_font_manager_draw_data( sx, 10, 2 );

	engine_font_manager_draw_data( cy, 30, 3 );
	//engine_font_manager_draw_data( dy, 20, 3 );
	//engine_font_manager_draw_data( sy, 10, 3 );

	engine_font_manager_draw_data( res, 30, 12 );
	first_time = 0;
	*screen_type = screen_type_intro;
}
