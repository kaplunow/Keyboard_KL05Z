#include "lcd1602.h"
#include "buttons.h"
#include "tone.h"
#include "dac.h"
#include "pit.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char rx_buf[16];
uint8_t rx_buf_pos=0;
uint8_t rx_FULL=0;

void LCD_Write(const char * str) {
	char buff[50];
	sprintf(buff, "Tone=%s", str);
	LCD1602_ClearAll();
	LCD1602_Print(buff);
}

void UART0_IRQHandler() {
	if(UART0->S1 & UART0_S1_RDRF_MASK) {		/* If data recived */
		char temp = UART0->D;											/* Read the buffer and clear RDRF flag*/
		if(!rx_FULL) {
			if(temp!=LF) {											/* Check for '\n' */
				rx_buf[rx_buf_pos] = temp;	
				rx_buf_pos++;
			}
			else 
				rx_FULL=1;
		}
	}
}

int main()
{
	
	buttons_Init();
	LCD1602_Init();
	PIT_Init();
	DAC_Init();
	UART_Init();
	
	int pos = 0;
	char tones[20][2];
	char lengths[20][4];		
	
	while (1)
	{
		
		//uint8_t button = get_button();
		//enum e_tone tone = get_tone(button);
		//if (tone) {
			//DAC_Tone(tone, 500);
			
			//const char* tone_str = tone2str(tone);
			//char str[50];
			//sprintf(str, "Tone=%s", tone_str);
			//LCD1602_ClearAll();
			//LCD1602_Print(str);
			
			//set_button(0);
		
			
		
			if(rx_FULL) {		

				if (strcmp(rx_buf, "play") == 0) {
					for (int i = 0; i < pos; i++) {
						char tone[2];
						strncpy(tone, tones[i], 2);
						DAC_Tone(str2tone(tone), atoi(lengths[i]));
					}
				}
				
				else {
					const char* token = strtok(rx_buf, " \n");				
					strcpy(tones[pos], token);
					token = strtok(NULL, " ");
					strcpy(lengths[pos], token);	
					pos++;
				}
			
				rx_buf_pos=0;
				memset(rx_buf, 0, sizeof rx_buf);
				rx_FULL=0;	// Dana skonsumowana
			}
	}
}
