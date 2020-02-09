#include "..\banks\bank4.h"

unsigned const char foo[] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x15, 0x067, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
};

// Board Manager.
const unsigned char board_object_posnX[] =
{
	0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0,
	
};
const unsigned char board_object_posnY[] =
{
	0xF0, 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0,
}; 

// Order:									  Pro,  Adi,  Suz,  Kid.
const unsigned char board_object_homeX[] = { 0x0A, 0x03, 0x0A, 0x03 };
const unsigned char board_object_homeY[] = { 0x0A, 0x0A, 0x03, 0x03 };
const unsigned char board_object_homeZ[] = { 0x96, 0x8F, 0x34, 0x2D };

const unsigned char board_object_exitX	= 0x06;
const unsigned char board_object_exitY	= 0x10;
const unsigned char board_object_top	= 0x00;
const unsigned char board_object_bottom = 0x16;
const unsigned char board_object_left	= 0x02;
const unsigned char board_object_middle = 0x18;
const unsigned char board_object_right	= 0x1E;


// Level Manager.
const unsigned char *level_object_AAdata[] =
{
	level0101_txt,
	level0102_txt,
};

const unsigned char level_object_AAsize[] =
{
	level0101_txt_size,
	level0102_txt_size,
};

const unsigned char level_object_AAbank[] =
{
	level0101_txt_bank,
	level0102_txt_bank,
};