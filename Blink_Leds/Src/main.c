/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Leonel Nieto
 * @brief          : Program to blink a led using bare metal
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

#define RCC_BASE 	   0x40023800
#define RCC_OFFSET   0x30
#define GPIOA_BASE   0x40020000
#define MODER_OFFSET 0x00
#define ODR_OFFSET	 0x14

int main(void)
{
  uint32_t cont = 0;
  uint32_t *p_ClockEnableGPIOA   = (uint32_t *)(RCC_BASE + RCC_OFFSET);
  uint32_t *p_RegisterModerGPIOA = (uint32_t *)(GPIOA_BASE + MODER_OFFSET);
  uint32_t *p_RegisterOdrGPIOA   = (uint32_t *)(GPIOA_BASE + ODR_OFFSET);

  *p_ClockEnableGPIOA   |= 0x00000001;                                          // Enable clock GPIO port A
  *p_RegisterModerGPIOA &= 0xFFFFF3FF;                                          // Ensure values start in 0
  *p_RegisterModerGPIOA |= 0x00000400;                                          // Set General purpose output mode in pin 5 (MODER5)
  
	while(1)
  {
    *p_RegisterOdrGPIOA   |=   0x00000020;									                    // Set pin 5 on ON (ODR5)
    for(cont = 0; cont < 500000; cont++);
    *p_RegisterOdrGPIOA   &= ~(0x00000020);									                    // Set pin 5 on OFF (ODR5)
    for(cont = 0; cont < 500000; cont++);
	}
}