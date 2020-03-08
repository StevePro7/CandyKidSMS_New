#include "score_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"
#include "..\devkit\_sms_manager.h"

//#define TEXT_X		SCREEN_TILE_LEFT + 24
//#define DATA_X		SCREEN_TILE_LEFT + 28

#define TITLE_Y		0
#define HIGHS_Y		4
#define SCORE_Y		8
#define LIVES_Y		12
#define LEVEL_Y		15
#define BOOST_Y		18
#define TEXTS_Y		22
#define WORLD_Y		22
#define ROUNT_Y		23

// IMPORTANT disable compiler warning 196
//#ifdef _CONSOLE
//#else
//#pragma disable_warning 196
//#endif

// Global variable.
struct_score_object global_score_object;

static unsigned char bonuses[] = { 10, 20, 40, 80, 200 };
static unsigned char boost_X[] = { 200, 100 };
static unsigned char value_y[] = { LIVES_Y + 1, LEVEL_Y + 1, BOOST_Y + 1, 22, 23 };
static unsigned char title_Y[] = { TITLE_Y, TITLE_Y + 1, HIGHS_Y, SCORE_Y, LIVES_Y, LEVEL_Y, BOOST_Y, };

// TODO need to split the reset functionality.
//static void reset();
static void update_score( unsigned char points );
static void update_lives( signed char value );

static void draw_value( unsigned char index );
static void draw_highs();
static void draw_score();
static void draw_zero( unsigned char x, unsigned char y );

void engine_score_manager_text()
{
	const unsigned char *text;
	unsigned char index;

	// IMPORTANT need to ROM bank text.
	devkit_SMS_mapROMBank( FIXED_BANK );
	for( index = 0; index < 7; index++ )
	{
		text = locale_object_texts[ index + 1 ];
		engine_font_manager_draw_text( text, TEXT_X, title_Y[ index ] );
	}
}

void engine_score_manager_init()
{
	struct_score_object *so = &global_score_object;
	so->score = 0;
	so->values[ score_type_lives ] = NUMBER_LIVES - state_object_difficulty;
	so->values[ score_type_lives ] = 1; // stevepro

	//so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
	//so->bonus = 0;
	//so->candy = 0;
	//so->total = 0;
	//so->values[ score_type_boost ] = boost_X[ state_object_difficulty ];

	draw_zero( DATA_X + 1, HIGHS_Y + 1 );
	draw_zero( DATA_X + 1, SCORE_Y + 1 );
	draw_highs();
	draw_score();
	draw_value( score_type_lives );
}

void engine_score_manager_load()
{
	struct_score_object *so = &global_score_object;
	//so->score = 0;
	//so->values[ score_type_lives ] = NUMBER_LIVES - state_object_difficulty;
	so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
	so->bonus = 0;
	so->candy = 0;
	//so->total = 0;
	so->values[ score_type_boost ] = boost_X[ state_object_difficulty ];
	//so->delay = 1 - state_object_difficulty;
	//so->timer = 0;

	draw_value( score_type_level );
	draw_value( score_type_boost );
}

unsigned char engine_score_manager_get_candy()
{
	struct_score_object *so = &global_score_object;
	return so->candy;
}
unsigned char engine_score_manager_get_value( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	return so->values[ index ];
}
//unsigned char engine_score_manager_get_lives()
//{
//	struct_score_object *so = &global_score_object;
//	return so->values[ score_type_lives ];
//}
//unsigned char engine_score_manager_get_boost()
//{
//	struct_score_object *so = &global_score_object;
//	return so->values[ score_type_boost ];
//}

void engine_score_manager_finish_bonus()
{
	struct_score_object *so = &global_score_object;
	unsigned char bonus = bonuses[ 4 ];
	update_score( bonus );
}

void engine_score_manager_update_bonus( unsigned char index )
{
	struct_score_object *so = &global_score_object;

	// The bonus tile enum is 3x values off.
	unsigned char bonus = bonuses[ index - 3 ];
	bonus *= level_object_multiplier;
	so->bonus++;
	//so->total++;
	update_score( bonus );
}

void engine_score_manager_update_candy()
{
	struct_score_object *so = &global_score_object;
	so->candy++;
	//so->total++;
	update_score( 1 );
}

void engine_score_manager_update_oneup()
{
	struct_score_object *so = &global_score_object;
	//so->total++;
	update_lives( 1 );
}

void engine_score_manager_update_lives( signed char value )
{
	update_lives( value );
}

