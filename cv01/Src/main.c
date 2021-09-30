/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f0xx.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	uint32_t sos = 0b10101001110111011100101010000000;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;

	//while(1)
	//{
	//	GPIOA->BSRR = (1<<5);
	//	for (volatile uint32_t i = 0; i < 100000; i++) {}
	//	GPIOA->BRR = (1<<5);
	//	for (volatile uint32_t i = 0; i < 100000; i++) {}

	//}

   for(;;){
    	for(uint32_t i= 0; i<32; i++)
    	{
    		if (sos & (1<<(31-i))){
    			GPIOA->BSRR = (1<<5);
    		}
    		else{

    			GPIOA->BRR = (1<<5);
    		}

    		for (volatile uint32_t i = 0; i < 100000; i++) {}
    	}




    }






}