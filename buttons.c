#include "buttons.h"

#define COL1 		6
#define COL2		7
#define COL3		8
#define COL4		9

#define ROW1	10	
#define ROW2	11
#define ROW3	12
#define ROW4	0

static uint32_t button = 0;

static void column_Init(void);
static void row_Init(void);

void PORTA_IRQHandler() {
	button = 2;
	if(PORTA->ISFR & (1 << ROW1)) {																								/* Check which row caused intterupt  */
		button = 3;
		PORTA->PCR[ROW1] |= PORT_PCR_ISF_MASK;
		FPTA->PSOR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);				
		
		FPTA->PCOR |= 1 << COL1;
		button = FPTA->PDIR;
		if((FPTA->PDIR & (1<<ROW1)) == 0)
			button = 1;
	}
	FPTA->PCOR |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);
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
	//PORTA->PCR[ROW2] |=  PORT_PCR_IRQC(10);														
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

uint32_t get_button() { return button; }
