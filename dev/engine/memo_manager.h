#ifndef _MEMO_MANAGER_H_
#define _MEMO_MANAGER_H_

void engine_memo_manager_clear();
void engine_memo_manager_draw( unsigned char topIndex, unsigned char botIndex );
void engine_memo_manager_pass( unsigned char perfect );
void engine_memo_manager_bonus( unsigned char perfect );
void engine_memo_manager_option();

#endif//_MEMO_MANAGER_H_