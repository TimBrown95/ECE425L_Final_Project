/**
 * @file Timer_1A_Interrupt.c
 *
 * @brief Source code for the Timer_1A_Interrupt driver.
 *
 * This file contains the function definitions for the Timer_1A_Interrupt driver.
 * It uses the Timer 1A module to generate periodic interrupts.
 *
 * @note Timer 1A has been configured to generate periodic interrupts every 1 ms
 * for the Timers lab.
 *
 * @note This driver assumes that the system clock's frequency is 50 MHz.
 * 
 * @note Refer to Table 2-9 (Interrupts) on pages 104 - 106 from the TM4C123G Microcontroller Datasheet
 * to view the Vector Number, Interrupt Request (IRQ) Number, and the Vector Address
 * for each peripheral.
 *
 * @author Aaron Nanas
 */

#include "Timer_1A_Interrupt.h"

// Declare pointer to the user-defined task
void (*Timer_1A_Task)(void);

void Timer_1A_Interrupt_Init(void(*task)(void))
{
	// Store the user-defined task function for use during interrupt handling
	Timer_1A_Task = task;
	
	// Set the R1 bit (Bit 1) in the RCGCTIMER register
	// to enable the clock for Timer 1A
	SYSCTL->RCGCTIMER |=  0x02;
	
	// Clear the TAEN bit (Bit 0) of the GPTMCTL register
	// to disable Timer 1A
	TIMER1->CTL &= ~0x01;
	
	// Set the bits of the GPTMCFG field (Bits 2 to 0) in the GPTMCFG register
	// 0x4 = Select the 16-bit timer configuration
	TIMER1->CFG |= 0x04;
	
	// Set the bits of the TAMR field (Bits 1 to 0) to enable 
	// Periodic Timer mode in the GPTMTAMR register
	// Writing TAMR = 0x2 will enable Periodic Timer mode
	TIMER1->TAMR |= 0x02;
	
	// Clear the bits of the TAPSR field (Bits 7 to 0) in the
	// GPTMTAPR register before setting the prescale value
	TIMER1->TAPR &= ~0x000000FF;
	
	// Set the prescale value to 50 by setting the bits of the 
	// TAPSR field (Bits 7 to 0) in the GPTMTAPR register
	// New timer clock frequency = (50 MHz / 50) = 1 MHz
	TIMER1->TAPR |= 50;
	
	// Set the timer interval load value by writing to the
	// TAILR field (Bits 31 to 0) in the GPTMTAILR register
	// (1 us * 1000) = 1 ms
	// Timer 1A Resolution: 1 ms
	TIMER1->TAILR = (1000 - 1);
	
	// Set the TATOCINT bit (Bit 0) to 1 in the GPTMICR register
	// The TATOCINT bit will be automatically cleared when it is set to 1
	TIMER1->ICR |= 0x01;
	
	// Enable the Timer 1A interrupt by setting the TATOIM bit (Bit 0)
	// in the GPTMIMR register
	TIMER1->IMR |= 0x01;
	
	// Set the priority level to 1 for the Timer 1A interrupt
	// In the Interrupt 20-23 Priority (PRI5) register,
	// the INTB field (Bits 15 to 13) corresponds to Interrupt Request (IRQ) 21
	// Timer 1A has an IRQ of 21
	NVIC->IP[5] = (NVIC->IP[5] & 0xFFFF00FF) | (1 << 13);
	
	// Enable IRQ 21 for Timer 1A by setting Bit 21 in the ISER[0] register
	NVIC->ISER[0] |= (1 << 21);
	
	// Set the TAEN bit (Bit 0) in the GPTMCTL register to enable Timer 1A
	TIMER1->CTL |= 0x01;
}

void TIMER1A_Handler(void)
{
	// Read the Timer 1A time-out interrupt flag
	if (TIMER1->MIS & 0x01)
	{
		// Execute the user-defined function
		(*Timer_1A_Task)();
		
		// Acknowledge the Timer 1A interrupt and clear it
		TIMER1->ICR |= 0x01;
	}
}
