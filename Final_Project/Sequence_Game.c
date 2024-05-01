/**
 * @file Sequence_Game.c
 *
 * @brief Source code for the Sequence Game driver.
 *
 * This file contains the function definitions for the Sequence Game driver.
 * It interfaces with the following:
 *  - User LED (RGB) Tiva C Series TM4C123G LaunchPad
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *	- DMT-1206 Magnetic Buzzer
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */

#include "Sequence_Game.h"

// Global variable used to set the delay rate for flashing LEDs in milliseconds
const uint32_t LED_DELAY_RATE = 500;

void Generate_Sequence(uint8_t led_sequence[], uint8_t sequence_length)
{	
	// Initialize an array of possible LED values
	uint8_t possible_values[4] = {1, 2, 4, 8};
	
	for (int i = 0; i < sequence_length; i++)
	{
		// Generate a random LED value from the possible_values array
		// and store it in led_sequence
		led_sequence[i] = possible_values[rand() % 4];
		
		// Turn on the corresponding LED pattern from led_sequence
		// and provide a short delay in milliseconds
		EduBase_LEDs_Output(led_sequence[i]);
		SysTick_Delay1ms(LED_DELAY_RATE);
		
		// Turn off all LEDs on the EduBase board
		// and provide a short delay in milliseconds
		EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
		SysTick_Delay1ms(LED_DELAY_RATE);
	}
}

void Read_Player_Input(uint8_t input_sequence[], uint8_t sequence_length)
{		
	for (int i = 0; i < sequence_length; i++)
	{
		// Wait until a button is pressed
		while (Get_EduBase_Button_Status() == 0x0);
		
		// Read the value of the button pressed and store it in the input_sequence array
		input_sequence[i] = GPIOD->DATA & 0x0F;
		
		// Display the LED pattern corresponding to the button pressed
		EduBase_LEDs_Output(input_sequence[i]);
		
		// Play a sound using the buzzer for a short duration
		Play_Note(G4_NOTE, 75);
		
		// Wait until the button is released
		while (Get_EduBase_Button_Status() != 0x0);
		
		// Turn off all LEDs
		EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
		
		// Provide a short delay after a button has been released
		// to prevent any bouncing effects
		SysTick_Delay1ms(200);
	}
}

void Compare_Sequence(uint8_t led_sequence[], uint8_t input_sequence[], uint8_t sequence_length)
{
	// Compare each input value from input_sequence
	// with the corresponding LED value
	for (int i = 0; i < sequence_length; i++)
	{
		// Blink the RGB LED in red twice to indicate
		// that the user entered the incorrect input sequence
		// and exit out of the function
		if (input_sequence[i] != led_sequence[i])
		{
			Blink_RGB_LED(RGB_LED_RED, 2, LED_DELAY_RATE);
			return;
		}
	}
	
	// Blink the RGB LED in green twice to indicate
	// that the user entered the correct input sequence
	Blink_RGB_LED(RGB_LED_GREEN, 2, LED_DELAY_RATE);
}