void engine_score_manager_update_boost()
{
	struct_score_object *so = &global_score_object;
	if( state_object_full_boost )
	{
		return;
	}

	if( 0 == so->values[ score_type_boost ] )
	{
		return;
	}

	//so->timer++;
	//if( so->timer <= so->delay )
	//{
	//	return;
	//}

	//so->timer = 0;
	so->values[ score_type_boost ]--;

	// TODO set enum or #define for this magic no.
	// TODO Easy = 200  Hard = 100 boost value!
	if( 0 == so->values[ score_type_boost ] % 10 )
	{
	//	draw_value( score_type_boost );
	}

	draw_value( score_type_boost );
}
//void engine_score_manager_draw_all()
//{
//	struct_score_object *so = &global_score_object;
//
//	draw_zero( DATA_X + 1, HIGHS_Y + 1 );
//	draw_zero( DATA_X + 1, SCORE_Y + 1 );
//	draw_highs();
//	draw_score();
//
//	draw_value( score_type_lives );
//	draw_value( score_type_level );
//	draw_value( score_type_boost );
//	draw_value( score_type_world );
//	draw_value( score_type_round );
//}



void engine_score_manager_draw_init()
{
		draw_zero( DATA_X + 1, HIGHS_Y + 1 );
		draw_zero( DATA_X + 1, SCORE_Y + 1 );
		draw_highs();
		draw_score();
		draw_value( score_type_lives );
}
void engine_score_manager_draw_load()
{
		draw_value( score_type_level );
		draw_value( score_type_boost );
		//draw_value( score_type_world );
		//draw_value( score_type_round );
}

// Call this function on ro load level.
void engine_score_manager_update_level()
{
	struct_score_object *so = &global_score_object;
	so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
	draw_value( score_type_level );

	// TODO delete this - used for debugging!
	draw_value( score_type_world );
	draw_value( score_type_round );
	// TODO delete this - used for debugging!
}

void engine_score_manager_reset_lives()
{
	struct_score_object *so = &global_score_object;
	so->values[ score_type_lives ] = NUMBER_LIVES - state_object_difficulty;
	draw_value( score_type_lives );
}
void engine_score_manager_reset_boost()
{
	struct_score_object *so = &global_score_object;
	so->values[ score_type_boost ] = boost_X[ state_object_difficulty ];
	draw_value( score_type_boost );
}

//static void reset()
//{
//	struct_score_object *so = &global_score_object;
//	so->score = 0;
//	so->values[ score_type_lives ] = NUMBER_LIVES - state_object_difficulty;
//	so->values[ score_type_level ] = state_object_world_data * MAX_WORLDS + state_object_round_data + 1;
//
//	so->bonus = 0;
//	so->candy = 0;
//	//so->total = 0;
//	so->values[ score_type_boost ] = boost_X[ state_object_difficulty ];
//	//so->delay = 1 - state_object_difficulty;
//	//so->timer = 0;
//}

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
	if( 0 == so->values[ score_type_lives ] && value < 0 )
	{
		return;
	}
	if( 99 == so->values[ score_type_lives ] && value > 0 )
	{
		return;
	}

	so->values[ score_type_lives ] += value;
	draw_value( score_type_lives );
}

static void draw_highs()
{
	//engine_font_manager_draw_long( state_object_high_score, DATA_X + 0, HIGHS_Y + 1 );
	engine_font_manager_draw_data( state_object_high_score, DATA_X + 0, HIGHS_Y + 1 );
	//engine_font_manager_draw_data( 2334, DATA_X + 0, HIGHS_Y + 1 );
}
static void draw_score()
{
	struct_score_object *so = &global_score_object;
	//engine_font_manager_draw_long( so->score, DATA_X + 0, SCORE_Y + 1 );
	engine_font_manager_draw_data( so->score, DATA_X + 0, SCORE_Y + 1 );
}

static void draw_value( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	unsigned char y_val = value_y[ index ];
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

	// HACK to workaround side tile for exit.
	if( score_type_level == index && exit_type_public == state_object_exits_type )
	{
		engine_font_manager_draw_data4( value, DATA_X + 1, y_val );
	}
	else
	{
		engine_font_manager_draw_data( value, DATA_X + 1, y_val );
	}

	if( value < 10 )
	{
		draw_zero( DATA_X + 0, y_val );
	}
}

static void draw_zero( unsigned char x, unsigned char y )
{
	engine_font_manager_draw_char( '0', x, y );
}