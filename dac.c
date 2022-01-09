#include "dac.h"
#include "pit.h"
#include "frdm_bsp.h"

void DAC_Init(void) {
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;          /* Clock enable */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					/* Port B enable */
	DAC0->C0 |= (DAC_C0_DACEN_MASK | DAC_C0_DACTRGSEL_MASK);		/* DAC enable and set software trigger */
}

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

void DAC_Tone(enum e_tone tone, uint32_t time_ms) {
	
	uint16_t values[16] = {2048,3072,3502,3810,4095,3810,3502,3072,2048,1024,594,287,0,287,594,1024};
	float samples = sizeof(values)/sizeof(values[0]);
	
	float freq = tone;
	if (freq == 0) {
		DELAY(time_ms)
		return;
	}
	float delay = 1000000.0f / (freq * samples);
	
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
