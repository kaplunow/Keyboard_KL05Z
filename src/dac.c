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

void DAC_Tone_tri(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[32] = {1,256,512,768,1024,1280,1536,1792,2048,2303,2559,2815,3071,3327,3583,3839,4095,3839,3583,3327,3071,2815,2559,2303,2048,1792,1536,1280,1024,768,512,256};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)
		return;
	}
	
	float delay = 1000000 / (freq * samples);
	
	float time = time_ms * freq / 1000.0f;
	if (time < 1) time = 1;
	
	for (int i = 0; i < (int)time; i++) {
		for(int i = 0; i < samples ; i++) {
			DAC_Load_Trig(values[i]);
			delay_us((uint32_t)delay);
		}
	}
	DELAY(100)
}

void DAC_Tone_sawtooth(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[32] = {128,256,384,512,640,768,895,1024,1152,1280,1408,1536,1664,1792,1920,2048,2175,2303,2431,2559,2687,2815,2943,3071,3200,3327,3455,3583,3711,3839,3967,4095};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)
		return;
	}
	
	float delay = 1000000 / (freq * samples);
	
	float time = time_ms * freq / 1000.0f;
	if (time < 1) time = 1;
	
	for (int i = 0; i < (int)time; i++) {
		for(int i = 0; i < samples ; i++) {
			DAC_Load_Trig(values[i]);
			delay_us((uint32_t)delay);
		}
	}
	DELAY(100)
}

void DAC_Tone_sq(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)
		return;
	}
	
	float delay = 1000000 / (freq * samples);
	
	float time = time_ms * freq / 1000.0f;
	if (time < 1) time = 1;
	
	for (int i = 0; i < (int)time; i++) {
		for(int i = 0; i < samples ; i++) {
			DAC_Load_Trig(values[i]);
			delay_us((uint32_t)delay);
		}
	}
	DELAY(100)
}

void DAC_Tone_semisine(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[32] = {0,798,1567,2275,2895,3404,3783,4016,4095,4016,3783,3404,2895,2275,1567,798,0,798,1567,2275,2895,3404,3783,4016,4095,4016,3783,3404,2895,2275,1567,789};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)
		return;
	}
	
	float delay = 1000000 / (freq * samples);
	
	float time = time_ms * freq / 1000.0f;
	if (time < 1) time = 1;
	
	for (int i = 0; i < (int)time; i++) {
		for(int i = 0; i < samples ; i++) {
			DAC_Load_Trig(values[i]);
			delay_us((uint32_t)delay);
		}
	}
	DELAY(100)
}
