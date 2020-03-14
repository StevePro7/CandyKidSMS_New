#include "hack_manager.h"
#include "global_manager.h"
#include "enum_manager.h"
#include "..\banks\databank.h"

#define PEEK( addr)			(* ( unsigned char *)( addr ) )
#define POKE( addr, data )	(* ( unsigned char *)( addr ) = ( data ) )

#define HACKER_START		0x0050

// TODO delete this - set only during debugging / play testing
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#pragma disable_warning 126
#endif

void engine_hack_manager_init()
{
	state_object_mydebugger = 0;
	state_object_full_boost = 0;
	state_object_invincibie = 0;

	state_object_difficulty = 0;
	state_object_pace_speed = 0;
	state_object_trees_type = 0;
	state_object_exits_type = 0;

	state_object_world_data = 0;
	state_object_round_data = 0;
	state_object_music_data = 0;
	state_object_sound_data = 0;

	// TODO delete - used for testing...!!
	state_object_delay_test = 0;
}

void engine_hack_manager_load()
{
#ifndef _CONSOLE

	state_object_mydebugger = PEEK( HACKER_START - 3 );			// 0x004D		// Set my debugging from zero-based value.
	state_object_full_boost = PEEK( HACKER_START - 2 );			// 0x004E		// Set maximum boost for zero-based value.
	state_object_invincibie = PEEK( HACKER_START - 1 );			// 0x004F		// Set invincibility for zero-based value.

	state_object_difficulty = PEEK( HACKER_START + 0 );			// 0x0050		// Set the difficulty to zero-based value.
	state_object_pace_speed = PEEK( HACKER_START + 1 );			// 0x0051		// Set the game speed to zero-based value.
	state_object_trees_type = PEEK( HACKER_START + 2 );			// 0x0052		// Set start treeType to zero-based value.
	state_object_exits_type = PEEK( HACKER_START + 3 );			// 0x0053		// Set start exitType to zero-based value.

	state_object_world_data = PEEK( HACKER_START + 4 );			// 0x0054		// Set start world no to zero-based value.
	state_object_round_data = PEEK( HACKER_START + 5 );			// 0x0055		// Set start round no to zero-based value.
	state_object_music_data = PEEK( HACKER_START + 6 );			// 0x0056		// Set 0=music to play otherwise disabled.
	state_object_sound_data = PEEK( HACKER_START + 7 );			// 0x0057		// Set 0=sound to play otherwise disabled.

	// TODO delete - used for testing...!!
	state_object_delay_test = PEEK( HACKER_START + 8 );			// 0x0058		// Set 0 enables all delays otherwise off.

#endif
}

void engine_hack_manager_invert()
{
	// TODO delete this hard coded
	//state_object_difficulty = 0;
	//state_object_pace_speed = 0;
	state_object_trees_type = 0;
	state_object_exits_type = 0;
	state_object_invincibie = 0;

	state_object_enemy_move[ actor_type_pro ] = 1;
	state_object_enemy_move[ actor_type_adi ] = 1;
	state_object_enemy_move[ actor_type_suz ] = 1;

	//state_object_enemy_move[ actor_type_pro ] = 0;
	//state_object_enemy_move[ actor_type_adi ] = 0;
	//state_object_enemy_move[ actor_type_suz ] = 0;

	state_object_mydebugger = 1;		// TODO don't forget to remove this!!
	state_object_full_boost = 0;
	state_object_delay_test = 0;
	// TODO delete this hard coded

	// Trees.
	state_object_trees_type = tree_type_death == state_object_trees_type ? tree_type_death : tree_type_avoid;

	// Exits.
	state_object_exits_type = exit_type_closed == state_object_exits_type ? exit_type_closed : exit_type_public;


	// World.
	if( 0 != state_object_world_data )
	{
		if( state_object_world_data > MAX_WORLDS )
		{
			state_object_world_data = MAX_WORLDS;
		}

		// Zero-based index.
		state_object_world_data -= 1;
	}

	// Round.
	if( 0 != state_object_round_data )
	{
		if( state_object_round_data > MAX_ROUNDS )
		{
			state_object_round_data = MAX_ROUNDS;
		}

		// Zero-based index.
		state_object_round_data -= 1;
	}

	// Invert default values.
	// TODO revert this code to play music + sound FX.
	state_object_music_data = !state_object_music_data;
	state_object_sound_data = !state_object_sound_data;
	// TODO revert this code to play music + sound FX.

	// TODO delete this hard coded
	state_object_world_data = 4 - 1;
	state_object_round_data = 10 - 1;

	//state_object_world_data = 8 - 1;
	//state_object_round_data = 9 - 1;
	// TODO delete this hard coded
}