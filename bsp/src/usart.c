/*
 * usart.c
 *
 *  Created on: Jun 27, 2023
 *      Author: stage
 */


#include "usart.h"

void USART3_Console_Init(void) {
	/*
	 * PCLK1 @54MHz
	 * USART3 on pins PD8, PD9 (AF7)
	 * 9600 bauds
	 * 16x over-sampling
	 *
	 * USARTDIV = fCK / Baud = 54e6/9600 = 5625
	 *
	 * using RX interrupts
	 */

	// Enable GPIOD clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Set PD8, PD9 as AF7
	GPIOD->MODER &= ~(GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk);
	GPIOD->MODER |= (0x02 << GPIO_MODER_MODER8_Pos) | (0x02 << GPIO_MODER_MODER9_Pos);
	GPIOD->AFR[1] &= ~(GPIO_AFRH_AFRH0_Msk | GPIO_AFRH_AFRH1_Msk);
	GPIOD->AFR[1] |= (0x07 << GPIO_AFRH_AFRH0_Pos) | (0x07 << GPIO_AFRH_AFRH1_Pos);

	// Select PCLK1 @54MHz as clock source
	RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_USART3SEL_Msk;

	// Enable USART3 clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	// Reset USART3 configuration
	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;

	// Enable RX interrupt
	USART3->CR1 |= USART_CR1_RXNEIE;

	// Set baud rate
	USART3->BRR = (uint16_t)5625;

	// Enable RX and TX
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// Enable USART3
	USART3->CR1 |= USART_CR1_UE;
}
