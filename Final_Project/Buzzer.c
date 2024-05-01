/**
 * @file Buzzer.c
 *
 * @brief Source code for the Buzzer driver.
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
 
#include "Buzzer.h"
#include "GPIO.h"
#include "SysTick_Delay.h"
#include "EduBase_LCD.h"

// Constant definitions for the buzzer
const uint8_t BUZZER_OFF 		= 0x00;
const uint8_t BUZZER_ON			= 0x10;

 //Notes
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
const int R = 0;

const int a_up1 = 70;
const int g_up1 = 78;
const int f_up1 = 88;
const int e_up1 = 93;
const int d_up1 = 105;
const int c_sharp_up = 112;
const int c_up1 = 118;
const int b_mid = 125;
const int b_flat_mid = 130;
const int a_mid = 141;
const int g_sharp_mid = 150;
const int g_mid = 158;
const int f_sharp_mid = 168;
const int f_mid = 177;
const int e_mid = 188;
const int d_sharp_mid = 200;
const int d_mid = 211;
const int c_mid = 237;

void Buzzer_Init(void)
{
	// Enable Clock to Port C
	SYSCTL->RCGCGPIO |= 0x04;
	
	// Set PC4 as an output GPIO pin
	GPIOC->DIR |= 0x10;
	
	// Configure PC4 to function as a GPIO pin
	GPIOC->AFSEL &= ~0x10;
	
	// Enable Digital Functionality for PC4
	GPIOC->DEN |= 0x10;
}
 
void Buzzer_Output(uint8_t buzzer_value)
{
	 // Set the output of the buzzer
	GPIOC->DATA = (GPIOC->DATA & 0xEF) | buzzer_value;
}

void beep(int note, unsigned int duration)
{
	// Calculate the period of the note in microseconds
	int period_us = (int)(((double)1/note) * ((double)1000000));
	
	// Calculate the half period of the note in microseconds
	int half_period_us = period_us / 2;
	
	// Generate a square wave for the specified duration
	for (unsigned int i = 0; i < duration; i++)
	{
		Buzzer_Output(BUZZER_ON);
		SysTick_Delay1us(half_period_us);
		Buzzer_Output(BUZZER_OFF);
		SysTick_Delay1us(half_period_us);
	}
}


void Song_Select(uint8_t edubase_button_status)
{
	switch(edubase_button_status)	
	{
		// No buttons are pressed
		case 0x00:
		{
			
		}
		break;
		
		// SW5 is pressed Mario is Played
		case 0x01:
		{
			EduBase_LCD_Print_Text("Song", "Imperial March");
			
			//Play first section
      beep(a, 250);
			SysTick_Delay1ms(5);
      beep(a, 250);
			SysTick_Delay1ms(5);
      beep(a, 250);
			SysTick_Delay1ms(5);
      beep(f, 175);
      beep(cH, 75); 
      beep(a, 250);
      beep(f, 175);
      beep(cH, 75);
      beep(a, 325);
    
      SysTick_Delay1ms(250);
    
      beep(eH, 250);
      beep(eH, 250);
      beep(eH, 250); 
      beep(fH, 175);
      beep(cH, 75);
      beep(gS, 250);
      beep(f, 175);
      beep(cH, 75);
      beep(a, 325);
    
      SysTick_Delay1ms(250);
			
      //Play second section
      beep(aH, 250);
      beep(a, 150);
      beep(a, 75);
      beep(aH, 250);
      beep(gSH, 175);
      beep(gH, 88);
      beep(fSH, 63);
      beep(fH, 63);   
      beep(fSH, 125);
    
      SysTick_Delay1ms(250);
    
      beep(aS, 125);
      beep(dSH, 250);
      beep(dH, 175); 
      beep(cSH, 88); 
      beep(cH, 63); 
      beep(b, 63); 
      beep(cH, 125); 
    
     SysTick_Delay1ms(250);
    
      //Variant 1
      beep(f, 175); 
      beep(gS, 250); 
      beep(f, 175); 
      beep(a, 63);
      beep(cH, 250);
      beep(a, 188); 
      beep(cH, 63);
      beep(eH, 325);
    
      SysTick_Delay1ms(250);
    
      //Repeat second section
      beep(aH, 250);
      beep(a, 150);
      beep(a, 75);
      beep(aH, 250);
      beep(gSH, 163);
      beep(gH, 88);
      beep(fSH, 63);
      beep(fH, 63);   
      beep(fSH, 125);
    
      SysTick_Delay1ms(250);
    
      beep(aS, 125);
      beep(dSH, 250);
      beep(dH, 163); 
      beep(cSH, 88); 
      beep(cH, 63); 
      beep(b, 63); 
      beep(cH, 125); 
    
      SysTick_Delay1ms(500);
    
      //Variant 2
      beep(f, 125); 
      beep(gS, 250); 
      beep(f, 188); 
      beep(cH, 63);
      beep(a, 250); 
      beep(f, 188); 
      beep(cH, 63);
      beep(a, 325); 
    
     SysTick_Delay1ms(500);
		}
		break;
		
		// SW4 is pressed. Mexican Hat Dance Plays
		case 0x02:
		{
			EduBase_LCD_Print_Text("Song", "Mario");
				tone(e5 ,3);
				tone(e5 ,6);
				tone(e5 ,3);
				sleep(3);
				tone(c5 ,3);
				tone(e5 ,6);
				tone(g5 ,12);
				tone(g4 ,12);
	
				tone(c5 ,6);
				sleep(3);
				tone(g4 ,3);
				sleep(6);
				tone(e4 ,6);
				sleep(3);
				tone(a4 ,3);
				sleep(3);
				tone(b4 ,3);
				sleep(3);
				tone(a4s,3);
				tone(a4 ,6);
	
				tone(g4 ,4);
				tone(e5 ,4);
				tone(g5 ,4);
				tone(a5 ,6);
				tone(f5 ,3);
				tone(g5 ,3);
				sleep(3);
				tone(e5 ,3);
				sleep(3);
				tone(c5 ,3);
				tone(d5 ,3);
				tone(b4 ,3);
				sleep(6);
				
				tone(c5 ,6);
				sleep(3);
				tone(g4 ,3);
				sleep(6);
				tone(e4 ,6);
				sleep(3);
				tone(a4 ,3);
				sleep(3);
				tone(b4 ,3);
				sleep(3);
				tone(a4s,3);
				tone(a4 ,6);
				
				tone(g4 ,4);
				tone(e5 ,4);
				tone(g5 ,4);
				tone(a5 ,6);
				tone(f5 ,3);
				tone(g5 ,3);
				sleep(3);
				tone(e5 ,3);
				sleep(3);
				tone(c5 ,3);
				tone(d5 ,3);
				tone(b4 ,3);
				sleep(6);

				sleep(6);
				tone(g5 ,3);
				tone(f5s,3);
				tone(f5 ,3);
				tone(d5s,6);
				tone(e5 ,3);
				sleep(3);
				tone(g4s,3);
				tone(a4 ,3);
				tone(c5 ,3);
				sleep(3);
				tone(a4 ,3);
				tone(c5 ,3);
				tone(d5 ,3);

				sleep(6);
				tone(g5 ,3);
				tone(f5s,3);
				tone(f5 ,3);
				tone(d5s,6);
				tone(e5 ,3);
				sleep(3);
				tone(c6 ,3);
				sleep(3);
				tone(c6 ,3);
				tone(c6 ,12);


				sleep(6);
				tone(g5 ,3);
				tone(f5s,3);
				tone(f5 ,3);
				tone(d5s,6);
				tone(e5 ,3);
				sleep(3);
				tone(g4s,3);
				tone(a4 ,3);
				tone(c5 ,3);
				sleep(3);
				tone(a4 ,3);
				tone(c5 ,3);
				tone(d5 ,3);

				sleep(6);
				tone(d5s,6);
				sleep(3);
				tone(d5 ,3);
				sleep(6);
				tone(c5 ,12);
				sleep(12);

		}
		break;
		
		// SW3 is pressed
		case 0x04:
		{
			
		}
		break;
		
		
		default:
		{
		
			
		}
	}
}
