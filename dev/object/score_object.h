#ifndef _SCORE_OBJECT_H_
#define _SCORE_OBJECT_H_

typedef struct tag_struct_score_object
{
	unsigned long score;
	unsigned char values[ 5 ];
	unsigned char bonus;
	unsigned char candy;
	//unsigned char total;		// TODO delete as don't believe we need as can calc complete vs. perfect!
	unsigned char delay;		// Boost delay
	unsigned char timer;		// Boost timer

} struct_score_object;

#endif//_SCORE_OBJECT_H_