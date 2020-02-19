#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

void engine_board_manager_init();
void engine_board_manager_draw_full();
void engine_board_manager_draw_exit();
void engine_board_manager_main_full();
void engine_board_manager_main_exit();
void engine_board_manager_side_tile();
//unsigned char engine_board_manager_near_exit( unsigned char tileX, unsigned char tileY, unsigned char direction );

//// TODO - delete!!
void engine_board_manager_debugger();

#endif//_BOARD_MANAGER_H_
