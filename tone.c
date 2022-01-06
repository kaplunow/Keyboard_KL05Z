#include "tone.h"

enum e_tone get_tone(uint8_t button) {
		switch (button) {
		case 1: return C4;	
		case 2: return D4;
		case 3: return E4;
		case 4: return F4;
		case 5: return G4;
		case 6: return A4;
		case 7: return AS4;
		case 8: return B4;
		case 9: return C5;
		case 10: return D5;
		case 11: return E5;
		case 12: return F5;
		case 13: return G5;
		case 14: return A5;
		case 15: return B5;
		case 16: return C6;
		default: return NULL;
	}		
}

const char* tone2str(enum e_tone tone) {
	switch (tone) {
		case C4:  return "C4";
		case CS4: return "CS4";
		case D4:  return "D4";
		case DS4: return "DS4";
		case E4:  return "E4";
		case F4:  return "F4";
		case FS4: return "FS4";
		case G4:  return "G4";
		case GS4: return "GS4";
		case A4:  return "A4";
		case AS4: return "AS4";
		case B4:  return "B4";
		case C5:  return "C5";
		case CS5: return "CS4";
		case D5:  return "D5";
		case DS5: return "DS5";
		case E5:  return "E5";
		case F5:  return "F5";
		case FS5: return "FS5";
		case G5:  return "G5";
		case GS5: return "GS5";
		case A5:  return "A5";
		case AS5: return "AS5";
		case B5:  return "B5";
		case C6:  return "C6";
		case NULL: return "0";
	}
	return "0";
}
