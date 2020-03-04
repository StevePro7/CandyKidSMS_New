#include "audio_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\devkit\_snd_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

// IMPORTANT disable compiler warning 196
//#ifdef _CONSOLE
//#else
//#pragma disable_warning 196
//#endif


// Music.
void engine_audio_manager_music_play( unsigned char index )
{
	const unsigned char *music;
	unsigned char bank;

	if( !state_object_music_data )
	{
		return;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	music = music_object_data[ index ];
	bank = music_object_bank[ index ];

	devkit_SMS_mapROMBank( bank );
	devkit_PSGPlay( ( unsigned char* ) music );
}
void engine_audio_manager_music_play_norepeat( unsigned char index )
{
	const unsigned char *music;
	unsigned char bank;

	if( !state_object_music_data )
	{
		return;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	music = music_object_data[ index ];
	bank = music_object_bank[ index ];

	devkit_SMS_mapROMBank( bank );
	devkit_PSGPlayNoRepeat( ( unsigned char* ) music );
}
void engine_audio_manager_music_resume()
{
	devkit_PSGResume();
}
void engine_audio_manager_music_stop()
{
	devkit_PSGStop();
}

// Sound.
void engine_audio_manager_sound_play( unsigned char index )
{
	const unsigned char *sound;
	unsigned char status;
	unsigned char bank;

	// If sound effects are  disabled then return.
	if( !state_object_sound_data )
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