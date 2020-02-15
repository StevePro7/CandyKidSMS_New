#include "score_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "..\banks\databank.h"


#define HIGHS_Y		4
#define SCORE_Y		8
#define BONUS_Y		12
#define CANDY_Y		16

// Global variable.
struct_score_object global_score_object;

static unsigned char bonuses[] = { 10, 20, 40, 80 };
static void reset();
static void update( unsigned char points );
static void draw_highs();
static void draw_score();

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

	// The bonus tile enum is 3x values off.
	unsigned char bonus = bonuses[ index - 3 ];
	so->bonus++;
	so->total++;
	update( bonus );
}

void engine_score_manager_update_candy()
{
	struct_score_object *so = &global_score_object;
	so->candy++;
	so->total++;
	update( 1 );
}

void engine_score_manager_draw_all()
{
	struct_score_object *so = &global_score_object;

	engine_font_manager_draw_char( '0', 31, 1 );
	engine_font_manager_draw_char( '0', 31, 5 );
	//engine_font_manager_draw_char( '0', 31, 11 );
	//engine_font_manager_draw_long( MAX_HI_SCORE, 30, 11 );

	//engine_font_manager_draw_char( '0', 31, 15 );
	//engine_font_manager_draw_long( so->score, 30, 15 );

	draw_highs();
	draw_score();
}

void engine_score_manager_draw_text()
{
	engine_font_manager_draw_text( LOCALE_HIGHS_TEXT, 28, 0 );
	engine_font_manager_draw_text( LOCALE_SCORE_TEXT, 27, 4 );
	//engine_font_manager_draw_text( LOCALE_BONUS_TEXT, 27, 8 );
	//engine_font_manager_draw_text( LOCALE_CANDY_TEXT, 27, 12 );
	engine_font_manager_draw_text( LOCALE_WORLD_TEXT, 27, 16 );
	engine_font_manager_draw_text( LOCALE_ROUND_TEXT, 27, 20 );
}

//void engine_score_manager_draw_bonus()
//{
//	struct_score_object *so = &global_score_object;
//	engine_font_manager_draw_data( so->bonus, 30, 9 );
//}

void engine_score_manager_draw_candy()
{

}

static void reset()
{
	struct_score_object *so = &global_score_object;
	so->score = 0;
	so->lives = NUMBER_LIVES - state_object_difficulty;
	so->bonus = MAX_BOOSTERX;
	so->delay = state_object_difficulty + 1;
	so->bonus = 0;
	so->candy = 0;
	so->total = 0;
}
static void update( unsigned char points )
{
	struct_score_object *so = &global_score_object;
	so->score += points;

	if( so->score > MAX_HI_SCORE )
	{
		so->score = MAX_HI_SCORE;
	}
	if( so->score > state_object_high_score )
	{
		state_object_high_score = so->score;
		draw_highs();
	}

	draw_score();
}
static void draw_highs()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_long( state_object_high_score, 30, 1 );
}
static void draw_score()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_long( so->score, 30, 5 );
}