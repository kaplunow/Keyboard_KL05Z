#ifndef TPM_H
#define TPM_H

#include "MKL05Z4.h"
#include "tone.h"

void TPM0_Init(void);
void TPM0_Start(void);
void TPM0_Stop(void);
void TPM0_Tone(enum e_tone tone);

#endif  /* TPM_H */
