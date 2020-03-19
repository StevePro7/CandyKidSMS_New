#ifndef _CURSOR_MANAGER_H_
#define _CURSOR_MANAGER_H_

// Tiles.
void engine_cursor_manager_init();
void engine_cursor_manager_update1( unsigned char index );
void engine_cursor_manager_update2( unsigned char index );
void engine_cursor_manager_draw1( unsigned char index );
void engine_cursor_manager_draw2( unsigned char index );
void engine_cursor_manager_draw_title1();
void engine_cursor_manager_draw_title2();
void engine_cursor_manager_draw_option1( unsigned char index, unsigned char x, unsigned char y );
void engine_cursor_manager_draw_option2( unsigned char index, unsigned char actor );
void engine_cursor_manager_draw_select1( unsigned char index, unsigned char x, unsigned char y );
void engine_cursor_manager_draw_select2( unsigned char index, unsigned char actor );
unsigned char engine_cursor_manager_get_cursor( unsigned char index );

#endif//_CURSOR_MANAGER_H_