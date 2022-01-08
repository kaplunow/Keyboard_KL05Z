#include "uart.h"

#define CLK_DIS 					0x00
#define MCGFLLCLK 				0x01				/* MCGFLLCLK=41943040Hz (CLOCK_SETUP=0) */
#define OSCERCLK					0x02
#define MCGIRCLK					0x03

#define UART0_TX 					1
#define UART0_RX 					2


void UART_Init(void) {
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;										/* Enable clock to PIT module */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;										/* Enable clock to PORTB */
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);					/* Clock source */
	PORTB->PCR[UART0_TX] = PORT_PCR_MUX(2);								/* Pin mux */
	PORTB->PCR[UART0_RX] = PORT_PCR_MUX(2);								
	
	UART0->BDH = 0;
	UART0->BDL =91;																				/* Baud rate = 28800*/
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(15);												/* Oversampling ratio = 15*/
	UART0->C5 |= UART0_C5_BOTHEDGE_MASK;									/* Both edge sampling */
	UART0->C2 |= UART0_C2_RIE_MASK;												/* Interrupts enable */
	UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);		/* Transmitter and receiver enable*/
	NVIC_EnableIRQ(UART0_IRQn);														/* NVIC UART0 interruprs enable */
	NVIC_ClearPendingIRQ(UART0_IRQn);
}
