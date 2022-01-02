#include "lcd1602.h"
#include "buttons.h"
#include "tpm.h"
#include "tone.h"
#include <stdio.h>

//void LED_Init() {
//	SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK;
//	PORTB->PCR[9] |= PORT_PCR_MUX(1);
//	FPTB->PDDR |= (1 << 9);
//	FPTB->PSOR |= (1 << 9);
//}

int main()
{
	buttons_Init();
	LCD1602_Init();
	TPM0_Init();
	//LED_Init();
	while (1)
	{
		char str[50];
		uint8_t button = get_button();
		sprintf(str, "Button=%d", button);
		LCD1602_ClearAll();
		LCD1602_Print(str);
		
		if (button == 1)
			TPM0_Tone(C4);
		else if (button == 2)
			TPM0_Tone(D4);
		else if (button == 3)
			TPM0_Tone(E4);
		else if (button == 4)
			TPM0_Tone(F4);
		else if (button == 5)
			TPM0_Tone(G4);
		else if (button == 6)
			TPM0_Tone(A4);
		else if (button == 7)
			TPM0_Tone(B4);
		else if (button == 8)
			TPM0_Tone(C5);
		else 
			DELAY(100)
	}
}
