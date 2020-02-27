// Global state.
extern unsigned char state_object_mydebugger;
extern unsigned char state_object_full_boost;
extern unsigned char state_object_invincibie;
extern unsigned long state_object_high_score;

extern unsigned char state_object_trees_type;
extern unsigned char state_object_exits_type;
extern unsigned char state_object_difficulty;
extern unsigned char state_object_game_speed;

extern unsigned char state_object_world_data;
extern unsigned char state_object_round_data;
extern unsigned char state_object_music_data;
extern unsigned char state_object_sound_data;

extern unsigned char state_object_actor_kill;
extern unsigned char state_object_delay_test;					// TODO delete - used for testing...!!
extern unsigned char state_object_enemy_move[];					// TODO delete


// Board Manager.
extern const unsigned char board_object_posnX[];
extern const unsigned char board_object_posnY[];
extern const unsigned char board_object_homeX[];
extern const unsigned char board_object_homeY[];

// Command Manager.
extern unsigned int command_object_frames[];
extern unsigned char command_object_cmds[];
extern unsigned char command_object_args[];

// Enemy Manager.
extern const unsigned char enemy_object_directions[];

// Level Manager.
extern unsigned char level_object_tiles_array[];
extern unsigned char level_object_bonus_count;
extern unsigned char level_object_candy_count;
extern unsigned char level_object_multiplier;