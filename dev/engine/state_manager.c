#include "state_manager.h"
#include "board_manager.h"
#include "cursor_manager.h"
#include "command_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "gamer_manager.h"
#include "global_manager.h"
#include "hack_manager.h"
#include "storage_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include "..\banks\databank.h"

// Global variable.
struct_state_object global_state_object;

void engine_state_manager_init()
{
	struct_state_object *st = &global_state_object;
	st->state_object_invincibie = 0;
	st->state_object_localcheat = 0;
	st->state_object_high_score = 0;
	st->state_object_difficulty = 0;
	st->state_object_pace_speed = 0;

	//engine_board_manager_init();
	engine_command_manager_init();
	engine_cursor_manager_init();

	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_gamer_manager_init();
	engine_enemy_manager_init();

	//level_object_multiplier = 1;
	//state_object_prev_screen = screen_type_none;
	st->state_object_curr_screen = screen_type_none;
	st->state_object_next_screen = screen_type_none;
}

void engine_state_manager_read()
{
	struct_state_object *st = &global_state_object;
	unsigned char test;

	// Set default global state.
	engine_hack_manager_init();
	st->state_object_high_score = DEF_HI_SCORE;
	st->state_object_actor_kill = actor_type_kid;

	// Check if global state previously stored.
	test = engine_storage_manager_available();
	if( test )
	{
		engine_storage_manager_read();
	}

	// Invert any hack overrides...
	engine_hack_manager_load();
	engine_hack_manager_invert();
}

void engine_state_manager_write()
{
}