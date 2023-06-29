/**
  ******************************************************************************
  * @file    Templates/Src/stm32f7xx.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
   
/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

#define CARRIAGE_RETURN 0x0D
#define BUFFER_MAX 16

char c = 0;
char numberBuffer[BUFFER_MAX];
uint8_t buffer_index = 0;
uint8_t wait_for_input;


Menu_Level level;
SRAM_Tester_t tester;

uint32_t atoi(const char* a, uint8_t len)  {
	uint32_t res = 0;
	for (uint8_t i = 0; i < len; i++)
		res = (res * 10) + (a[i] - '0');
	return res;
}

void USART3_IRQHandler(void) {

	c = (char)USART3->RDR;

	switch (level) {

	case ROOT:
		wait_for_input = 0;
		if (c == 's' || c == 'S') { level = SIZE; 		break; }
		if (c == 'a' || c == 'A') { level = ADDRESS; 	break; }
		if (c == 'm' || c == 'M') { level = MODE; 		break; }
		if (c == 't' || c == 'T') { level = TEST; 		break; }
		break;

	case MODE:
		wait_for_input = 0;
		if (c == 'r' || c == 'R') { tester.mode = 0; level = ROOT; break; }
		if (c == 'w' || c == 'W') { tester.mode = 1; level = ROOT; break; }
		break;

	case ADDRESS:
		if (c == CARRIAGE_RETURN) {
			level = ROOT;
			tester.start = atoi(numberBuffer, buffer_index);
			buffer_index = 0;
			wait_for_input = 0;
			break;
		}
		numberBuffer[buffer_index++] = c;
		if (buffer_index == BUFFER_MAX -1) {
			buffer_index = 0;
		}
		break;

	case SIZE:
		if (c == CARRIAGE_RETURN) {
			level = ROOT;
			tester.size = atoi(numberBuffer, buffer_index);
			buffer_index = 0;
			wait_for_input = 0;
			break;
		}
		numberBuffer[buffer_index++] = c;
		if (buffer_index == BUFFER_MAX -1) {
			buffer_index = 0;
		}
		break;

	default:
		break;
	}

	// Echo
	while((USART3->ISR & USART_ISR_TC) != USART_ISR_TC);
	USART3->TDR = c;

}

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 

/**
  * @}
  */

