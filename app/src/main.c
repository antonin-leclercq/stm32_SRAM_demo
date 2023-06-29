/*
 * main.c
 *
 *  Created on: Jun 27, 2023
 *      Author: stage
 */

#include "main.h"

static void SystemClock_Config108(void);

// Declared in stm32f7xx_it.c
extern Menu_Level level;
extern SRAM_Tester_t tester;
extern uint8_t wait_for_input;

int main(void) {
	SystemClock_Config108();
	FMC_SRAM_Init();
	USART3_Console_Init();
	SRAM_Timer_Init();

	level = ROOT;
	wait_for_input = 1;

	smallprintf("SRAM memory tester\r\n");

	// Set tester to default values:
	tester.mode = 0; 		// Read
	tester.size = 256; 		// 256 bytes
	tester.start = 0; 		// SRAM start, not including bank 1 offset
	tester.test = 0; 		// Don't test

	print_menu(&tester);

	NVIC_Init();

	while(1)  {

		if (wait_for_input == 1) continue;

		switch (level) {
		case ROOT:
			print_menu(&tester);
			wait_for_input = 1;
			break;
		case SIZE:
			smallprintf("\nEnter size (in bytes): ");
			wait_for_input = 1;
			break;
		case ADDRESS:
			smallprintf("\nEnter address start (in decimal): ");
			wait_for_input = 1;
			break;
		case MODE:
			smallprintf("\nEnter mode (r for Read / w for Write):  ");
			wait_for_input = 1;
			break;
		case TEST:
			smallprintf("\nTesting RAM...\r\n");

			// Disable USART3 interruptions
			NVIC_DisableIRQ(USART3_IRQn);

			test_sram(&tester);

			// Enable USART3 interruptions
			NVIC_EnableIRQ(USART3_IRQn);

			level = ROOT;
			break;
		default:
			break;
		}
	}
}

static void SystemClock_Config108(void) {

	// SYSCLK @ 108MHz
	// PLLM = 4, PLLN = 216, PLLP = 4, PLLQ = 9
	// AHBPRE = /1, APB2PRE = /1, APB1PRE = /2

	uint32_t HSE_timeout = 100000;
	uint32_t PLL_timeout = 100000;
	uint32_t SW_timeout = 100000;

	// HSE bypass, turn on
	RCC->CR |= RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;

	while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY && HSE_timeout-- > 0);

	// PLLQ = 9
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_Msk;
	RCC->PLLCFGR |= (0x09 << RCC_PLLCFGR_PLLQ_Pos);

	// PLLP = 4
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;
	RCC->PLLCFGR |= (0x01 << RCC_PLLCFGR_PLLP_Pos);

	// PLLN = 216
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |= (216 << RCC_PLLCFGR_PLLN_Pos);

	// PLLM = 4
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |= (0x04 << RCC_PLLCFGR_PLLM_Pos);

	// Select PLL source (HSE)
	RCC->PLLCFGR |= (0x01 << RCC_PLLCFGR_PLLSRC_Pos);

	// Turn on PLL
	RCC->CR |= RCC_CR_PLLON;

	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY && PLL_timeout-- > 0);

	// Set AHBPRE, APB2PRE to /1 (default), APB1PRE to /2
	RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_PPRE2_Msk | RCC_CFGR_PPRE1_Msk);
	RCC->CFGR |= (0x04 << RCC_CFGR_PPRE1_Pos);

	// Configure flash latency for 108MHz and enable instruction pre-fetch
	FLASH->ACR |= FLASH_ACR_PRFTEN | (0x03 << FLASH_ACR_LATENCY_Pos);

	// Select PLL as system clock
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= (0x02 << RCC_CFGR_SW_Pos);

	while ((RCC->CFGR & RCC_CFGR_SWS) != (0x02 << RCC_CFGR_SWS_Pos) && SW_timeout-- > 0);

	// Update global variables
	SystemCoreClockUpdate();
}


void print_menu(const SRAM_Tester_t* tester) {
	smallprintf("\r\nEnter one of the following letters:\r\n");
	smallprintf("\tS or s - set size (current = %u byte(s))\r\n", tester->size);
	smallprintf("\tA or a - set SRAM address start (current = 0x%X)\r\n", tester->start);
	smallprintf("\tM or m - perform a read / write operation (current = %s)\r\n", (tester->mode == 0) ? "Read" : "Write" );
	smallprintf("\tT or t - test the SRAM with current settings\r\n");
}

void NVIC_Init(void) {
	NVIC_SetPriority(USART3_IRQn, 25);
	NVIC_EnableIRQ(USART3_IRQn);
}

void SRAM_Timer_Init(void) {
	/*
	 * Timer 6 running at 108MHz
	 * 1us resolution (measure up to 65ms)
	 */

	// Enable Timer 6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	// Reset timer 6 configuration
	TIM6->CR1 = 0x0000;
	TIM6->CR2 = 0x0000;
	TIM6->ARR = (uint16_t)0xFFFF;

	// Enable auto-reload
	TIM6->CR1 |= TIM_CR1_ARPE;

	// Set pre-scaler for 1MHz counting frequency
	TIM6->PSC = (uint16_t)108 -1;

	// Make sure that counter is disabled
	TIM6->CR1 &= ~TIM_CR1_CEN;
}

#define COPY_VALUE 0x55

void test_sram(const SRAM_Tester_t* tester) {

	uint8_t sram_read = 0;
	uint16_t cnt = 0;

	// Reset TIM6 counter
	TIM6->EGR |= TIM_EGR_UG;

	if (tester->mode == 0) {

		// Start counting
		TIM6->CR1 |= TIM_CR1_CEN;

		for (uint32_t i = 0; i < tester->size; i++) {
			sram_read = (uint8_t) *(volatile uint32_t*)(BANK1_ADDR_START + tester->start + i);
		}

		// Get counter value
		cnt = TIM6->CNT;

		// Stop counting
		TIM6->CR1 &= ~TIM_CR1_CEN;

		smallprintf("last sram_read = %u\r\n", sram_read);
	}

	else if (tester->mode == 1) {

		// Start counting
		TIM6->CR1 |= TIM_CR1_CEN;

		for (uint32_t i = 0; i < tester->size; i++) {
			*(volatile uint32_t*)(BANK1_ADDR_START + tester->start + i) = (uint8_t)COPY_VALUE;
		}

		// Get counter value
		cnt = TIM6->CNT;

		// Stop counting
		TIM6->CR1 &= ~TIM_CR1_CEN;

	}

	smallprintf("Done : took %u us\r\n", cnt);
}
