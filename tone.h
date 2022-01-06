#ifndef TONE_H
#define TONE_H

#include "MKL05Z4.h"


enum e_tone {
	C4 = 262,				  	/* 262 Hz */
	CS4 = 277,					/* 277 Hz */
	D4 = 294,				  	/* 294 Hz */
	DS4 = 311,					/* 311 Hz	*/
	E4 = 329,				  	/* 329 Hz */
	F4 = 349,				  	/* 349 Hz */
	FS4 = 370,		  		/* 370 Hz */
	G4 = 392,				  	/* 392 Hz */
	GS4 = 415,					/* 415 Hz */
	A4 = 440,		  	  	/* 440 Hz */
	AS4 = 466,					/* 466 Hz */
	B4 = 494,				  	/* 494 Hz */
	C5 = 523,				    /* 523 Hz */
	CS5 = 554,					/* 554 Hz */
	D5 = 587,				  	/* 587 Hz */
	DS5 = 622,					/* 622 HZ */
	E5 = 659,				  	/* 659 Hz */
	F5 = 698,				    /* 698 Hz */
	FS5 = 740,					/* 740 Hz */
	G5 = 784,				  	/* 784 Hz */
	GS5 = 831,					/* 831 Hz */
	A5 = 880,				  	/* 880 Hz */
	AS5 = 923,					/* 932 Hz */
	B5 = 988,				   	/* 988 Hz */
	C6 = 1047,					/* 1047 Hz */
	NULL = 0
};


enum e_tone get_tone(uint8_t button);
const char* tone2str(enum e_tone tone);

#endif  /* TONE_H */
