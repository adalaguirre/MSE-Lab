/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Steven McClellan
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f4xx.h"
// Define base address and registers for RCC
#define RCC_BASE 				(0x40023800UL)
#define RCC_AHB1ENR 			(*(volatile unsigned int *)(RCC_BASE + RRC_AHB1ENR_OFFSET))
#define RRC_AHB1ENR_OFFSET 		0x30UL
// Define base address and registers for GPIOA
#define GPIOA_BASE 				(0x40020000UL)
#define GPIOA_ODDR 				(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_ODDR_OFFSET))
#define GPIOA_MODER 			(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_MODER_OFFSET))
#define GPIOA_ENR 				(1 << 0)
#define GPIOA_MODER5N 			(1 << 10)
#define GPIOA_MODER5F 			~(1 << 11)
#define GPIOA_MODER_OFFSET 		0x00UL
#define GPIOA_ODDR_OFFSET 		0x14UL
// Define values for Register manipulation
#define GPIOAEN					0
#define CLK_EN					1U
#define GPIO5 					5
#define MODER5					(2 * GPIO5)
#define MODE_OUTPUT				1U
#define HIGH					1UL
#define LOW						0U
#define DEBOUNCE_LIST			3U

int main(void)
{
	RCC_AHB1ENR |= (1U << 0);
	/* GPIO Mode Output: 0x01 --> Update Bit 10 and 11 to configure GPIOA pin 5*/
	GPIOA_MODER |= (1U << 10);
	GPIOA_MODER &= ~(1U << 11);


    /* Loop forever */
	while(1){

		GPIOA_ODDR ^= (1U << 5);

		for (unsigned int i = 0 ; i < 800000 ; i++){

			RCC -> 
		}

	}
}
