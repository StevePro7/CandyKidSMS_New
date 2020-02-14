#ifndef _SCORE_MANAGER_H_
#define _SCORE_MANAGER_H_

#include "..\object\score_object.h"

// Global variable.
extern struct_score_object global_score_object;

void engine_score_manager_init();
void engine_score_manager_load();
void engine_score_manager_update();

#endif//_SCORE_MANAGER_H_