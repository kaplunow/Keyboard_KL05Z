#ifndef TONE_H
#define TONE_H

#include "MKL05Z4.h"


enum e_tone {
	C4 = 4894,					/* 262 Hz */
	CS4 = 4629,					/* 277 Hz */
	D4 = 4361,					/* 294 Hz */
	DS4 = 4123,					/* 311 Hz	*/
	E4 = 3885,					/* 329 Hz */
	F4 = 3674,					/* 349 Hz */
	FS4 = 3465,		  		/* 370 Hz */
	G4 = 3270,					/* 392 Hz */
	GS4 = 3090,					/* 415 Hz */
	A4 = 2914,		  		/* 440 Hz */
	AS4 = 2751,					/* 466 Hz */
	B4 = 2595,					/* 494 Hz */
	C5 = 2452,				  /* 523 Hz */
	CS5 = 2314,					/* 554 Hz */
	D5 = 2184,					/* 587 Hz */
	DS5 = 2061,					/* 622 HZ */
	E5 = 1956,					/* 659 Hz */
	F5 = 1837,					/* 698 Hz */
	FS5 = 1733,					/* 740 Hz */
	G5 = 1635,					/* 784 Hz */
	GS5 = 1543,					/* 831 Hz */
	A5 = 1457,					/* 880 Hz */
	AS5 = 1376,					/* 932 Hz */
	B5 = 1298,					/* 988 Hz */
	C6 = 1225,					/* 1047 Hz */
	NULL = 0
};


enum e_tone get_tone(uint8_t button);
const char* tone2str(enum e_tone tone);

#endif  /* TONE_H */
