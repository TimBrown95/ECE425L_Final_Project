#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "Buzzer.h"

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

void beep(double note, unsigned int duration)
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

int MAX_COUNT = sizeof(melody1) / 2;

// Melody 1: Imperial March
void ImperialMarchNotes()
 {

	int melody1[] = {  a, R,  a, R,  a, R,  f, R, cH, R,  a, R,  f, R, cH, R, a, R,  eH, R,  eH, R,  eH, R,  fH, R, cH, R,  gH, R,  fH, R,  cH, R, a, R};
	int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};
 }

// Melody 2: Star Wars Theme
void StarWarsNotes()
{
				/*beep(f, 21);
			beep(f, 21);
			beep(f, 21);
			beep(aS, 128);
			beep(fH, 128);
			beep(dSH, 21);
			beep(dH, 21);
			beep(cH, 21);
			beep(aH, 128);
			beep(fH, 64);
			beep(dSH, 21);
			beep(dH, 21);
			beep(cH, 21);
			beep(aH, 128);
			beep(fH, 64);
			beep(dSH, 21);
			beep(dH, 21);
			beep(dSH, 21);
			beep(cH, 128);
			*/
	int melody2[] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};
	int beats2[]  = {  21,  21, 21,  128,  128,   21,  21,  21, 128, 64,  21,  21,  21, 128, 64,  21, 21,  21, 128 }; 
}

void ImperialMarch()
{
  for (int i=0; i<MAX_COUNT; i++) 
	{
    toneM = melody1[i];
    beat = beats1[i];
 
    duration = beat * tempo; // Set up timing
 
    playTone(); // A pause between notes
    delayMicroseconds(pause);
  }
}

void StarWarsTheme()
{
	
	for (int i=0; i<MAX_COUNT; i++) 
	{
    toneM = melody2[i];
    beat = beats2[i];
 
    duration = beat * tempo; // Set up timing
 
    beep(); // A pause between notes
    delayMicroseconds(pause);
   }
}
  