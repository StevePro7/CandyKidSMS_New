#include "score_manager.h"
#include "enum_manager.h"
#include "global_manager.h"
#include "..\banks\databank.h"

// Global variable.
struct_score_object global_score_object;

static void reset();

void engine_score_manager_init()
{
	reset();
}

void engine_score_manager_load()
{
	reset();
}

void engine_score_manager_update()
{
}

static void reset()
{
	struct_score_object *so = &global_score_object;
	so->my_score = 0;
	so->lives = NUMBER_LIVES - state_object_difficulty;
	so->bonus = MAX_BOOSTERX;
	so->delay = state_object_difficulty + 1;
	so->bonus = 0;
	so->candy = 0;
	so->total = 0;
	
}