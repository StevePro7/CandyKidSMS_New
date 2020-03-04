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

	engine_board_manager_midd_text();
	engine_locale_manager_draw_text( topIndex, x, y + 1 );
	engine_locale_manager_draw_text( botIndex, x, y + 2 );
}

void engine_memo_manager_pass( unsigned char perfect )
{
	//unsigned char *text = ( unsigned char * ) LOCALE_PASS_MESSAGE2;

	//if( perfect )
	//{
	//	text = ( unsigned char * ) LOCALE_PASS_MESSAGE3;
	//}

	//engine_memo_manager_draw( LOCALE_PASS_MESSAGE1, text );
}

void engine_memo_manager_bonus( unsigned char perfect )
{
	//unsigned char *text1 = ( unsigned char * ) LOCALE_BONUS_MESSAGE1;
	//unsigned char *text2 = ( unsigned char * ) LOCALE_BONUS_MESSAGE2;

	//if( perfect )
	//{
	//	text1 = ( unsigned char * ) LOCALE_BONUS_MESSAGE3;
	//	text2 = ( unsigned char * ) LOCALE_BONUS_MESSAGE4;
	//}

	//engine_memo_manager_draw( text1, text2 );
}