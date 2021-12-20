#include "buttons.h"
#include "frdm_bsp.h"

#define COL1 		6
#define COL2		7
#define COL3		8
#define COL4		9

#define ROW1	10	
#define ROW2	11
#define ROW3	12
#define ROW4	0

static uint8_t row_flag = 0;
static uint8_t button = 0;

static void column_Init(void);
static void row_Init(void);
static uint8_t is_button_pressed(void);

void PORTA_IRQHandler() {
	if(PORTA->ISFR & (1 << ROW1)) {																		/* Check which row caused intterupt  */
		PORTA->PCR[ROW1] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 3;
	}
	else if(PORTA->ISFR & (1 << ROW2)) {												  		/* Check which row caused intterupt  */
		PORTA->PCR[ROW2] |= PORT_PCR_ISF_MASK;													/* Interrupt mask clear*/
		row_flag = 2;
	}
}

uint8_t get_button() {
	
	if (row_flag == 0) 
		return button;
	
	else {
		
		FPTA->PSOR |= (1 << COL2) | (1 << COL3) | (1 << COL4);					/* Clear COL1, Set others*/
		DELAY(5)																												/* Wait for pin state change and debouncing */
		if( is_button_pressed() )																/* Check if COL1 */
			button = 4 + (4*row_flag);
		else {
			FPTA->PSOR |= (1 << COL1);					  				/* Set COL1*/
			FPTA->PCOR |= (1 << COL2);										/* Clear COL2 */
			DELAY(5)																	    /* Wait for pin state change and debouncing */
			if( is_button_pressed() )											/* Check if COL2 */
						button = 3 + (4*row_flag);
			else {
				FPTA->PSOR |= (1 << COL2);					  		/* Set COL2*/
				FPTA->PCOR |= (1 << COL3);								/* Clear COL3 */
				DELAY(5)																	/* Wait for pin state change and debouncing */
				if( is_button_pressed() )					/* Check if COL3 */
					button = 2 + (4*row_flag);
				else {
					FPTA->PSOR |= (1 << COL3);					  		/* Set COL3*/
					FPTA->PCOR |= (1 << COL4);								/* Clear COL4 */
					DELAY(5)																	/* Wait for pin state change and debouncing */
					if( is_button_pressed() )					/* Check if COL4 */
						button = 1 + (4*row_flag);
				}
			}
		}
		
		FPTA->PCOR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);		/* Clear all columns */
		row_flag = 0;																														/* Clear interrupt flag*/
		return button;
	
	}
}

uint8_t is_button_pressed() {
	return ( (FPTA->PDIR & (1<<ROW1)) == 0 ||
					 (FPTA->PDIR & (1<<ROW2)) == 0	
					)? 1 : 0;				
}

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
	//PORTA->PCR[ROW3] |=  PORT_PCR_IRQC(10);														
	PORTA->PCR[ROW4] |=  PORT_PCR_PE_MASK |	PORT_PCR_PS_MASK;
	//PORTA->PCR[ROW4] |=  PORT_PCR_IRQC(10);														

	/* ARM's Nested Vector Interrupt Controller configuration */
	NVIC_ClearPendingIRQ(PORTA_IRQn);				/* Clear NVIC any pending interrupts on PORTC_B */
	NVIC_EnableIRQ(PORTA_IRQn);							/* Enable NVIC interrupts source for PORTC_B module */
	
	NVIC_SetPriority (PORTA_IRQn, 3);			  /* Set POR_B interrupt priority level  */ 
	
}

void buttons_Init() {
	column_Init();
	row_Init();
}

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
