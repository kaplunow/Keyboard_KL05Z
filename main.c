#include "lcd1602.h"
#include "buttons.h"
#include "tpm.h"
#include "tone.h"
#include <stdio.h>


int main()
{
	
	buttons_Init();
	LCD1602_Init();
	TPM0_Init();
	
	while (1)
	{
		uint8_t button = get_button();
		enum e_tone tone = get_tone(button);
		if (tone) {
			TPM0_Tone(tone);
			
			const char* tone_str = tone2str(tone);
			char str[50];
			sprintf(str, "Tone=%s", tone_str);
			LCD1602_ClearAll();
			LCD1602_Print(str);
		}

	}
	
}
