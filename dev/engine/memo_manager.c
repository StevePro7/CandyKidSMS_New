#include "memo_manager.h"
#include "board_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "score_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

void engine_memo_manager_draw( unsigned char topIndex, unsigned char botIndex )
{
	unsigned char x = SCREEN_TILE_LEFT + LFT_SIDE_X + 8;
	unsigned char y = TOP_SIDE_Y + 10;

	engine_locale_manager_draw_text( topIndex, x, y + 1 );
	engine_locale_manager_draw_text( botIndex, x, y + 2 );
}

void engine_memo_manager_pass( unsigned char perfect )
{
	unsigned char topIndex = 15;
	unsigned char botIndex = 16;

	if( perfect )
	{
		botIndex = 17;
	}

	engine_memo_manager_draw( topIndex, botIndex );
}

void engine_memo_manager_bonus( unsigned char perfect )
{
	unsigned char topIndex = 18;
	unsigned char botIndex = 19;

	if( perfect )
	{
		topIndex = 20;
		botIndex = 21;
	}

	engine_memo_manager_draw( topIndex, botIndex );
}