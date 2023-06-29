/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f7xx.h"
#include "fmc.h"
#include "usart.h"

#define BANK1_ADDR_START 0x60000000

typedef struct {
	uint32_t size;
	uint32_t start;
	uint8_t mode;
	uint8_t test;
} SRAM_Tester_t ;

typedef enum {
	ROOT,
	SIZE,
	ADDRESS,
	MODE,
	TEST
} Menu_Level;

extern int smallprintf(const char *format, ...);
extern int smallsprintf(char *out, const char *format, ...);

void print_menu(const SRAM_Tester_t* tester);

void NVIC_Init(void);

void test_sram(const SRAM_Tester_t* tester);

void SRAM_Timer_Init(void);


#endif /* __MAIN_H */

