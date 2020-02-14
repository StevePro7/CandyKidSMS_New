#ifndef _SCORE_OBJECT_H_
#define _SCORE_OBJECT_H_

typedef struct tag_struct_score_object
{
	unsigned long my_score;
	unsigned char lives;
	unsigned char boost;
	unsigned char delay;
	unsigned char bonus;
	unsigned char candy;
	unsigned char total;

} struct_score_object;

#endif//_SCORE_OBJECT_H_