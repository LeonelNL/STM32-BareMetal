/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Leonel Nieto
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved. 
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "globaldefine.h"

// Button PC13

int main(void)
{
  uint32_t cont = 0;
  uint32_t* p_ClockEnableAHB1    = (uint32_t *)(RCC_AHB1_BASE + RCC_AHB1_OFFSET);
  uint32_t* p_RegisterIDRGPIOC   = (uint32_t *)(GPIOC_BASE    + IDR_OFFSET);
  uint32_t* p_RegisterModerGPIOA = (uint32_t *)(GPIOA_BASE    + MODER_OFFSET);
  uint32_t* p_RegisterModerGPIOC = (uint32_t *)(GPIOC_BASE    + MODER_OFFSET);
  uint32_t* p_RegisterOdrGPIOA   = (uint32_t *)(GPIOA_BASE    + ODR_OFFSET);
  uint32_t* p_RegisterPUPDRGPIOC = (uint32_t *)(GPIOC_BASE    + PUPDR_OFFSET);

  *p_ClockEnableAHB1    |= 0x00000005;                                          // Enable clock GPIO port A and GPIO port C
  *p_RegisterModerGPIOA &= 0xFFFFF3FF;                                          // Ensure values start in 0
  *p_RegisterModerGPIOA |= 0x00000400;                                          // Set General purpose output mode in pin 5 (MODER5)
  *p_RegisterModerGPIOC &= 0xF3FFFFFF;                                          // Ensure values start in 0 and set pin to Input
  *p_RegisterPUPDRGPIOC &= 0xF3FFFFFF;                                          // Ensure values start in 0
  *p_RegisterPUPDRGPIOC |= 0x04000000;                                          // Set the button pull up


  while(1)
  {
    if (*p_RegisterIDRGPIOC != 0x00002000)                                      // Verify if bit is ON (pull up button)
    {
      *p_RegisterOdrGPIOA |=  0x00000020;									                      // Set pin 5 on ON (ODR5)
    }
    else                                                                         // If bit button is OFF
    {
      *p_RegisterOdrGPIOA &= ~(0x00000020);									                    // Set pin 5 on OFF (ODR5)
    }
  }
}