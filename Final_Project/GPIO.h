
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"

// Constant definitions for the user LED (RGB) colors
extern const uint8_t RGB_LED_OFF;
extern const uint8_t RGB_LED_RED;
extern const uint8_t RGB_LED_BLUE;
extern const uint8_t RGB_LED_GREEN;

// Constant definitions for the EduBase board LEDs
extern const uint8_t EDUBASE_LED_ALL_OFF;
extern const uint8_t EDUBASE_LED_ALL_ON;



void EduBase_Button_Init(void);

/**
 * @brief The Get_EduBase_Button_Status reads the status of the EduBase Board buttons (SW2 - SW5) and returns it.
 *
 * This function reads the status of the EduBase Board buttons connected to pins PD0, PD1, PD2, and PD3.
 * It indicates whether or not the buttons are pressed and returns the status.
 * A bitwise AND operation (& 0xF) is performed to mask the unused bits in the data register.
 *
 * @param None
 *
 * @return Indicates the status of the buttons. 
 *
 * For example:
 *  - 0x00: No buttons are pressed
 *  - 0x01: SW5 is pressed
 *  - 0x02: SW4 is pressed
 *  - 0x04: SW3 is pressed
 *  - 0x08: SW2 is pressed
 */
uint8_t Get_EduBase_Button_Status(void);

/**
 * @brief The LED_Pattern_1 function sets the output of the RGB LED and the EduBase Board LEDs.
 *
 * This function sets the output of both the RGB LED (PF1 - PF3) and the EduBase Board LEDs (PB0 - PB3).
 * All of the EduBase Board LEDs will be on and the RGB LED will display a red color.
 *
 * @param None
 *
 * @return None
 */

uint32_t Change_Counter_Speed(void);
