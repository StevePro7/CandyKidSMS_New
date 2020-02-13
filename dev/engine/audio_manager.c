#include "audio_manager.h"
#include "font_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\devkit\_snd_manager.h"
#include "..\object\audio_object.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

// IMPORTANT disable compiler warning 196
#ifdef _CONSOLE
#else
#pragma disable_warning 196
#endif

// Private helper functions.
//static void play_music( unsigned char *music, unsigned char bank );
//static void play_music_norepeat( unsigned char *music, unsigned char bank );
//static void play_sound( unsigned char *sound );

// Music.
//void engine_audio_manager_music_game( unsigned char index )
//{
//	play_music( ( unsigned char* ) game_audio_data[ index ], game_audio_bank[ index ] );
//}
//void engine_audio_manager_music_title()
//{
//	play_music_norepeat( ( unsigned char* ) title_audio_data[ 0 ], title_audio_bank[ 0 ] );
//}
//void engine_audio_manager_music_over()
//{
//	play_music_norepeat( ( unsigned char* ) over_audio_data[ 0 ], over_audio_bank[ 0 ] );
//}
//void engine_audio_manager_music_beat()
//{
//	play_music_norepeat( ( unsigned char* ) beat_audio_data[ 0 ], beat_audio_bank[ 0 ] );
//}

// Music.
void engine_audio_manager_music_play( unsigned char index )
{
	//struct_hack_object *ho = &global_hack_object;
	//if( !ho->hack_music )
	//{
	//	return;
	//]}

	const unsigned char *music;
	unsigned char bank;

	devkit_SMS_mapROMBank( FIXED_BANK );
	music = music_object_data[ index ];
	bank = music_object_bank[ index ];

	devkit_SMS_mapROMBank( bank );
	devkit_PSGPlay( ( unsigned char* ) music );
}
void engine_audio_manager_music_play_norepeat( unsigned char index )
{
	//struct_hack_object *ho = &global_hack_object;
	//if( !ho->hack_music )
	//{
	//	return;
	//}

	const unsigned char *music;
	unsigned char bank;

	devkit_SMS_mapROMBank( FIXED_BANK );
	music = music_object_data[ index ];
	bank = music_object_bank[ index ];

	devkit_SMS_mapROMBank( bank );
	devkit_PSGPlayNoRepeat( ( unsigned char* ) music );
}


// Sound.
void engine_audio_manager_sound_play( unsigned char index )
{
	const unsigned char *sound;
	unsigned char status;
	unsigned char bank;

	// If sound effects are  disabled then return.
	if( !state_object_sound_on )
	{
		return;
	}

	// If sound effect already playing then return.
	status = devkit_PSGSFXGetStatus();
	if( status )
	{
		return;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	sound = sound_object_data[ index ];
	bank = sound_object_bank[ index ];

	devkit_SMS_mapROMBank( bank );
	devkit_PSGSFXPlay( ( unsigned char* ) sound, devkit_SFX_CHANNEL2() );
}

//static void play_music( unsigned char *music, unsigned char bank )
//{
//	//struct_hack_object *ho = &global_hack_object;
//	//if( !ho->hack_music )
//	//{
//	//	return;
//	//]}
//
//	devkit_SMS_mapROMBank( bank );
//	devkit_PSGPlay( music );
//}
//static void play_music_norepeat( unsigned char *music, unsigned char bank )
//{
//	//struct_hack_object *ho = &global_hack_object;
//	//if( !ho->hack_music )
//	//{
//	//	return;
//	//}
//
//	devkit_SMS_mapROMBank( bank );
//	devkit_PSGPlayNoRepeat( music );
//}
//static void play_sound( unsigned char *sound )
//{
//	unsigned char status;
//	//struct_hack_object *ho = &global_hack_object;
//
//	//if( !ho->hack_sound )
//	//{
//	//	return;
//	//}
//
//	// If sound effect already playing then return.
//	status = devkit_PSGSFXGetStatus();
//	if( status )
//	{
//		return;
//	}
//
//	devkit_PSGSFXPlay( sound, devkit_SFX_CHANNEL2() );
//}