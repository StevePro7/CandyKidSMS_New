#include "storage_manager.h"
#include "..\devkit\_sms_manager.h"
//#include "board_manager.h"
#include "storage_manager.h"
#include "font_manager.h"
#include "..\banks\databank.h"

#define MAGIC			0xACE0B004

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
	//struct_board_object *bo = &global_board_object;
	//struct_command_object *co = &global_command_object;
	//unsigned int idx;

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

	savegame->terminal = 0xFD;
	devkit_SMS_disableSRAM();
}