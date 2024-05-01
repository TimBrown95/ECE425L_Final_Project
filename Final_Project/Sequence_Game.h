/**
 * @file Sequence_Game.h
 *
 * @brief Header file for the Sequence Game driver.
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

#include "TM4C123GH6PM.h"
#include "stdlib.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "Buzzer.h"

// Global variable used to set the delay rate for flashing LEDs in milliseconds
extern const uint32_t LED_DELAY_RATE;

/**
 * @brief The Generate_Sequence function generates a pseudo-random sequence of LED patterns and outputs them to the LEDs.
 *
 * This function generates a sequence of LED patterns by randomly selecting values from the possible_values array
 * using the rand() function and storing them in the led_sequence array. For each value in the sequence, 
 * it outputs the corresponding LED pattern using the EduBase_LEDs_Output function, followed by a delay 
 * of LED_DELAY_RATE milliseconds. After each LED pattern is displayed, all LEDs are turned off 
 * for the same duration to create a blinking effect.
 *
 * "rand() % 4" generates a pseudo-random number uses the modulo operator
 * to calculate the remainder when the random number is divided by 4,
 * providing a result between 0 and 3 because any (integer % 4) can only have a 
 * remainder in this range
 *
 * @param led_sequence An array to store the generated LED sequence.
 * 
 * @param sequence_length The length of the LED sequence to generate.
 *
 * @return None
 */
void Generate_Sequence(uint8_t led_sequence[], uint8_t sequence_length);

/**
 * @brief The Read_Player_Input function reads the player's input from the buttons, displays corresponding LED patterns, and plays buzzer sounds.
 *
 * This function reads the player's input from EduBase board push buttons. It waits until any button is pressed, reads
 * the value of the pressed button, and stores it in the input_sequence array. For each button press, it displays the
 * corresponding LED pattern using the EduBase_LEDs_Output function and plays the corresponding note using the Play_Note function.
 * It then waits until the button is released before proceeding to the next input. After each input, it turns off all LEDs
 * and waits for a short duration.
 *
 * @param input_sequence An array to store the player's input sequence.
 *
 * @param sequence_length The length of the input sequence to read.
 *
 * @return None
 */
void Read_Player_Input(uint8_t input_sequence[], uint8_t sequence_length);

/**
 * @brief The Compare_Sequence function compares the player's input sequence with the generated LED sequence.
 *
 * This function compares the player's input sequence with the generated LED sequence
 * to determine if the player correctly reproduced the sequence. If any input value differs from the corresponding
 * LED sequence value, the function indicates a wrong input by blinking the RGB LED in red twice. If the input matches
 * the LED sequence, the function indicates a correct input by blinking the RGB LED in green twice.
 *
 * @param led_sequence The generated LED sequence to compare against.
 *
 * @param input_sequence The player's input sequence to compare.
 *
 * @param sequence_length The length of the sequences to compare.
 *
 * @return None
 */
void Compare_Sequence(uint8_t led_sequence[], uint8_t input_sequence[], uint8_t sequence_length);
