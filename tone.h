#ifndef TONE_H
#define TONE_H

#include "MKL05Z4.h"


enum e_tone {
	C4 = 255,				  	/* 262 Hz */
	CS4 = 272,					/* 277 Hz */
	D4 = 289,				  	/* 294 Hz */
	DS4 = 306,					/* 311 Hz	*/
	E4 = 324,				  	/* 329 Hz */
	F4 = 345,				  	/* 349 Hz */
	FS4 = 366,		  		/* 370 Hz */
	G4 = 388,				  	/* 392 Hz */
	GS4 = 411,					/* 415 Hz */
	A4 = 440,		  	  	/* 440 Hz */
	AS4 = 466,					/* 466 Hz */
	B4 = 494,				  	/* 494 Hz */
	C5 = 523,				    /* 523 Hz */
	CS5 = 554,					/* 554 Hz */
	D5 = 597,				  	/* 587 Hz */
	DS5 = 632,					/* 622 HZ */
	E5 = 672,				  	/* 659 Hz */
	F5 = 713,				    /* 698 Hz */
	FS5 = 755,					/* 740 Hz */
	G5 = 815,				  	/* 784 Hz */
	GS5 = 871,					/* 831 Hz */
	A5 = 930,				  	/* 880 Hz */
	AS5 = 978,					/* 932 Hz */
	B5 = 1063,			  	/* 988 Hz */
	C6 = 1130,					/* 1047 Hz */
	E_NULL = 0
};


enum e_tone get_tone(uint8_t button);
const char* tone2str(enum e_tone tone);
enum e_tone str2tone(const char* str);
	
#endif  /* TONE_H */
