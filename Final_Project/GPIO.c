/**
 * @file GPIO.c
 *
 * @brief Source code for the GPIO driver.
 *
 * This file contains the function definitions for the GPIO driver.
 * It interfaces with the following:
 *  - User LED (RGB) Tiva C Series TM4C123G LaunchPad
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */

#include "GPIO.h"

void EduBase_Button_Init(void)
{
	// Enable Clock to Port D
	SYSCTL->RCGCGPIO |= 0x08;
	
	// Set PD0, PD1, PD2, and PD3 as input GPIO pins
	GPIOD->DIR &= ~0x0F;
	
	// Configure PD0, PD1, PD2, and PD3 to function as GPIO pins
	GPIOD->AFSEL &= ~0x0F;
	
	// Enable Digital Functionality for PD0, PD1, PD2, and PD3
	GPIOD->DEN |= 0x0F;
}

uint8_t Get_EduBase_Button_Status(void)
{
	uint8_t button_status = GPIOD->DATA & 0xF;
	return button_status;
}

