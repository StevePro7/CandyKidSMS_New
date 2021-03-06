#ifndef _GLOBAL_MANAGER_H_
#define _GLOBAL_MANAGER_H_

#define MAX_SCREEENS			30
#define CONTENT_BANK			2

#define MAX_ENEMIES				3
#define MAX_ACTORS				MAX_ENEMIES + 1

#define INVALID_INDEX			-1

// Have capacity for 20 worlds i.e. 200 levels
#define TOT_WORLDS				20
#define MAX_WORLDS				10
#define MAX_ROUNDS				10
#define MULTIPLIER_LEVEL		70

#define MAX_ROWS				10
#define MAX_COLS				10

#define TREE_ROWS				12
#define TREE_COLS				12

#define MAZE_ROWS				14
#define MAZE_COLS				14

#define TILE_WIDE				16
#define TILE_HIGH				16

#define TILE_SIZE				16
#define TILE_HALF				8

#define SCREEN_SIZE_WIDE		256
#define SCREEN_SIZE_HIGH		192

#define SCREEN_TILE_WIDE		16
#define SCREEN_TILE_HIGH		12
#define SCREEN_TILE_LEFT		2

#define MAX_EXITS_PUBLIC		8

#define MAX_MOVES_COUNT			10	//1000
#define MAX_SPEED_COUNT			1	//100

#define SPRITE_TILES			256
#define MAX_BLOCK_TILES			12

#define MAX_BYTE_SIZE			256
#define MAX_CMD_TYPE			16	//32
#define MAX_COMMANDS			256

#define NUM_DIRECTIONS			4
#define NUM_ENTITY_IMAGE		2
#define NUM_ENTITY_FRAME		2

#define MAX_HI_SCORE			50000	//99999
#define DEF_HI_SCORE			5000
//#define MAX_BOOSTERX			100
#define NUMBER_LIVES			4

#define TOP_SIDE_Y				0
#define LFT_SIDE_X				0

#define TEXT_X					SCREEN_TILE_LEFT + 24
#define DATA_X					SCREEN_TILE_LEFT + 28

// Generic Y heights
#define TEXT0_Y					0
#define TEXT1_Y					4
#define TEXT2_Y					9
#define TEXT3_Y					13
#define TEXT4_Y					18
#define BOTT_TEXT_Y				21

// Type1 cursor
#define TYPE1_TEXT_X			SCREEN_TILE_LEFT + 7
#define TYPE1_TEXT_Y			18
#define TYPE1_OPT1_X			TYPE1_TEXT_X + 0
#define TYPE1_OPT2_X			TYPE1_TEXT_X + 11

#define SOUND_SCREEN_DELAY		30

#endif//_GLOBAL_MANAGER_H_