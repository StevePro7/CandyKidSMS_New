#ifndef _SCORE_OBJECT_H_
#define _SCORE_OBJECT_H_

typedef struct tag_struct_score_object
{
	unsigned long score;
	unsigned char lives;
	unsigned char level;
	unsigned char bonus;
	unsigned char candy;
	unsigned char total;
	unsigned char boost;
	unsigned char delay;

} struct_score_object;

#endif//_SCORE_OBJECT_H_