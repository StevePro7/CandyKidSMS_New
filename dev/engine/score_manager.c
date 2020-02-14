#include "score_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "..\banks\databank.h"

// Global variable.
struct_score_object global_score_object;

static unsigned char bonuses[] = { 10, 20, 40, 80 };
static void reset();
static void calculate( unsigned char points );

void engine_score_manager_init()
{
	reset();
}

void engine_score_manager_load()
{
	reset();
}

unsigned char engine_score_manager_get_total()
{
	struct_score_object *so = &global_score_object;
	return so->total;
}

void engine_score_manager_update_bonus( unsigned char index )
{
	struct_score_object *so = &global_score_object;

	// The bonus tile enum is 2x values off.
	unsigned char bonus = bonuses[ index - 2 ];
	so->bonus++;
	so->total++;
	calculate( bonus );
}

void engine_score_manager_update_candy()
{
	struct_score_object *so = &global_score_object;
	so->candy++;
	so->total++;
	calculate( 1 );
}

void engine_score_manager_draw_all()
{
	struct_score_object *so = &global_score_object;

	engine_font_manager_draw_char( '0', 31, 11 );
	engine_font_manager_draw_long( MAX_HI_SCORE, 30, 11 );

	engine_font_manager_draw_char( '0', 31, 15 );
	engine_font_manager_draw_long( so->my_score, 30, 15 );
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

static void calculate( unsigned char points )
{
	struct_score_object *so = &global_score_object;
	so->my_score += points;

	if( so->my_score > MAX_HI_SCORE )
	{
		so->my_score = MAX_HI_SCORE;
		engine_font_manager_draw_char( '9', 31, 11 );
	}
	if( so->my_score > state_object_high_score )
	{
		state_object_high_score = so->my_score;
	}
}