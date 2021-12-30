#include "lcd1602.h"
#include "buttons.h"
#include "tpm.h"
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
		sprintf(str, "Button=%d", get_button());
		LCD1602_ClearAll();
		LCD1602_Print(str);
		DELAY(100)
	}
}
