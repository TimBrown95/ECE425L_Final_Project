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

 //Notes Table 1
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
const int d_sharp_mid = 150;
const int d_mid = 211;
const int c_mid = 237;

//Notes Table 2
const int B0  = 31;
const int C1  = 33;
const int CS1 = 35;
const int D1  = 37;
const int DS1 = 39;
const int E1  = 41;
const int F1  = 44;
const int FS1 = 46;
const int G1  = 49;
const int GS1 = 52;
const int A1  = 55;
const int AS1 = 58;
const int B1  = 62;
const int C2  = 65;
const int CS2 = 69;
const int D2  = 73;
const int DS2 = 78;
const int E2  = 82;
const int F2  = 87;
const int FS2 = 93;
const int G2  = 98;
const int GS2 = 104;
const int A2  = 110;
const int AS2 = 117;
const int B2  = 123;
const int C3  = 131;
const int CS3 = 139;
const int D3  = 147;
const int DS3 = 156;
const int E3  = 165;
const int F3  = 175;
const int FS3 = 185;
const int G3  = 196;
const int GS3 = 208;
const int A3  = 220;
const int AS3 = 233;
const int B3  = 247;
const int C4  = 262;
const int CS4 = 277;
const int D4  = 294;
const int DS4 = 311;
const int E4  = 330;
const int F4  = 349;
const int FS4 = 370;
const int G4  = 392;
const int GS4 = 415;
const int A4  = 440;
const int AS4 = 466;
const int B4  = 494;
const int C5  = 523;
const int CS5 = 554;
const int D5  = 587;
const int DS5 = 622;
const int E5  = 659;
const int F5  = 698;
const int FS5 = 740;
const int G5  = 784;
const int GS5 = 831;
const int A5  = 880;
const int AS5 = 932;
const int B5  = 988;
const int C6  = 1047;
const int CS6 = 1109;
const int D6  = 1175;
const int DS6 = 1245;
const int E6  = 1319;
const int F6  = 1397;
const int FS6 = 1480;
const int G6  = 1568;
const int GS6 = 1661;
const int A6  = 1760;
const int AS6 = 1865;
const int B6  = 1976;
const int C7  = 2093;
const int CS7 = 2217;
const int D7  = 2349;
const int DS7 = 2489;
const int E7  = 2637;
const int F7  = 2794;
const int FS7 = 2960;
const int G7  = 3136;
const int GS7 = 3322;
const int A7  = 3520;
const int AS7 = 3729;
const int B7  = 3951;
const int C8  = 4186;
const int CS8 = 4435;
const int D8  = 4699;
const int DS8 = 4978;

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
			EduBase_LCD_Print_Text("Press a button", "to play a song");
		}
		break;
		
		// When SW5 is pressed, the Imperial March Theme is played
		case 0x01:
		{
			EduBase_LCD_Print_Text("Song", "Imperial March");
			
			//Play first section
      beep(a, 150);
			SysTick_Delay1ms(5);
      beep(a, 150);
			SysTick_Delay1ms(5);
      beep(a, 150);
			SysTick_Delay1ms(5);
      beep(f, 175);
      beep(cH, 75); 
      beep(a, 150);
      beep(f, 175);
      beep(cH, 75);
      beep(a, 325);
    
      SysTick_Delay1ms(150);
    
      beep(eH, 150);
      beep(eH, 150);
      beep(eH, 150); 
      beep(fH, 175);
      beep(cH, 75);
      beep(gS, 150);
      beep(f, 175);
      beep(cH, 75);
      beep(a, 325);
    
      SysTick_Delay1ms(150);
			
      //Play second section
      beep(aH, 150);
      beep(a, 150);
      beep(a, 75);
      beep(aH, 150);
      beep(gSH, 175);
      beep(gH, 88);
      beep(fSH, 63);
      beep(fH, 63);   
      beep(fSH, 125);
    
      SysTick_Delay1ms(150);
    
      beep(aS, 125);
      beep(dSH, 150);
      beep(dH, 175); 
      beep(cSH, 88); 
      beep(cH, 63); 
      beep(b, 63); 
      beep(cH, 125); 
    
     SysTick_Delay1ms(150);
    
      //Variant 1
      beep(f, 175); 
      beep(gS, 150); 
      beep(f, 175); 
      beep(a, 63);
      beep(cH, 150);
      beep(a, 188); 
      beep(cH, 63);
      beep(eH, 325);
    
      SysTick_Delay1ms(150);
    
      //Repeat second section
      beep(aH, 150);
      beep(a, 150);
      beep(a, 75);
      beep(aH, 150);
      beep(gSH, 163);
      beep(gH, 88);
      beep(fSH, 63);
      beep(fH, 63);   
      beep(fSH, 125);
    
      SysTick_Delay1ms(150);
    
      beep(aS, 125);
      beep(dSH, 150);
      beep(dH, 163); 
      beep(cSH, 88); 
      beep(cH, 63); 
      beep(b, 63); 
      beep(cH, 125); 
    
      SysTick_Delay1ms(500);
    
      //Variant 2
      beep(f, 125); 
      beep(gS, 150); 
      beep(f, 188); 
      beep(cH, 63);
      beep(a, 150); 
      beep(f, 188); 
      beep(cH, 63);
      beep(a, 325); 
    
     SysTick_Delay1ms(500);
		}
		break;
		
		// When SW4 is pressed, Super Mario Bros Theme is played
		case 0x02:
		{
			EduBase_LCD_Print_Text("Song", "Super Mario Bros");
				beep(E5 ,100);
			SysTick_Delay1ms(3);
				beep(E5 ,100);
			SysTick_Delay1ms(3);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(C5 ,100);
				beep(E5 ,100);
				beep(G5 ,100);
				beep(G4 ,100);
	
				beep(C5 ,100);
				SysTick_Delay1ms(3);
				beep(G4 ,100);
				SysTick_Delay1ms(6);
				beep(E4 ,100);
				SysTick_Delay1ms(3);
				beep(A4 ,100);
				SysTick_Delay1ms(3);
				beep(B4 ,100);
				SysTick_Delay1ms(3);
				beep(AS4,100);
				beep(A4 ,100);
	
				beep(G4 ,100);
				beep(E5 ,100);
				beep(G5 ,100);
				beep(A5 ,100);
				beep(F5 ,100);
				beep(G5 ,100);
				SysTick_Delay1ms(3);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(C5 ,100);
				beep(D5 ,100);
				beep(B4 ,100);
				SysTick_Delay1ms(6);
				
				beep(C5 ,100);
				SysTick_Delay1ms(3);
				beep(G4 ,100);
				SysTick_Delay1ms(6);
				beep(E4 ,100);
				SysTick_Delay1ms(3);
				beep(A4 ,100);
				SysTick_Delay1ms(3);
				beep(B4 ,100);
				SysTick_Delay1ms(3);
				beep(AS4,100);
				beep(A4 ,100);
				
				beep(G4 ,100);
				beep(E5 ,100);
				beep(G5 ,100);
				beep(A5 ,100);
				beep(F5 ,100);
				beep(G5 ,100);
				SysTick_Delay1ms(3);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(C5 ,100);
				beep(D5 ,100);
				beep(B4 ,10);
				SysTick_Delay1ms(6);

				SysTick_Delay1ms(6);
				beep(G5 ,100);
				beep(FS5,100);
				beep(F5 ,100);
				beep(DS5,100);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(GS4,100);
				beep(A4 ,100);
				beep(C5 ,100);
				SysTick_Delay1ms(3);
				beep(A4 ,100);
				beep(C5 ,100);
				beep(D5 ,100);

				SysTick_Delay1ms(6);
				beep(G5 ,100);
				beep(FS5,100);
				beep(F5 ,100);
				beep(DS5,100);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(C6 ,100);
				SysTick_Delay1ms(3);
				beep(C6 ,100);
				beep(C6 ,100);


				SysTick_Delay1ms(6);
				beep(G5 ,100);
				beep(FS5,100);
				beep(F5 ,100);
				beep(DS5,100);
				beep(E5 ,100);
				SysTick_Delay1ms(3);
				beep(GS4,100);
				beep(A4 ,100);
				beep(C5 ,100);
				SysTick_Delay1ms(3);
				beep(A4 ,100);
				beep(C5 ,100);
				beep(D5 ,100);

				SysTick_Delay1ms(6);
				beep(DS5,100);
				SysTick_Delay1ms(3);
				beep(D5 ,100);
				SysTick_Delay1ms(6);
				beep(C5 ,100);
				SysTick_Delay1ms(12);

		}
		break;
		
		// When SW3 is pressed, the Mexican Hat Dance Theme is played
		case 0x04:
		{
			EduBase_LCD_Print_Text("Song", "Tetris");
				beep(E5, 100);
				beep(B4,200);
				beep(C5,200);
				beep(D5,100);
				beep(C5,200);
				beep(B4,200);
				beep(A4, 100);
				beep(A4,200);
				beep(C5,200);
				beep(E5,100);
				beep(D5,200);
				beep(C5,200);

				beep(B4, 100);
				beep(C5,200);
				beep(D5,100);
				beep(E5,100);
				beep(C5, 100);
				beep(A4,100);
				beep(A4,200);
				beep(A4,100);
				beep(B4,200);
				beep(C5,200);

				beep(D5, 100);
				beep(F5,200);
				beep(A5,100);
				beep(G5,200);
				beep(F5,200);

				beep(E5, 100);
				beep(C5,200);
				beep(E5,100);
				beep(D5,200);
				beep(C5,200);

				beep(B4,100);
				beep(B4,200);
				beep(C5,200);
				beep(D5,100);
				beep(E5,100);

				beep(C5, 100);
				beep(A4,100);
				beep(A4,100);
				SysTick_Delay1ms(100);

				beep(E5, 100);
				beep(B4,200);
				beep(C5,200);
				beep(D5,100);
				beep(C5,200);
				beep(B4,200);

				beep(A4, 100);
				beep(A4,200);
				beep(C5,200);
				beep(E5,100);
				beep(D5,200);
				beep(C5,200);

				beep(B4, 100);
				beep(C5,200);
				beep(D5,100);
				beep(E5,100);

				beep(C5, 100);
				beep(A4,100);
				beep(A4,200);
				beep(A4,100);
				beep(B4,200);
				beep(C5,200);

				beep(D5, 100);
				beep(F5,200);
				beep(A5,100);
				beep(G5,200);
				beep(F5,200);

				beep(E5, 100);
				beep(C5,200);
				beep(E5,100);
				beep(D5,200);
				beep(C5,200);

				beep(B4, 100);
				beep(B4,200);
				beep(C5,200);
				beep(D5,100);
				beep(E5,100);

				beep(C5, 100);
				beep(A4,100);
				beep(A4,100);

				SysTick_Delay1ms(100);


				beep(E5,50);
				beep(C5,50);

				beep(D5,50);
				beep(B4,50);

				beep(C5,50);
				beep(A4,50);

				beep(GS4,50);
				beep(B4,100);

				SysTick_Delay1ms(200);
				
				beep(E5,50);
				beep(C5,50);
				beep(D5,50);
				beep(B4,50);

				beep(C5,100);
				beep(E5,100);
				beep(A5,50);
				beep(GS5,50);


			
		}
		break;
		
		
		case 0x08:
		{
		// When SW2 is pressed, "Take on Me" is played
			
			EduBase_LCD_Print_Text("Song", "Aha - Take On Me");

				beep(FS5,100);
				beep(FS5,100);
				beep(D5,100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(E5,100);

				SysTick_Delay1ms(100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(E5,100);
				beep(GS5,100);
				beep(GS5,100);
				beep(A5,100);
				beep(B5,100);

				beep(A5,100);
				beep(A5,100);
				beep(A5,100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(D5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);

				SysTick_Delay1ms(100);
				beep(FS5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);
				beep(E5,100);
				beep(E5,100);
				beep(FS5,100);
				beep(E5,100);

				beep(FS5,100);
				beep(FS5,100);
				beep(D5,100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(E5,100); 

				SysTick_Delay1ms(100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(E5,100);
				beep(GS5,100);
				beep(GS5,100);
				beep(A5,100);
				beep(B5,100);

				beep(A5,100);
				beep(A5,100);
				beep(A5,100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(D5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);

				SysTick_Delay1ms(100);
				beep(FS5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);
				beep(E5,100);
				beep(E5,100);
				beep(FS5,100);
				beep(E5,100);

				beep(FS5,100);
				beep(FS5,100);
				beep(D5,100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(B4,100);
				SysTick_Delay1ms(100);
				beep(E5,100);

				SysTick_Delay1ms(100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(E5,100);
				beep(GS5,100);
				beep(GS5,100);
				beep(A5,100);
				beep(B5,100);

				beep(A5,100);
				beep(A5,100);
				beep(A5,100);
				beep(E5,100);
				SysTick_Delay1ms(100);
				beep(D5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);

				SysTick_Delay1ms(100);
				beep(FS5,100);
				SysTick_Delay1ms(100);
				beep(FS5,100);
				beep(E5,100);
				beep(E5,100);
				beep(FS5,100);
				beep(E5,100);

			
			
		}
	}
}
