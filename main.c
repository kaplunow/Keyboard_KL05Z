#include "lcd1602.h"
#include "buttons.h"
#include "tone.h"
#include "dac.h"
#include "pit.h"
#include <stdio.h>


int main()
{
	
	buttons_Init();
	LCD1602_Init();
	PIT_Init();
	DAC_Init();
	
	while (1)
	{
		uint8_t button = get_button();
		enum e_tone tone = get_tone(button);
		if (tone) {
			DAC_Tone(tone, 500);
			
			const char* tone_str = tone2str(tone);
			char str[50];
			sprintf(str, "Tone=%s", tone_str);
			LCD1602_ClearAll();
			LCD1602_Print(str);
			
			set_button(0);
		}

	}
	
}
