#include "option_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\devkit\_snd_manager.h"

static unsigned char att = 0;

void screen_option_screen_load()
{
	engine_font_manager_draw_text( "OPTION SCREEN.!!", 2, 10 );
	engine_audio_manager_music_play( music_type_game03 );
}

void screen_option_screen_update( unsigned char *screen_type )
{
	unsigned char input;

	input = engine_input_manager_hold( input_type_up );
	input = engine_input_manager_hold( input_type_down );

	//devkit_PSGSetMusicVolumeAttenuation( 10 );

	//*screen_type = screen_type_init;
	*screen_type = screen_type_option;
}
