#include "lcd1602.h"
#include "buttons.h"
#include "tone.h"
#include "dac.h"
#include "pit.h"
#include "uart.h"
#include <stdio.h>

static void button_play(void);


int main()
{
	
	buttons_Init();
	LCD1602_Init();
	PIT_Init();
	DAC_Init();
	UART_Init();
	
	while (1)
	{
			button_play();
			UART_play();
	}
}


void button_play() {
	uint8_t button = get_button();
	enum e_tone tone = get_tone(button);
	if (tone) {
		const char* tone_str = tone2str(tone);
		char str[20];
		sprintf(str, "Tone=%s", tone_str);
		LCD1602_ClearAll();
		LCD1602_Print(str);
		DAC_Tone(tone, 200);
		
		set_button(0);
	}
}
