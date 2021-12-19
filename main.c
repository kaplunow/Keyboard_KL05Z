#include "lcd1602.h"
#include "buttons.h"
#include <stdio.h>

void led_delay(){
volatile int delay;
	for(delay=0; delay<1200000; delay++);
}

int main()
{
	buttons_Init();
	LCD1602_Init();
	while (1)
	{
		char str[50];
		sprintf(str, "Button=%d", get_button());
		LCD1602_ClearAll();
		LCD1602_Print(str);
		led_delay();
	}
}
