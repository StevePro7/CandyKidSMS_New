#ifndef _CURSOR_MANAGER_H_
#define _CURSOR_MANAGER_H_

// Tiles.
void engine_cursor_manager_init();
void engine_cursor_manager_update2( unsigned char index );
void engine_cursor_manager_update1( unsigned char index );
void engine_cursor_manager_draw1( unsigned char index );
void engine_cursor_manager_draw2( unsigned char index );
void engine_cursor_manager_draw_titles();
void engine_cursor_manager_draw_option( unsigned char index, unsigned char x, unsigned char y );
void engine_cursor_manager_draw_option2( unsigned char index, unsigned char actor );

#endif//_CURSOR_MANAGER_H_