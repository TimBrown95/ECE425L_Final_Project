/**
 * @file Analog_Sensors.c
 * @brief Source code for the Analog_Sensors driver.
 *
 * This file contains the function definitions for the Analog_Sensors driver.
 * The ADC Module 0 is used to sample the potentiometer and the analog
 * light sensor that are connected on the EduBase board. The ADC module
 * is configured to sample the potentiometer first and the light sensor after.
 * After the light sensor is sampled, an interrupt signal is set to 
 * indicate that the sampling sequence has ended. After the conversion
 * results have been read from the corresponding FIFO, the interrupt is cleared.
 *
 * The following pins are used:
 *  - Potentiometer   <-->  Tiva LaunchPad Pin PE2 (Channel 1)
 *  - Light Sensor    <-->  Tiva LaunchPad Pin PE1 (Channel 2)
 *
 * @author Aaron Nanas
 *
 */

#include "Analog_Sensors.h"

void Analog_Sensors_Init(void)
{
	// Enable the clock to Port E by setting the
	// R4 bit (Bit 4) in the RCGCGPIO register
	SYSCTL->RCGCGPIO |= 0x10;
	
	// Configure the PE2 and PE1 pins as input
	// by clearing Bits 2 to 1 in the DIR register
	GPIOE->DIR &= ~0x06;
	
	// Disable the digital functionality for the PE2 and PE1 pins
	// by clearing Bits 2 to 1 in the DEN register
	GPIOE->DEN &= ~0x06;
	
	// Enable the analog functionality for the PE2 and PE1 pins
	// by setting Bits 2 to 1 in the AMSEL register
	GPIOE->AMSEL |= 0x06;
	
	// Select the alternate function for the PE2 (AIN1) and PE1 (AIN2) pins
	// by setting Bits 2 to 1 in the AFSEL register
	// Refer to Table 23-5 from the TM4C123GH6PM Microcontroller Datasheet
	// for a list of GPIO Pins and Alternate Functions
	GPIOE->AFSEL |= 0x06;

	// Enable the clock to the ADC Module 0 by setting the
	// R0 bit (Bit 0) in the RCGCADC register and provide
	// a short delay of 1 ms after enabling the clock
	SYSCTL->RCGCADC |= 0x01;
	SysTick_Delay1ms(1);
	
	// Disable the Sample Sequencer 0 by clearing the
	// ASEN0 bit (Bit 0) in the ACTSS register
	ADC0->ACTSS &= ~0x1;
	
	// Select the event (trigger) that initiates sampling for
	// the Sample Sequencer 0 by clearing all of the bits
	// in the EM0 field (Bits 3 to 0). This enables
	// Sample Sequencer 0 to sample whenever the SSn bit
	// in the PSSI register is set
	ADC0->EMUX &= ~0x000F;
	
	// Clear all of the bits (Bits 31 to 0) in the SSMUX0 register before configuration
	ADC0->SSMUX0 &= ~0xFFFFFFFF;
	
	// Choose Channel 1 for the first sample and Channel 2 for the second sample
	// by writing a value of 0x1 in the MUX0 field (Bits 3 to 0) 
	// and 0x02 in the MUX1 field (Bits 7 to 4) in the SSMUX0 register
	// In this configuration, the potentiometer will be sampled first,
	// and the light sensor will be sampled after
	ADC0->SSMUX0 |= 0x00000021;
	
	// Assign the second sample to be the end of the sampling sequence
	// by setting the END1 bit (Bit 5) in the SSCCTL0 register
	ADC0->SSCTL0 |= 0x00000020;
	
	// Enable the raw interrupt signal (IN0) by setting the IE1 bit (Bit 6)
	// in the SSCTL0 register. The IN0 interrupt signal will be triggered
	// at the end of the second sample's conversion
	ADC0->SSCTL0 |= 0x00000040;
	
	// Enable the Sample Sequencer 0 by setting the
	// ASEN0 bit (Bit 0) in the ACTSS register
	ADC0->ACTSS |= 0x1;
}

void Sample_Analog_Sensors(double analog_value_buffer[])
{
	// Begin sampling on the Sample Sequencer 0 module by setting the
	// SS0 bit (Bit 0) in the PSSI register. Note that the SS0 bit 
	// is a write-only bit, so it will be automatically cleared after setting it
	ADC0->PSSI |= 0x01;
	
	// Wait until an interrupt has occurred by reading the
	// SS0 raw interrupt status bit (INR0, Bit 0) in the RIS register
	// If INR0 is set to 1, then that indicates the end of the sampling sequence
	while ((ADC0->RIS & 0x01) == 0);
	
	// Read the conversion results for samples collected with the Sample Sequencer 0
	// module by reading the SSFIFO0 (Sample Sequence Result FIFO 0) register
	// The potentiometer will be sampled first and the light sensor will be sampled after
	uint32_t potentiometer_sample_result = ADC0->SSFIFO0;
	uint32_t light_sensor_sample_result = ADC0->SSFIFO0;
	
	// Clear the interrupt signal by setting the IN0 bit (Bit 0) in the ISC register.
	ADC0->ISC |= 0x01;
	
	// Calculate the analog voltage measured and store the results in a double array
	analog_value_buffer[0] = (potentiometer_sample_result * 3.3) / 4096;
	analog_value_buffer[1] = (light_sensor_sample_result * 3.3) / 4096;
}
