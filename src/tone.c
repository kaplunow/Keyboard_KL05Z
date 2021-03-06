/*******************************************************************************
 *  This is source file for tones processing functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file tone.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for tones processing functions
 * @ver 0.1
 *******************************************************************************/
 
/* Private includes ---------------------------------------------------------*/
#include "tone.h"
#include <string.h>

/**
 * @brief Conversion number of button pressed to coressponding tone
 *
 * @param Number of button.
 * @return Enum e_tone type of tone.
 */
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
		default: return E_NULL;
	}		
}
/**
 * @brief Conversion enum type e_tone to string(const char* ).
 *
 * @param Enum e_tone type.
 * @return String.
 */
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
		case CS5: return "CS5";
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
		case E_NULL: return "NULL";
	}
	return "0";
}
/**
 * @brief Conversion string(const char* ) to enum type e_tone.
 *
 * @param String.
 * @return Enum e_tone type.
 */
enum e_tone str2tone(const char* str) {
	
	char temp[3];
	strncpy(temp, str, 2);
	
	if (temp[1] == 'S')
		strncpy(temp, str, 3);	
	
	if (strcmp(temp, "C4") == 0) 			  return C4;
	else if (strcmp(temp, "CS4") == 0)  return CS4;
	else if (strcmp(temp, "D4") == 0)   return D4;
	else if (strcmp(temp, "DS4") == 0)  return DS4;
	else if (strcmp(temp, "E4") == 0)   return E4;
	else if (strcmp(temp, "F4") == 0)   return F4;
	else if (strcmp(temp, "FS4") == 0)  return FS4;
	else if (strcmp(temp, "G4") == 0)   return G4;
	else if (strcmp(temp, "GS4") == 0)  return GS4;
	else if (strcmp(temp, "A4") == 0)   return A4;
	else if (strcmp(temp, "AS4") == 0)  return AS4;
	else if (strcmp(temp, "B4") == 0)   return B4;
	else if (strcmp(temp, "C5") == 0)   return C5;
	else if (strcmp(temp, "CS5") == 0)  return CS5;
	else if (strcmp(temp, "D5") == 0)   return D5;
	else if (strcmp(temp, "DS5") == 0)  return DS5;
	else if (strcmp(temp, "E5") == 0)   return E5;
	else if (strcmp(temp, "F5") == 0)   return F5;
	else if (strcmp(temp, "FS5") == 0)  return FS5;
	else if (strcmp(temp, "G5") == 0)   return G5;
	else if (strcmp(temp, "GS5") == 0)  return GS5;
	else if (strcmp(temp, "A5") == 0)   return A5;
	else if (strcmp(temp, "AS5") == 0)  return AS4;
	else if (strcmp(temp, "B5") == 0)   return B5;
	else if (strcmp(temp, "C6") == 0)   return C6;
	else 														    return E_NULL;
}
