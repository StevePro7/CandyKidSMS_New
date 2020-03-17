#include "replay_screen.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\state_manager.h"
#include "..\banks\databank.h"

void screen_replay_screen_load()
{
	struct_state_object *st = &global_state_object;
	engine_font_manager_draw_text( "REPLAY SCREEN...!!", 2, 10 );
	engine_font_manager_draw_data( st->state_object_high_score, 20, 20);
}

void screen_replay_screen_update( unsigned char *screen_type )
{
	*screen_type = screen_type_replay;
}
