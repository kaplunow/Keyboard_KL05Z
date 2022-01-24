/*******************************************************************************
 *  This is source file for utility helper functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file utils.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for utility functions
 * @ver 0.1
 *******************************************************************************/

/* Private includes ----------------------------------------------------------*/
#include "utils.h"
#include <stdio.h>


/**
 * @brief Read button, play corresponding tone, and display it on LCD1602
 */
void button_play() {
	uint8_t button = get_button();
	enum e_tone tone = get_tone(button);
	if (tone) {
		const char* tone_str = tone2str(tone);
		char str[20];
		sprintf(str, "Tone=%s", tone_str);
		LCD1602_ClearAll();
		LCD1602_Print(str);
		DAC_Tone(tone, 200);
		
		set_button(0);
	}
}
