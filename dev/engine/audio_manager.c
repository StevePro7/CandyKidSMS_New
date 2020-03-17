#include "audio_manager.h"
#include "state_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\devkit\_snd_manager.h"
#include "..\banks\databank.h"
#include "..\banks\fixedbank.h"

static unsigned char music_bank;
//static unsigned char sound_bank;

// IMPORTANT disable compiler warning 196
//#ifdef _CONSOLE
//#else
//#pragma disable_warning 196
//#endif


// Music.
void engine_audio_manager_music_play( unsigned char index )
{
	struct_state_object *st = &global_state_object;
	const unsigned char *music_data;
	//unsigned char bank;

	if( !st->state_object_music_data )
	{
		return;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	music_data = music_object_data[ index ];
	music_bank = music_object_bank[ index ];

	devkit_SMS_mapROMBank( music_bank );
	devkit_PSGPlay( ( unsigned char* ) music_data );
}
void engine_audio_manager_music_play_norepeat( unsigned char index )
{
	struct_state_object *st = &global_state_object;
	const unsigned char *music;
	unsigned char bank;

	if( !st->state_object_music_data )
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
	devkit_SMS_mapROMBank( music_bank );
	devkit_PSGResume();
}
void engine_audio_manager_music_stop()
{
	devkit_PSGStop();
}

// Sound.
void engine_audio_manager_sound_play( unsigned char index )
{
	struct_state_object *st = &global_state_object;
	const unsigned char *sound;
	unsigned char status;
	unsigned char bank;

	// If sound effects are  disabled then return.
	if( !st->state_object_sound_data )
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

void engine_audio_manager_sfx_play( unsigned char index )
{
	struct_state_object *st = &global_state_object;
	const unsigned char *sfx;
	unsigned char status;

	// If sound effects are  disabled then return.
	if( !st->state_object_sound_data )
	{
		return;
	}

	// If sound effect already playing then return.
	status = devkit_PSGSFXGetStatus();
	if( status )
	{
		return;
	}

	sfx = sfx_object_data[ index ];
	devkit_PSGSFXPlay( ( unsigned char* ) sfx, devkit_SFX_CHANNEL2() );
}