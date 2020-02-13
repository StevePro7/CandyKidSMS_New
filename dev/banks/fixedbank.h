// Fixed  bank.
#define FIXED_BANK	15

// Board Manager.
extern const unsigned char board_object_posnX[];
extern const unsigned char board_object_posnY[];

extern const unsigned char board_object_homeX[];
extern const unsigned char board_object_homeY[];
// TODO permanently delet as don't believe necc. as will calcSpots() "Z"
//extern const unsigned char board_object_homeZ[];

extern const unsigned char board_object_exitX;
extern const unsigned char board_object_exitY;
extern const unsigned char board_object_top;
extern const unsigned char board_object_bottom;
extern const unsigned char board_object_left;
extern const unsigned char board_object_middle;
extern const unsigned char board_object_right;


// Enemy Manager.
extern const unsigned char enemy_object_directions[];

// Audio Manager.
//extern const unsigned char *music_object_data[];
//extern const unsigned char music_object_bank[];
extern const unsigned char *sound_object_data[];
extern const unsigned char sound_object_bank[];


// Level Manager.
extern const unsigned char *level_object_AAdata[];
extern const unsigned char level_object_AAsize[];
extern const unsigned char level_object_AAbank[];

extern const unsigned char *level_object_BBdata[];
extern const unsigned char level_object_BBsize[];
extern const unsigned char level_object_BBbank[];