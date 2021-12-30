#include "tpm.h"

#define TPM_CH		0											/* CHANNEL 0 of TPM0 */
#define TPM_PIN 	11										/* PTB11 */
#define A4		2914.0f

void TPM0_Init() {
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;				/* Enable TPM0 mask in SCGC6 register */
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);  		  /* Choose MCGFLLCLK clock source */
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;   		/* Connect port B to clock */
  PORTB->PCR[TPM_PIN] = PORT_PCR_MUX(2);		/* Set multiplekser to TPM0 for PTB0 */
	
	TPM0->SC |= TPM_SC_PS(4);  								/* Set prescaler to 16 */
	TPM0->MOD = A4; 												/* Set modulo value */
	TPM0->SC |= TPM_SC_CMOD(1);								/* For TMP0, select the internal input clock source */

	TPM0->CONTROLS[TPM_CH].CnSC |= (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK); 			/* Output compare, toggle on match */ 
	TPM0->CONTROLS[2].CnV = A4 / 2; 			/* 180 degree phase shift */

}
