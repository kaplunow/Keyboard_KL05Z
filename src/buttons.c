/*******************************************************************************
 *  This is source file for tact switch matrix usage functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file buttons.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for DAC functions
 * @ver 0.1
 *******************************************************************************/

/* Private includes ----------------------------------------------------------*/
#include "buttons.h"

/* Private defines -----------------------------------------------------------*/
#define COL1 		6
#define COL2		5
#define COL3		8
#define COL4		9

#define ROW1	10	
#define ROW2	11
#define ROW3	12
#define ROW4	7

/* Private variables ----------------------------------------------------------*/
static uint8_t row_flag = 0;
static uint8_t button = 0;				

/* Private prototypes ---------------------------------------------------------*/
static void column_Init(void);
static void row_Init(void);
static uint8_t is_button_pressed(void);


/**
 * @brief ISR for tact switch matrix. Setting corresponding flag which row caused int.
 */
void PORTA_IRQHandler() {
	if(PORTA->ISFR & (1 << ROW1)) {																		/* Check which row caused intterupt  */
		PORTA->PCR[ROW1] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 4;																										
	}
	else if(PORTA->ISFR & (1 << ROW2)) {												  		
		PORTA->PCR[ROW2] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 3;
	}
	else if(PORTA->ISFR & (1 << ROW3)) {												  		
		PORTA->PCR[ROW3] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 2;
	}
	else if(PORTA->ISFR & (1 << ROW4)) {												  		
		PORTA->PCR[ROW4] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 1;
	}
}
/**
 * @brief Check wich button has been pressed.
 *
 * @return Number of button pressed.
 */
uint8_t get_button() {
	
	if (row_flag == 0) 
		return button;
	
	else {
				
		FPTA->PSOR |= (1 << COL2) | (1 << COL3) | (1 << COL4);					/* Clear COL1, Set others*/
		DELAY(5)																												/* Wait for pin state change and debouncing */
		if( is_button_pressed() )															        	/* Check if COL1 */
			button = 4 + (4*(row_flag-1));
		else {
			FPTA->PSOR |= (1 << COL1);					  				/* Set COL1*/
			FPTA->PCOR |= (1 << COL2);										/* Clear COL2 */
			DELAY(5)																	    /* Wait for pin state change and debouncing */
			if( is_button_pressed() )											/* Check if COL2 */
						button = 3 + (4*(row_flag-1));
			else {
				FPTA->PSOR |= (1 << COL2);					  		/* Set COL2*/
				FPTA->PCOR |= (1 << COL3);								/* Clear COL3 */
				DELAY(5)																	/* Wait for pin state change and debouncing */
				if( is_button_pressed() )									/* Check if COL3 */
					button = 2 + (4*(row_flag-1));
				else {
					FPTA->PSOR |= (1 << COL3);					  		/* Set COL3*/
					FPTA->PCOR |= (1 << COL4);								/* Clear COL4 */
					DELAY(5)																	/* Wait for pin state change and debouncing */
					if( is_button_pressed() )									/* Check if COL4 */
						button = 1 + (4*(row_flag-1));
				}
			}
		}
		
		FPTA->PCOR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);		/* Clear all columns */
		row_flag = 0;																														/* Clear interrupt row flag*/
		return button;
	
	}
}
/**
 * @brief Conditions ckeck if button has been pressed.
 *
 * @return True/false (0/1).
 */
uint8_t is_button_pressed() {
	return ( (FPTA->PDIR & (1<<ROW1)) == 0 ||
					 (FPTA->PDIR & (1<<ROW2)) == 0 ||
					 (FPTA->PDIR & (1<<ROW3)) == 0 ||
					 (FPTA->PDIR & (1<<ROW4)) == 0
					)? 1 : 0;				
}
/**
 * @brief Row initilization
 */
void row_Init() {
	
	/* Enable clock for port A */
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; 		

	/* Set pins as gpio */
	PORTA->PCR[ROW1] |= PORT_PCR_MUX(1);      	
	PORTA->PCR[ROW2] |= PORT_PCR_MUX(1);      	
	PORTA->PCR[ROW3] |= PORT_PCR_MUX(1);   
	PORTA->PCR[ROW4] |= PORT_PCR_MUX(1);	

	/* Activate pull up and interrupt (on falling edge) */
	PORTA->PCR[ROW1] |=  PORT_PCR_PE_MASK |	PORT_PCR_PS_MASK;
	PORTA->PCR[ROW1] |=  PORT_PCR_IRQC(10);														
	PORTA->PCR[ROW2] |=  PORT_PCR_PE_MASK |	PORT_PCR_PS_MASK;
	PORTA->PCR[ROW2] |=  PORT_PCR_IRQC(10);														
	PORTA->PCR[ROW3] |=  PORT_PCR_PE_MASK |	PORT_PCR_PS_MASK;
	PORTA->PCR[ROW3] |=  PORT_PCR_IRQC(10);														
	PORTA->PCR[ROW4] |=  PORT_PCR_PE_MASK |	PORT_PCR_PS_MASK;
	PORTA->PCR[ROW4] |=  PORT_PCR_IRQC(10);											

	/* ARM's Nested Vector Interrupt Controller configuration */
	NVIC_ClearPendingIRQ(PORTA_IRQn);				/* Clear NVIC any pending interrupts on PORTC_A */
	NVIC_EnableIRQ(PORTA_IRQn);							/* Enable NVIC interrupts source for PORTC_A module */
	
	NVIC_SetPriority (PORTA_IRQn, 3);			  /* Set POR_B interrupt priority level  */ 
	
}
/**
 * @brief Buttons initilization.
 */
void buttons_Init() {
	column_Init();
	row_Init();
}
/**
 * @brief Column initilization.
 */
void column_Init() {
	
	/* Clock enable to port A */
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	/* Set pins as gpio */ 
	PORTA->PCR[COL1] = PORT_PCR_MUX(1);
	PORTA->PCR[COL2] = PORT_PCR_MUX(1);
	PORTA->PCR[COL3] = PORT_PCR_MUX(1);
	PORTA->PCR[COL4] = PORT_PCR_MUX(1);
	
	/* Set pins as output */
	FPTA->PDDR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);
	
	/* Clear output */
	FPTA->PCOR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);
	
}
/**
 * @brief Set new value to button.
 *
 * @param New value.
 */
void set_button(uint8_t new_button) {
	button = new_button;
}
