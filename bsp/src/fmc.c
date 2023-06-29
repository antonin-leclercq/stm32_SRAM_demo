/*
 * fmc.c
 *
 *  Created on: Jun 27, 2023
 *      Author: stage
 */


#include "fmc.h"

void FMC_SRAM_Init(void) {
/*
 * Using FM28V020-SG FRAM (SRAM compatible) memory:
 * - 32k x 8 array (256k total)
 * - 15 address lines
 * - 8 data lines
 * - asynchronous access
 * - Address hold time = 70ns => address hold phase duration = 70e9/(1/HCLK) = 8 (@108MHz)
 * - Data setup time = 0ns
 *
 * FMC memory bank 1 device number 1, starting at address 0x60000000
 * FMC BCR1 = BTCR[0]
 * FMC BTR1 = BTCR[4]
 *
 * Data lines pin assignment
	 * FMC_D0: pin PD14
	 * FMC_D1: pin PD15
	 * FMC_D2: pin PD0
	 * FMC_D3: pin PD1
	 * FMC_D4: pin PE7
	 * FMC_D5: pin PE8
	 * FMC_D6: pin PE9
	 * FMC_D7: pin PE10
 *
 * Address lines pin assignment
	 * FMC_A0: pin PF0
	 * FMC_A1: pin PF1
	 * FMC_A2: pin PF2
	 * FMC_A3: pin PF3
	 * FMC_A4: pin PF4
	 * FMC_A5: pin PF5 #
	 *
	 * FMC_A6: pin PF12
	 * FMC_A7: pin PF13
	 * FMC_A8: pin PF14
	 * FMC_A9: pin PF15
	 * FMC_A10: pin PG0
	 * FMC_A11: pin PG1
	 * FMC_A12: pin PG2
	 * FMC_A13: pin PG3
	 * FMC_A14: pin PG4 #
 *
 * Write Enable (WE): pin PD5 (NWE)
 * Output Enable (OE): pin PD4 (NOE)
 * Chip Enable (CE): pin PD7 (NE1 <=> chip select 1)
 *
 *
 *
 */

	// Enable GPIOD, GPIOE, GPIOF, GPIOG
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN;

	// Set all FMC pins as alternate function 12

	// PD0, PD1, PD14, PD15
	GPIOD->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk | GPIO_MODER_MODER14_Msk | GPIO_MODER_MODER15_Msk);
	GPIOD->MODER |= (0x02 << GPIO_MODER_MODER0_Pos) | (0x02 << GPIO_MODER_MODER1_Pos) | (0x02 << GPIO_MODER_MODER14_Pos) | (0x02 << GPIO_MODER_MODER15_Pos);
	GPIOD->AFR[0] &= ~(GPIO_AFRL_AFRL0_Msk | GPIO_AFRL_AFRL1_Msk);
	GPIOD->AFR[0] |= (0x0C << GPIO_AFRL_AFRL0_Pos) | (0x0C << GPIO_AFRL_AFRL1_Pos);
	GPIOD->AFR[1] &= ~(GPIO_AFRH_AFRH6_Msk | GPIO_AFRH_AFRH7_Msk);
	GPIOD->AFR[1] |= (0x0C << GPIO_AFRH_AFRH6_Pos) | (0x0C << GPIO_AFRH_AFRH7_Pos);

	// PE7, PE8, PE9, PE10
	GPIOE->MODER &= ~(GPIO_MODER_MODER7_Msk | GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER10_Msk);
	GPIOE->MODER |= (0x02 << GPIO_MODER_MODER7_Pos) | (0x02 << GPIO_MODER_MODER8_Pos) | (0x02 << GPIO_MODER_MODER9_Pos) | (0x02 << GPIO_MODER_MODER10_Pos);
	GPIOE->AFR[0] &= ~GPIO_AFRL_AFRL7_Msk;
	GPIOE->AFR[0] |= (0x0C << GPIO_AFRL_AFRL7_Pos);
	GPIOE->AFR[1] &= ~(GPIO_AFRH_AFRH0_Msk | GPIO_AFRH_AFRH1_Msk | GPIO_AFRH_AFRH2_Msk);
	GPIOE->AFR[1] |= (0x0C << GPIO_AFRH_AFRH0_Pos) | (0x0C << GPIO_AFRH_AFRH1_Pos) | (0x0C << GPIO_AFRH_AFRH2_Pos);

	// PF0, PF1, PF2, PF3, PF4, PF5, PF12, PF13, PF14, PF15
	GPIOF->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk | GPIO_MODER_MODER2_Msk | GPIO_MODER_MODER3_Msk | GPIO_MODER_MODER4_Msk |
			GPIO_MODER_MODER5_Msk | GPIO_MODER_MODER12_Msk | GPIO_MODER_MODER13_Msk | GPIO_MODER_MODER14_Msk | GPIO_MODER_MODER15_Msk);
	GPIOF->MODER |= (0x02 << GPIO_MODER_MODER0_Pos) | (0x02 << GPIO_MODER_MODER1_Pos) | (0x02 << GPIO_MODER_MODER2_Pos) | (0x02 << GPIO_MODER_MODER3_Pos) | (0x02 << GPIO_MODER_MODER4_Pos) |
			(0x02 << GPIO_MODER_MODER5_Pos) | (0x02 << GPIO_MODER_MODER12_Pos) | (0x02 << GPIO_MODER_MODER13_Pos) | (0x02 << GPIO_MODER_MODER14_Pos) | (0x02 << GPIO_MODER_MODER15_Pos);
	GPIOF->AFR[0] &= ~(GPIO_AFRL_AFRL0_Msk | GPIO_AFRL_AFRL1_Msk | GPIO_AFRL_AFRL2_Msk | GPIO_AFRL_AFRL3_Msk | GPIO_AFRL_AFRL4_Msk | GPIO_AFRL_AFRL5_Msk);
	GPIOF->AFR[0] |= (0x0C << GPIO_AFRL_AFRL0_Pos) | (0x0C << GPIO_AFRL_AFRL1_Pos) | (0x0C << GPIO_AFRL_AFRL2_Pos) | (0x0C << GPIO_AFRL_AFRL3_Pos) | (0x0C << GPIO_AFRL_AFRL4_Pos) | (0x0C << GPIO_AFRL_AFRL5_Pos);
	GPIOF->AFR[1] &= ~(GPIO_AFRH_AFRH4_Msk | GPIO_AFRH_AFRH5_Msk | GPIO_AFRH_AFRH6_Msk | GPIO_AFRH_AFRH7_Msk);
	GPIOF->AFR[1] |= (0x0C << GPIO_AFRH_AFRH4_Pos) | (0x0C << GPIO_AFRH_AFRH5_Pos) | (0x0C << GPIO_AFRH_AFRH6_Pos) | (0x0C << GPIO_AFRH_AFRH7_Pos);

	// PG0, PG1, PG2, PG3, PG4
	GPIOG->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk |  GPIO_MODER_MODER2_Msk | GPIO_MODER_MODER3_Msk | GPIO_MODER_MODER4_Msk);
	GPIOG->MODER |= (0x02 << GPIO_MODER_MODER0_Pos) | (0x02 << GPIO_MODER_MODER1_Pos) | (0x02 << GPIO_MODER_MODER2_Pos) | (0x02 << GPIO_MODER_MODER3_Pos) | (0x02 << GPIO_MODER_MODER4_Pos);
	GPIOG->AFR[0] &= ~(GPIO_AFRL_AFRL0_Msk | GPIO_AFRL_AFRL1_Msk | GPIO_AFRL_AFRL2_Msk | GPIO_AFRL_AFRL3_Msk | GPIO_AFRL_AFRL4_Msk);
	GPIOG->AFR[0] |= (0x0C << GPIO_AFRL_AFRL0_Pos) | (0x0C << GPIO_AFRL_AFRL1_Pos) | (0x0C << GPIO_AFRL_AFRL2_Pos) | (0x0C << GPIO_AFRL_AFRL3_Pos) | (0x0C << GPIO_AFRL_AFRL4_Pos);

	// PD4, PD5, PD7
	GPIOD->MODER &= ~(GPIO_MODER_MODER4_Msk | GPIO_MODER_MODER5_Msk  | GPIO_MODER_MODER7_Msk);
	GPIOD->MODER |= (0x02 << GPIO_MODER_MODER4_Pos) | (0x02 << GPIO_MODER_MODER5_Pos) | (0x02 << GPIO_MODER_MODER7_Pos);
	GPIOD->AFR[0] &= ~(GPIO_AFRL_AFRL4_Msk | GPIO_AFRL_AFRL5_Msk | GPIO_AFRL_AFRL7_Msk);
	GPIOD->AFR[0] |= (0x0C << GPIO_AFRL_AFRL4_Pos) | (0x0C << GPIO_AFRL_AFRL5_Pos) | (0x0C << GPIO_AFRL_AFRL7_Pos);

	// Enable FMC clock
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;

	// Reset Bank 1, device number 1
	FMC_Bank1->BTCR[0] = 0x000030DB;
	FMC_Bank1->BTCR[4] = 0x0FFFFFFF;
	FMC_Bank1E->BWTR[0] = 0x0FFFFFFF;

	// Disable NOR flash memory access
	FMC_Bank1->BTCR[0] &= ~FMC_BCR1_FACCEN_Msk;

	// Set memory width to 8 bits
	FMC_Bank1->BTCR[0] &= ~FMC_BCR1_MWID_Msk;

	// Select SRAM memory type
	FMC_Bank1->BTCR[0] &= ~FMC_BCR1_MTYP_Msk;

	// Disable Address/data multiplexing
	FMC_Bank1->BTCR[0] &= ~FMC_BCR1_MUXEN_Msk;

	// Enable Bank 1
	FMC_Bank1->BTCR[0] |= FMC_BCR1_MBKEN;
}
