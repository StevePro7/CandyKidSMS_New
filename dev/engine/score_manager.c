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
#define LEVEL_Y		15
#define BOOST_Y		18
#define TEXTS_Y		22
#define WORLD_Y		22
#define ROUNT_Y		23

// Global variable.
struct_score_object global_score_object;

static unsigned char y[] = { LIVES_Y + 1, LEVEL_Y + 1, BOOST_Y + 1, 22, 23 };
static unsigned char bonuses[] = { 10, 20, 40, 80 };
static void reset();
static void update_score( unsigned char points );
static void update_lives( signed char value );

static void draw_value( unsigned char index );
static void draw_highs();
static void draw_score();
//static void draw_lives();
//static void draw_level();
//static void draw_boost();
//static void draw_world();
//static void draw_round();
//static unsigned char calc_level();
static void draw_zero( unsigned char x, unsigned char y );

void engine_score_manager_init()
{
	reset();
}

void engine_score_manager_load()
{
	reset();
}

unsigned char engine_score_manager_get_candy()
{
	struct_score_object *so = &global_score_object;
	return so->candy;
}

void engine_score_manager_update_bonus( unsigned char index )
{
	struct_score_object *so = &global_score_object;

	// The bonus tile enum is 3x values off.
	unsigned char bonus = bonuses[ index - 3 ];
	bonus *= level_object_multiplier;
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

void engine_score_manager_update_boost()
{
	struct_score_object *so = &global_score_object;
	//if( 0 == so->boost )
	if( 0 == so->values[ score_type_boost ] )
	{
		return;
	}

	so->timer++;
	if( so->timer <= so->delay )
	{
		return;
	}

	so->timer = 0;
	so->values[ score_type_boost ]--;
	draw_value( score_type_boost );
	//so->boost--;
	//draw_boost();
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

	draw_value( score_type_lives );
	draw_value( score_type_level );
	draw_value( score_type_boost );
	draw_value( score_type_world );
	draw_value( score_type_round );

	//draw_lives();
	//draw_level();
	//draw_boost();
	//draw_world();
	//draw_round();
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

	//engine_font_manager_draw_text( LOCALE_PLAY1_TEXT, TEXT_X, TEXTS_Y + 0 );
	//engine_font_manager_draw_text( LOCALE_MODES_TEXT, TEXT_X, TEXTS_Y + 1 );
	//engine_font_manager_draw_text( LOCALE_WORLD_TEXT, TEXT_X, WORLD_Y + 0 );
	//engine_font_manager_draw_text( LOCALE_ROUND_TEXT, TEXT_X, ROUNT_Y + 0 );
}

// Call this function on ro load level.
void engine_score_manager_update_level()
{
	struct_score_object *so = &global_score_object;

	//unsigned char level = calc_level();
	// Weird = not sure why giving garbage value when call calc_level()??
	//so->level = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
	so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;

	//so->level = level;
	//so->level = calc_level();

	draw_value( score_type_level );

	// TODO delete this - used for debugging!
	draw_value( score_type_world );
	draw_value( score_type_round );
	// TODO delete this - used for debugging!
	//draw_level();
	//draw_world();
	//draw_round();
}

static void reset()
{
	struct_score_object *so = &global_score_object;
	//unsigned char level = calc_level();
	so->score = 0;
	//so->lives = NUMBER_LIVES - state_object_difficulty;
	so->values[ score_type_lives ] = NUMBER_LIVES - state_object_difficulty;

	//engine_font_manager_draw_data( state_object_world_data, DATA_X + 1, LEVEL_Y + 3 );
	//engine_font_manager_draw_data( MAX_WORLDS, DATA_X + 1, LEVEL_Y + 4 );
	//engine_font_manager_draw_data( state_object_round_data, DATA_X + 1, LEVEL_Y + 5 );
	//engine_font_manager_draw_data( level, DATA_X + 1, LEVEL_Y + 6 );

	// Weird = not sure why giving garbage value when call calc_level()??
	//so->level = state_object_world_data * MAX_WORLDS + state_object_round_data + 1; //calc_level();
	so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
	//so->level = calc_level();
	//so->level = level;

	so->bonus = 0;
	so->candy = 0;
	so->total = 0;
	//so->boost = MAX_BOOSTERX;
	so->values[ score_type_boost ] = MAX_BOOSTERX;
	so->delay = 1 - state_object_difficulty;
	so->timer = 0;
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
	//if( 0 == so->lives && value < 0 )
	if( 0 == so->values[ score_type_lives ] && value < 0 )
	{
		return;
	}

	so->values[ score_type_lives ] += value;
	draw_value( score_type_lives );
	//so->lives += value;
	//draw_lives();
}

static void draw_highs()
{
	engine_font_manager_draw_long( state_object_high_score, DATA_X + 0, HIGHS_Y + 1 );
}
static void draw_score()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_long( so->score, DATA_X + 0, SCORE_Y + 1 );
}

//static void draw_lives()
//{
//	struct_score_object *so = &global_score_object;
//	engine_font_manager_draw_data( so->lives, DATA_X + 1, LIVES_Y + 1 );
//	if( so->lives < 10 )
//	{
//		draw_zero( DATA_X + 0, LIVES_Y + 1 );
//	}
//}
//static void draw_level()
//{
//	struct_score_object *so = &global_score_object;
//	engine_font_manager_draw_data( so->level, DATA_X + 1, LEVEL_Y + 1 );
//	if( so->level < 10 )
//	{
//		draw_zero( DATA_X + 0, LEVEL_Y + 1 );
//	}
//}
//static void draw_boost()
//{
//	struct_score_object *so = &global_score_object;
//	engine_font_manager_draw_data( so->boost, DATA_X + 1, BOOST_Y + 1 );
//	if( so->boost < 10 )
//	{
//		draw_zero( DATA_X + 0, BOOST_Y + 1 );
//	}
//}
//static void draw_world()
//{
//	unsigned char world = state_object_world_data + 1;
//	engine_font_manager_draw_data( world, DATA_X + 1, 22 );
//	if( world < 10 )
//	{
//		draw_zero( DATA_X + 0, 22 );
//	}
//}
//static void draw_round()
//{
//	unsigned char round = state_object_round_data + 1;
//	engine_font_manager_draw_data( round, DATA_X + 1, 23 );
//	if( round < 10 )
//	{
//		draw_zero( DATA_X + 0, 23 );
//	}
//}

static void draw_value( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	unsigned char y_val = y[ index ];
	unsigned char value = 0;
	
	if( index < score_type_world )
	{
		value = so->values[ index ];
	}
	else if( score_type_world == index )
	{
		value = state_object_world_data + 1;
	}
	else if( score_type_round == index )
	{
		value = state_object_round_data + 1;
	}

	engine_font_manager_draw_data( value, DATA_X + 1, y_val );
	if( value < 10 )
	{
		draw_zero( DATA_X + 0, y_val );
	}
}

//static unsigned char calc_level()
//{
//	return state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
//}

static void draw_zero( unsigned char x, unsigned char y )
{
	engine_font_manager_draw_char( '0', x, y );
}