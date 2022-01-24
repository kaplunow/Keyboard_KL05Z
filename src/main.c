/*******************************************************************************
 *  This is main file for Keyboard_KL05Z project.
 *  Software is designed for KL05Z CMSIS.
 *******************************************************************************
 * @file main.c
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing main
 * @ver 0.1
 *******************************************************************************/ 
 
#include "utils.h"

int main()
{
	
	/* Initialize */
	buttons_Init();
	LCD1602_Init();
	PIT_Init();
	DAC_Init();
	UART_Init();
	
	
	/* Main loop */
	while (1)
	{
			button_play();
			UART_play();
	}
	
	
}
