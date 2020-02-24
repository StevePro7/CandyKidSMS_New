#include "score_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "..\banks\databank.h"
//#include "..\banks\fixedbank.h"
//#include "..\devkit\_sms_manager.h"

#define TEXT_X		SCREEN_TILE_LEFT + 25
#define DATA_X		SCREEN_TILE_LEFT + 28

#define TITLE_Y		0
#define HIGHS_Y		4
#define SCORE_Y		8
#define LIVES_Y		12
#define LEVEL_Y		16
#define BOOST_Y		20
//#define WORLD_Y		14
//#define ROUNT_Y		18

// Global variable.
struct_score_object global_score_object;

static unsigned char bonuses[] = { 10, 20, 40, 80 };
static void reset();
static void update_score( unsigned char points );
static void update_lives( signed char value );
static void draw_highs();
static void draw_score();
static void draw_lives();
static void draw_level();
static void draw_boost();
static void draw_world();
static void draw_round();
static unsigned char calc_level();
static void draw_zero( unsigned char x, unsigned char y );

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
	update_score( bonus );
}

void engine_score_manager_update_candy()
{
	struct_score_object *so = &global_score_object;
	so->candy++;
	so->total++;
	update_score( 1 );
}

void engine_score_manager_update_oneup()
{
	struct_score_object *so = &global_score_object;
	so->total++;
	update_lives( 1 );
}

void engine_score_manager_update_lives( signed char value )
{
	update_lives( value );
}

void engine_score_manager_draw_all()
{
	struct_score_object *so = &global_score_object;

	draw_zero( DATA_X + 1, HIGHS_Y + 1 );
	draw_zero( DATA_X + 1, SCORE_Y + 1 );

	//engine_font_manager_draw_long( MAX_HI_SCORE, 30, 11 );

	//engine_font_manager_draw_char( '0', 31, 15 );
	//engine_font_manager_draw_long( so->score, 30, 15 );

	draw_highs();
	draw_score();
	draw_lives();
	draw_level();
	draw_boost();
}

void engine_score_manager_draw_text()
{
	engine_font_manager_draw_text( LOCALE_TITLE1_TEXT, TEXT_X, TITLE_Y + 0 );
	engine_font_manager_draw_text( LOCALE_TITLE2_TEXT, TEXT_X, TITLE_Y + 1 );
	engine_font_manager_draw_text( LOCALE_HIGHS_TEXT, TEXT_X, HIGHS_Y + 0 );
	engine_font_manager_draw_text( LOCALE_SCORE_TEXT, TEXT_X, SCORE_Y + 0 );
	engine_font_manager_draw_text( LOCALE_LIVES_TEXT, TEXT_X, LIVES_Y + 0 );
	engine_font_manager_draw_text( LOCALE_LEVEL_TEXT, TEXT_X, LEVEL_Y + 0 );
	engine_font_manager_draw_text( LOCALE_BOOST_TEXT, TEXT_X, BOOST_Y + 0 );
	//engine_font_manager_draw_text( LOCALE_WORLD_TEXT, TEXT_X, WORLD_Y + 0 );
	//engine_font_manager_draw_text( LOCALE_ROUND_TEXT, TEXT_X, ROUNT_Y + 0 );
}

void engine_score_manager_draw_level()
{

}


static void reset()
{
	struct_score_object *so = &global_score_object;
	unsigned level = calc_level();
	so->score = 0;
	so->lives = NUMBER_LIVES - state_object_difficulty;
	//engine_font_manager_draw_data( state_object_world_data, DATA_X + 1, LEVEL_Y + 3 );
	//engine_font_manager_draw_data( MAX_WORLDS, DATA_X + 1, LEVEL_Y + 4 );
	//engine_font_manager_draw_data( state_object_round_data, DATA_X + 1, LEVEL_Y + 5 );
	//engine_font_manager_draw_data( level, DATA_X + 1, LEVEL_Y + 6 );

	//so->level = state_object_world_data * MAX_WORLDS + state_object_round_data + 1; //calc_level();
	so->level = level;
	so->bonus = 0;
	so->candy = 0;
	so->total = 0;
	so->boost = MAX_BOOSTERX;
	so->delay = state_object_difficulty + 1;
}
static void update_score( unsigned char points )
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
static void update_lives( signed char value )
{
	struct_score_object *so = &global_score_object;
	if( 0 == so->lives && value < 0 )
	{
		return;
	}

	so->lives += value;
	draw_lives();
}

static void draw_highs()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_long( state_object_high_score, DATA_X + 0, HIGHS_Y + 1 );
}
static void draw_score()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_long( so->score, DATA_X + 0, SCORE_Y + 1 );
}

static void draw_lives()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_data( so->lives, DATA_X + 1, LIVES_Y + 1 );
	if( so->lives < 10 )
	{
		draw_zero( DATA_X + 0, LIVES_Y + 1 );
	}
}
static void draw_level()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_data( so->level, DATA_X + 1, LEVEL_Y + 1 );
	if( so->level < 10 )
	{
		draw_zero( DATA_X + 0, LEVEL_Y + 1 );
	}
}
static void draw_boost()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_data( so->boost, DATA_X + 1, BOOST_Y + 1 );
	if( so->boost < 10 )
	{
		draw_zero( DATA_X + 0, BOOST_Y + 1 );
	}
}
static void draw_world()
{
	
}
static void draw_round()
{

}

static unsigned char calc_level()
{
	return state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
}

static void draw_zero( unsigned char x, unsigned char y )
{
	engine_font_manager_draw_char( '0', x, y );
}