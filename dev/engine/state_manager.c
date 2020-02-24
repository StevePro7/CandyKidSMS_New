#include "state_manager.h"
#include "enum_manager.h"
#include "global_manager.h"
#include "hack_manager.h"
#include "storage_manager.h"
#include "..\banks\databank.h"

void engine_state_manager_read()
{
	unsigned char test;

	// Set default global state.
	engine_hack_manager_init();
	state_object_high_score = DEF_HI_SCORE;
	state_object_actor_kill = actor_type_kid;

	// Check if global state previously stored.
	test = engine_storage_manager_available();
	if( test )
	{
		engine_storage_manager_read();
	}

	// Invert any hack overrides...
	engine_hack_manager_invert();
}

void engine_state_manager_write()
{
}