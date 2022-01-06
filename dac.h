#ifndef DAC_H
#define DAC_H

#include "MKL05Z4.h"
#include "tone.h"

void DAC_Init(void);
uint8_t DAC_Load_Trig(uint16_t load);
void DAC_Tone(enum e_tone tone, uint32_t time_ms);

#endif /* DAC_H */
