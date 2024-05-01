/**
 * @file Analog_Sensors.h
 * @brief Header file for the Analog_Sensors driver.
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

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"

/**
 * @brief Initializes the potentiometer and the analog light sensor on the EduBase board.
 *
 * This function initializes the potentiometer and the analog light sensor that are
 * connected on the EduBase board. It enables analog functionality for the PE2 and PE1
 * pins, enables the clock to the ADC module used, configures the corresponding
 * sample sequencer, and initiates the ADC module for sampling. The potentiometer (Channel 1)
 * will be sampled first, and then the light sensor (Channel 2) will be sampled after.
 *
 * The following pins are used:
 *  - Potentiometer   <-->  Tiva LaunchPad Pin PE2 (Channel 1)
 *  - Light Sensor    <-->  Tiva LaunchPad Pin PE1 (Channel 2)
 *
 * @param None
 *
 * @return None
 */
void Analog_Sensors_Init(void);

/**
 * @brief Stores the sampled results of the potentiometer and the analog light sensors in a buffer.
 *
 * This function initiates the sampling process for the potentiometer and the analog light sensor. 
 * It initiates Sample Sequencer 0 to begin sampling, waits until an interrupt has occurred,
 * and reads the conversion results from the FIFO. Then, the analog measured voltage values are
 * calculated and the results are stored in a double array which is provided as an argument.
 *
 * @param analog_value_buffer A double array to store the analog sensor readings.
 *
 * @return None
*/
void Sample_Analog_Sensors(double analog_value_buffer[]);
