/*******************************************************************************
 *  This is header file for PIT module functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file pit.h
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing declarations for PIT functions
 * @ver 0.1
 *******************************************************************************/
 
#ifndef PIT_H
#define PIT_H

#include "MKL05Z4.h"

void PIT_Init(void);
void delay_us(uint32_t us);

#endif 		/* PIT_H */
