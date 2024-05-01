/**
 * @file Timer_0A_PWM.c
 *
 * @brief Source file for the Timer_0A_PWM driver.
 *
 * This file contains the function definitions for the Timer_0A_PWM driver.
 * It uses the Timer 0A module to generate PWM signals.
 *
 * @note This driver assumes that the system clock's frequency is 50 MHz.
 *
 * @author Aaron Nanas
 */

#include "Timer_0A_PWM.h"

void Timer_0A_PWM_Init(uint32_t period_constant, uint32_t duty_cycle)
{	
	if (duty_cycle >= period_constant) return;
	
	// Enable the clock to Timer 0A by setting the
	// R0 bit (Bit 0) in the RCGCTIMER register
	SYSCTL->RCGCTIMER |=  0x01;
	
	// Enable the clock to GPIO Port B by setting the
	// R1 bit (Bit 1) in the RCGCGPIO register
	SYSCTL->RCGCGPIO |= 0x02;
	
	while((SYSCTL->PRGPIO & 0x00002) == 0);
	
	// Configure the PB6 pin to use the alternate function (T0CCP0)
	// by setting Bit 6 in the AFSEL register
	GPIOB->AFSEL |= 0x40;
	
	// Clear the PMC6 field (Bits 27 to 24) in the PCTL register
	GPIOB->PCTL &= ~0xF0FFFFFF;
	
	// Configure the PB6 pin to operate as a Timer 0A pin (T0CCP0)
	// by writing 0x7 to the PMC6 field (Bits 27 to 24) in the PCTL register
	// The 0x7 value is derived from Table 10-2 in the TM4C123G Microcontroller Datasheet
	GPIOB->PCTL |= 0x07000000;
	
	// Enable the digital functionality for the PB6 pin
	// by setting Bit 6 in the DEN register
	GPIOB->DEN |= 0x40;

	// Clear the TAEN bit (Bit 0) of the GPTMCTL register
	// to disable Timer 0A
	TIMER0->CTL &= ~0x01;
	
	// Set the bits of the GPTMCFG field (Bits 2 to 0) in the GPTMCFG register
	// 0x4 = Select the 16-bit timer configuration
	TIMER0->CFG |= 0x04;
		
	// Set the bits of the TAMR field (Bits 1 to 0) to enable Periodic Timer mode
	// and set the TAAMS bit (Bit 3) to enable PWM mode in the GPTMTAMR register
	// TAMR = 0x2 will enable Periodic Timer mode
	TIMER0->TAMR |= 0x0A;
	
	// Clear the bits of the TAPSR field (Bits 7 to 0) in the
	// GPTMTAPR register before setting the prescale value
	//TIMER0->TAPR &= ~0x000000FF;
	
	// Set the prescale value to 50 by setting the bits of the 
	// TAPSR field (Bits 7 to 0) in the GPTMTAPR register
	// New timer clock frequency = (50 MHz / 50) = 1 MHz
	//TIMER0->TAPR = 5;
	
	// Set the period by writing to the
	// TAILR field (Bits 31 to 0) in the GPTMTAILR register
	TIMER0->TAILR = (period_constant - 1);
	
	// Set the duty cycle by writing to the
	// TAMR feild (Bits 31 to 0) in the GPTMTAMATCHR register
	TIMER0->TAMATCHR = (period_constant - duty_cycle - 1);
	
	// Set the TAEN bit (Bit 0) in the GPTMCTL register to enable Timer 0A
	TIMER0->CTL |= 0x01;
}

void Timer_0A_Update_PWM_Duty_Cycle(uint16_t duty_cycle)
{
	// Set the duty cycle by writing to the
	// TAMR feild (Bits 31 to 0) in the GPTMTAMATCHR register
	TIMER0->TAMATCHR = (duty_cycle - 1);
}
