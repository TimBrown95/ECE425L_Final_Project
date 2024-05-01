/**
 * @file Timer_0A_PWM.h
 *
 * @brief Header file for the Timer_0A_PWM driver.
 *
 * This file contains the function definitions for the Timer_0A_PWM driver.
 * It uses the Timer 0A module to generate PWM signals.
 *
 * @note This driver assumes that the system clock's frequency is 50 MHz.
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"

void Timer_0A_PWM_Init(uint32_t period_constant, uint32_t duty_cycle);

void Timer_0A_Update_PWM_Duty_Cycle(uint16_t duty_cycle);
