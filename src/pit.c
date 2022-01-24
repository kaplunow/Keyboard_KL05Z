/*******************************************************************************
 *  This is source file for PIT module functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file pit.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for PIT functions
 * @ver 0.1
 *******************************************************************************/
 
/* Private includes ---------------------------------------------------------*/
#include "pit.h"


/**
 * @brief PIT initalize.
 */
void PIT_Init(){ 
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; 					/* Enable clock to PIT module */ 
	PIT->MCR &= ~PIT_MCR_MDIS_MASK; 						/* Enable module */
}
/**
 * @brief Delay timer which base is 1us
 *
 * @param Time in microseconds.
 */
void delay_us(uint32_t us) {
	uint32_t val = us * 19;
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(0xFFFF);		/* Load max value - timer is downcounting*/
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;			/* Timer disable */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;			/* Timer enable */
	while (PIT->CHANNEL[0].CVAL > 0xFFFF - val);
}
