/*******************************************************************************
 *  This is header file for UART module functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file uart.h
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing declarations for UART functions
 * @ver 0.1
 *******************************************************************************/
 
#ifndef UART_H
#define UART_H

#define LF	0xa		 			/* Line feed */

void UART_Init(void);
void UART_play(void);

#endif 	/* UART_H */
