#include "memo_manager.h"
#include "board_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"

void engine_memo_manager_draw( unsigned char *topLine, unsigned char *botLine )
{
	unsigned char x = SCREEN_TILE_LEFT + LFT_SIDE_X + 8;
	unsigned char y = TOP_SIDE_Y + 10;

	engine_board_manager_midd_text();
	engine_font_manager_draw_text( LOCALE_BLANK_SIZE8, x, y + 0 );
	engine_font_manager_draw_text( topLine,x, y + 1 );
	engine_font_manager_draw_text( botLine, x, y + 2 );
	engine_font_manager_draw_text( LOCALE_BLANK_SIZE8, x, y + 3 );
}