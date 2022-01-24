/*******************************************************************************
 *  This is source file for digital analog converter functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file dac.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for DAC functions
 * @ver 0.1
 *******************************************************************************/
 
 /* Private includes ----------------------------------------------------------*/
#include "dac.h"
#include "pit.h"

/**
 * @brief DAC Initialize 
 */
void DAC_Init(void) {
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;          /* Clock enable */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					/* Port B enable */
	DAC0->C0 |= (DAC_C0_DACEN_MASK | DAC_C0_DACTRGSEL_MASK);		/* DAC enable and set software trigger */
}
/**
 * @brief Load value and trigger DAC
 *
 * @param load 12b value to write 
 *
 * @return Error code
 */
uint8_t DAC_Load_Trig(uint16_t load) {
	uint8_t load_temp;
	if(load>0xFFF)	return (1);					/* Check if arg is not over 12b */
	load_temp=load&0x0FF;
	DAC0->DAT->DATL = load_temp;				/* Load lower byte */
	load_temp=(load>>8);
	DAC0->DAT->DATH = load_temp;				/* Load upper byte */
	DAC0->C0 |= DAC_C0_DACSWTRG_MASK;		/* Software trigger  */
	return (0);
}
/**
 * @brief Play tone for time in ms on DAC (sin wave)
 *
 * @param tone Enum e_tone type value.
 * @param time_ms Time in ms.
 */
void DAC_Tone(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[32] = {2048,2447,2830,3184,3481,3747,3932,4055,4095,4055,3932,3747,3481,3184,2830,2447,2048,1648,1269,921,614,348,163,41,0,41,163,348,614,921,1269,1648};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)																	/* freq = 0 - pause */
		return;
	}
	
	float delay = 1000000 / (freq * samples);					/* Calculating delay between samples */
	
	float time = time_ms * freq / 1000.0f;						/* Calculating how many sin waves to play */
	if (time < 1) time = 1;
	
	for (int i = 0; i < (int)time; i++) {
		for(int i = 0; i < samples ; i++) {
			DAC_Load_Trig(values[i]);
			delay_us((uint32_t)delay);
		}
	}
	DELAY(80)																					/* Short delay between notes */
}
