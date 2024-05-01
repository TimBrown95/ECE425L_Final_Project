/*
 * @file main.c
 *
 * @brief Main source code for the Final Project program.
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"
#include "stdlib.h"
#include "string.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "Buzzer.h"
#include "EduBase_LCD.h"


int main(void)
{		
	// Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	// Initialize the Magnetic Buzzer (Port C)
	Buzzer_Init();
	
	// Initialize the 16x2 LCD on the EduBase board
	EduBase_LCD_Init();
	
	// Initialize the buttons (SW2 - SW5) on the EduBase board (Port D)
	EduBase_Button_Init();
	
	while(1)
	{
		uint8_t button_status = Get_EduBase_Button_Status();
		Song_Select(button_status);
	}
	

	while(1)
	{
		uint8_t button_status = Get_EduBase_Button_Status();
		EduBase_LCD_Controller(button_status);
	}
}
