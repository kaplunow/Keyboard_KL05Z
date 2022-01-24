/*******************************************************************************
 *  This is header file for digital analog converter functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file dac.h
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing declarations for DAC functions
 * @ver 0.1
 *******************************************************************************/
 
#ifndef DAC_H
#define DAC_H

#include "frdm_bsp.h"
#include "tone.h"


void DAC_Init(void);
uint8_t DAC_Load_Trig(uint16_t load);
void DAC_Tone(enum e_tone tone, uint32_t time_ms);
void DAC_Tone_tri(enum e_tone tone, uint32_t time_ms);
void DAC_Tone_sawtooth(enum e_tone tone, uint32_t time_ms);
void DAC_Tone_sq(enum e_tone tone, uint32_t time_ms);
void DAC_Tone_semisine(enum e_tone tone, uint32_t time_ms);


#endif /* DAC_H */
