/**
 * @file Buzzer.h
 *
 * @brief Header file for the Buzzer driver.
 *
 * This file contains the function definitions for the Buzzer driver.
 * It interfaces with the following:
 *	- DMT-1206 Magnetic Buzzer
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"

// Constant definitions for the buzzer
extern const uint8_t BUZZER_OFF;
extern const uint8_t BUZZER_ON;

// Constant definitions for musical notes (Notes Table 1)
extern const int c;
extern const int d;
extern const int e;
extern const int f;
extern const int g;
extern const int gS;
extern const int a;
extern const int aS;
extern const int b;
extern const int cH;
extern const int cSH;
extern const int dH;
extern const int dSH;
extern const int eH;
extern const int fH;
extern const int fSH;
extern const int gH;
extern const int gSH;
extern const int aH;
extern const int R;

extern const int a_up1;
extern const int g_up1;
extern const int f_up1;
extern const int e_up1;
extern const int d_up1;
extern const int c_sharp_up;
extern const int c_up1;
extern const int b_mid;
extern const int b_flat_mid;
extern const int a_mid;
extern const int g_sharp_mid;
extern const int g_mid;
extern const int f_sharp_mid;
extern const int f_mid;
extern const int e_mid;
extern const int d_sharp_mid;
extern const int d_mid;
extern const int c_mid;

// Constant definitions for musical notes (Notes Table 2)
extern const int B0 ;
extern const int C1 ;
extern const int CS1;
extern const int D1 ;
extern const int DS1;
extern const int E1 ;
extern const int F1 ;
extern const int FS1;
extern const int G1 ;
extern const int GS1;
extern const int A1 ;
extern const int AS1;
extern const int B1 ;
extern const int C2 ;
extern const int CS2;
extern const int D2 ;
extern const int DS2;
extern const int E2 ;
extern const int F2 ;
extern const int FS2;
extern const int G2 ;
extern const int GS2;
extern const int A2 ;
extern const int AS2;
extern const int B2 ;
extern const int C3 ;
extern const int CS3;
extern const int D3 ;
extern const int DS3;
extern const int E3 ;
extern const int F3 ;
extern const int FS3;
extern const int G3 ;
extern const int GS3;
extern const int A3 ;
extern const int AS3;
extern const int B3 ;
extern const int C4 ;
extern const int CS4;
extern const int D4 ;
extern const int DS4;
extern const int E4 ;
extern const int F4 ;
extern const int FS4;
extern const int G4 ;
extern const int GS4;
extern const int A4 ;
extern const int AS4;
extern const int B4 ;
extern const int C5 ;
extern const int CS5;
extern const int D5 ;
extern const int DS5;
extern const int E5 ;
extern const int F5 ;
extern const int FS5;
extern const int G5 ;
extern const int GS5;
extern const int A5 ;
extern const int AS5;
extern const int B5 ;
extern const int C6 ;
extern const int CS6;
extern const int D6 ;
extern const int DS6;
extern const int E6 ;
extern const int F6 ;
extern const int FS6;
extern const int G6 ;
extern const int GS6;
extern const int A6 ;
extern const int AS6;
extern const int B6 ;
extern const int C7 ;
extern const int CS7;
extern const int D7 ;
extern const int DS7;
extern const int E7 ;
extern const int F7 ;
extern const int FS7;
extern const int G7 ;
extern const int GS7;
extern const int A7 ;
extern const int AS7;
extern const int B7 ;
extern const int C8 ;
extern const int CS8;
extern const int D8 ;
extern const int DS8;



/**
 * @brief Initializes the DMT-1206 Magnetic Buzzer on the EduBase board.
 *
 * This function configures the PC4 pin used by the DMT-1206 Magnetic Buzzer.
 * It enables the clock to Port C, sets PC4 as an output GPIO pin, configures PC4 to function as a GPIO pin,
 * and enables digital functionality for PC4.
 *
 * @param None
 *
 * @return None
 */
void Buzzer_Init(void);

/**
 * @brief Sets the output of the DMT-1206 Magnetic Buzzer.
 *
 * This function sets the output of the buzzer based on the value of the input, buzzer_value.
 * A bitwise AND operation (& 0xEF) is performed to mask Bit 4 of the GPIOC's DATA register
 * to preserve the state of other pins connected to Port C while keeping the buzzer pin unaffected.
 * Then, a bitwise OR operation is performed with buzzer_value to set the buzzer pin to the desired state
 * specified by buzzer_value.
 *
 * @param buzzer_value An 8-bit unsigned integer that determines the output of the buzzer. To turn off
 *                      the buzzer, set buzzer_value to 0. To turn on the buzzer, set buzzer_value to 0x10.
 *
 * @return None
 */
void Buzzer_Output(uint8_t buzzer_value);

/**
 * @brief Plays a note with the DMT-1206 Magnetic Buzzer.
 *
 * This function generates a square wave with the DMT-1206 Magnetic Buzzer to produce a note of the specified frequency and duration.
 * It calculates the period of the note in microseconds, divides it by two to get half period, and then toggles the
 * buzzer output at the half period interval for the specified duration.
 *
 * @param note The frequency of the note to play in Hz.
 *
 * @param duration The duration of the note in microseconds.
 *
 * @return None
 */
void beep(int note, unsigned int duration);

void NOTE(int note, unsigned int duration);

void Mario(void);

void PlaySongs(uint8_t button_status);

void Song_Select(uint8_t edubase_button_status);
