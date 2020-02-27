#include "storage_manager.h"
#include "enum_manager.h"
#include "global_manager.h"
#include "storage_manager.h"
#include "..\banks\databank.h"
#include "..\devkit\_sms_manager.h"

#define MAGIC			0xACE0B004
#define FINAL			0xFE

// Global variable.
struct_storage_object global_savegame_object;

unsigned char engine_storage_manager_available()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );
	unsigned char foundMagic;

	devkit_SMS_enableSRAM();
	foundMagic = MAGIC == savegame->Magic;
	devkit_SMS_disableSRAM();
	return foundMagic;
}

void engine_storage_manager_read()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );

	devkit_SMS_enableSRAM();
	state_object_high_score = savegame->save_high_score;

	state_object_trees_type = savegame->save_trees_type;
	state_object_exits_type = savegame->save_exits_type;
	state_object_difficulty = savegame->save_difficulty;
	state_object_game_speed = savegame->save_game_speed;

	state_object_world_data = savegame->save_world_data;
	state_object_round_data = savegame->save_round_data;
	state_object_music_data = savegame->save_music_data;
	state_object_sound_data = savegame->save_sound_data;
	devkit_SMS_disableSRAM();
}

void engine_storage_manager_write()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );

	devkit_SMS_enableSRAM();
	savegame->Magic = MAGIC;
	savegame->save_high_score = state_object_high_score;

	savegame->save_trees_type = state_object_trees_type;
	savegame->save_exits_type = state_object_exits_type;
	savegame->save_difficulty = state_object_difficulty;
	savegame->save_game_speed = state_object_game_speed;

	savegame->save_world_data = state_object_world_data;
	savegame->save_round_data = state_object_round_data;
	savegame->save_music_data = state_object_music_data;
	savegame->save_sound_data = state_object_sound_data;

	savegame->terminal = FINAL;
	devkit_SMS_disableSRAM();
}

void engine_storage_manager_erase()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );

	devkit_SMS_enableSRAM();
	savegame->Magic = MAGIC;
	savegame->save_high_score = DEF_HI_SCORE;

	savegame->save_trees_type = tree_type_avoid;
	savegame->save_exits_type = exit_type_public;
	savegame->save_difficulty = diff_type_easy;
	savegame->save_game_speed = pace_type_slow;

	savegame->save_world_data = 0;
	savegame->save_round_data = 0;
	savegame->save_music_data = 0;
	savegame->save_sound_data = 0;

	savegame->terminal = FINAL;
	devkit_SMS_disableSRAM();
}