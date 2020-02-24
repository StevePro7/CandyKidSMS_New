#ifndef _SCORE_MANAGER_H_
#define _SCORE_MANAGER_H_

#include "..\object\score_object.h"

// Global variable.
extern struct_score_object global_score_object;

void engine_score_manager_init();
void engine_score_manager_load();

unsigned char engine_score_manager_get_total();

void engine_score_manager_update_bonus( unsigned char bonus );
void engine_score_manager_update_candy();
void engine_score_manager_update_oneup();
void engine_score_manager_update_lives( signed char value );

void engine_score_manager_draw_all();
void engine_score_manager_draw_text();

#endif//_SCORE_MANAGER_H_
