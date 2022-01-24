/*******************************************************************************
 *  This is source file for UART module functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file uart.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing definitions for UART functions
 * @ver 0.1
 *******************************************************************************/
 
 /* Private includes ---------------------------------------------------------*/
#include "uart.h"
#include "dac.h"
#include "frdm_bsp.h"
#include <string.h>
#include <stdlib.h>

/* Private defines ------------------------------------------------------------*/
#define CLK_DIS 					0x00
#define MCGFLLCLK 				0x01				/* MCGFLLCLK=41943040Hz (CLOCK_SETUP=0) */
#define OSCERCLK					0x02
#define MCGIRCLK					0x03

#define UART0_TX 					1
#define UART0_RX 					2

/* Private variables ---------------------------------------------------------*/
char rx_buf[16];
uint8_t rx_buf_pos=0;
uint8_t rx_FULL=0;

/* Private prototypes ---------------------------------------------------------*/
void UART0_IRQHandler(void);
static void play_melody(void);

/**
 * @brief ISR for UART MODULE. Save data from (e.g from PC) to buffer.
 */
void UART0_IRQHandler() {
	if(UART0->S1 & UART0_S1_RDRF_MASK) {				/* If data recived */
		char temp = UART0->D;											/* Read the buffer and clear RDRF flag*/
		if(!rx_FULL) {
			if(temp!=LF) {													/* Check for '\n' */
				rx_buf[rx_buf_pos] = temp;	
				rx_buf_pos++;
			}
			else 
				rx_FULL=1;														/* Rise flag */
		}
	}
}
/**
 * @brief UART Initialize
 */
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
/**
 * @brief DAC controlling by UART module. 
 */
void UART_play() {
	
	static int pos = 0;
	char tones[30][3];
  char lengths[30][4];
	
	if(rx_FULL) {		

		if (strcmp(rx_buf, "play") == 0) {
			if (pos == 0) 																 /* Play melody from memory if bufffer is empty */
				play_melody();
			else {																				 /* Play melody from temp buffer if it isn't empty */
				for (int i = 0; i < pos; i++)
					DAC_Tone(str2tone(tones[i]), atoi(lengths[i]));
			}
		}
		
		else if (strcmp(rx_buf, "reset") == 0)
			pos = 0;
		
		else {																						/* Add note to the buffers (notes and lenghts)*/
			const char* token = strtok(rx_buf, " \n");				
			strcpy(tones[pos], token);
			token = strtok(NULL, " ");
			strcpy(lengths[pos], token);	
			pos++;
		}

		rx_buf_pos=0;
		memset(rx_buf, 0, sizeof rx_buf);
		rx_FULL=0;
	}
}
/**
 * @brief Play melody from memory buffer.
 */
void play_melody() {
	#define notes 100
  #define MELODY2

#if defined(MELODY1)			/* Fur elise */
	char tones[notes][3] = {
		"E5", "DS5", "E5", "DS5", "E5", "B4", "D5", "C5", "A4", "C4",
		"E4", "A4", "B4", "E4", "GS4", "B4", "C5", "E4",
		"E5", "DS5", "E5", "DS5", "E5", "B4", "D5", "C5", "A4", "C4",
		"E4", "A4", "B4", "E4", "C5", "B4", "A4"
	};

	char lenghts[notes][4] = {
		"200", "200", "200", "200", "200", "200", "200", "200", "600", "200",
		"200", "200", "600", "200", "200", "200", "600", "200",
		"200", "200", "200", "200", "200", "200", "200", "200", "600", "200",
		"200", "200", "600", "200", "200", "200", "800"
	};

#elif defined(MELODY2)			/* Mario theme */
	char tones[notes][3] = {
		"E5", "E5", "00", "E5", "00", "C5", "E5", "G5", "00", "G4", "00",
		"C5", "00", "G4", "00", "E4",
		"00", "A4", "B4", "AS4", "A4",
		"G4", "E5", "G5", "A5", "F5", "G5",
		"00", "E5", "C5", "D5", "B4", "00",
		"C5", "00", "G4", "00", "E4",
		"00", "A4", "B4", "AS4", "A4",
		"G4", "E5", "G5", "A5", "F5", "G5",
		"00", "E5", "C5", "D5", "B4", "00",
		"00", "G5", "FS5", "F5", "DS5", "E5",
		"00", "GS4", "A4", "C5", "00", "A4", "C5", "D5",
		"00", "G5", "FS5", "F5", "DS5", "E5",
		"00", "C6", "C6", "C6", "00",
		"00", "G5", "FS5", "F5", "DS5", "E5",
		"00", "GS4", "A4", "C5", "00", "A4", "C5", "D5",
		"00", "DS5", "00", "D5", "00",
		"C5"
	};
	
	char lenghts[notes][4] = {
		"100", "100", "100", "100", "100", "100", "200", "200", "200", "200", "200",
		"200", "100", "200", "100", "200",
		"100", "200", "200", "100", "200",
		"133", "133", "133", "200", "100", "100",
		"100", "200", "100", "100", "200", "100",
		"200", "100", "200", "100", "200",
		"100", "200", "200", "100", "200",
		"133", "133", "133", "200", "100", "100",
		"100", "200", "100", "100", "200", "100",
		"200", "100", "100", "100", "200", "100",
		"100", "100", "100", "100", "100", "100", "100", "100",
		"200", "100", "100", "100", "200", "100",
		"100", "200", "100", "200", "200",
		"200", "100", "100", "100", "200", "100",
		"100", "100", "100", "100", "100", "100", "100", "100",
		"200", "200", "100", "200", "100",
		"200"
	};
#endif 				/* MELODY */
	
	for (int i = 0; i < notes; i++)
		DAC_Tone(str2tone(tones[i]), atoi(lenghts[i]));
}
