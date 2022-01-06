#include "pit.h"

void PIT_Init(){ 
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; 					/* Enable clock to PIT module */ 
	PIT->MCR &= ~PIT_MCR_MDIS_MASK; 						/* Enable module */
}

void delay_us(uint32_t us) {
	uint32_t val = us * 20;
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(0xFFFF);		/* Load max value */
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;			/* Timer disable */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;			/* Timer enable */
	while (PIT->CHANNEL[0].CVAL > 0xFFFF - val);
}
