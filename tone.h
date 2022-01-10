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
	A4 = 443,		  	  	/* 440 Hz */
	AS4 = 470,					/* 466 Hz */
	B4 = 497,				  	/* 494 Hz */
	C5 = 528,				    /* 523 Hz */
	CS5 = 564,					/* 554 Hz */
	D5 = 597,				  	/* 587 Hz */
	DS5 = 632,					/* 622 HZ */
	E5 = 672,				  	/* 659 Hz */
	F5 = 713,				    /* 698 Hz */
	FS5 = 755,					/* 740 Hz */
	G5 = 804,				  	/* 784 Hz */
	GS5 = 851,					/* 831 Hz */
	A5 = 910,				  	/* 880 Hz */
	AS5 = 953,					/* 932 Hz */
	B5 = 1028,			  	/* 988 Hz */
	C6 = 1090,					/* 1047 Hz */
	E_NULL = 0
};


enum e_tone get_tone(uint8_t button);
const char* tone2str(enum e_tone tone);
enum e_tone str2tone(const char* str);
	
#endif  /* TONE_H */
