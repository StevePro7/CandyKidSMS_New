#include "hack_manager.h"
#include "global_manager.h"
#include "enum_manager.h"
#include "..\banks\databank.h"

#define PEEK( addr)			(* ( unsigned char *)( addr ) )
#define POKE( addr, data )	(* ( unsigned char *)( addr ) = ( data ) )

#define HACKER_START		0x0050

// Global variable.
//struct_hack_object global_hack_object;

void engine_hack_manager_init()
{
	//struct_hack_object *ho = &global_hack_object;

	state_object_tree_type = 0;
	state_object_exit_type = 0;
	state_object_world_no = 0;
	state_object_round_no = 0;
	state_object_music_on = 0;
	state_object_sound_on = 0;

#ifndef _CONSOLE

	state_object_tree_type = PEEK( HACKER_START + 0 );			// 0x0050		// Set start treeType to zero-based value.
	state_object_exit_type = PEEK( HACKER_START + 1 );			// 0x0051		// Set start exitType to zero-based value.
	state_object_world_no = PEEK( HACKER_START + 2 );			// 0x0052		// Set start world no to zero-based value.
	state_object_round_no = PEEK( HACKER_START + 3 );			// 0x0053		// Set start round no to zero-based value.
	state_object_music_on = PEEK( HACKER_START + 4 );			// 0x0054		// Set 0=music to play otherwise disabled.
	state_object_sound_on = PEEK( HACKER_START + 5 );			// 0x0055		// Set 0=sound to play otherwise disabled.

#endif

}


void engine_hack_manager_invert()
{
	//struct_hack_object *ho = &global_hack_object;

	// Trees.
	state_object_tree_type = tree_type_death == state_object_tree_type ? tree_type_death : tree_type_avoid;

	// Exits.
	state_object_exit_type = exit_type_closed == state_object_tree_type ? exit_type_closed : exit_type_public;

	// World.
	if( 0 != state_object_world_no )
	{
		if( state_object_world_no > MAX_WORLDS )
		{
			state_object_world_no = MAX_WORLDS;
		}

		// Zero-based index.
		state_object_world_no -= 1;
	}

	// Round.
	if( 0 != state_object_round_no )
	{
		if( state_object_round_no > MAX_ROUNDS )
		{
			state_object_round_no = MAX_ROUNDS;
		}

		// Zero-based index.
		state_object_round_no -= 1;
	}

	// Invert default values.
	state_object_music_on = !state_object_music_on;
	state_object_sound_on = !state_object_sound_on;


	state_object_world_no = 7-1;
	state_object_round_no = 9-1;
}