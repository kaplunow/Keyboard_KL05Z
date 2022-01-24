/*******************************************************************************
 *  This is header file for tact switch matrix usage functions.
 *  Software is part of Keyboard_KL05Z project and it's designed for KL05Z CMSIS.
 *******************************************************************************
 * @file buttons.h
 * @author Kaplunow, Lisowski
 * @date Jan 2022
 * @brief File containing declarations for DAC functions
 * @ver 0.1
 *******************************************************************************/
 
#ifndef BUTTONS_H
#define BUTTONS_H

#include "frdm_bsp.h"

void buttons_Init(void);
uint8_t get_button(void);
void set_button(uint8_t new_button);
	
#endif  /* BUTTONS_H */
