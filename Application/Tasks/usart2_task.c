/********************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************
 *********************************************************************
 * File Name    : usart2_task.c
 * Version      :
 * Description  :
 * Creation Date: Nov 30, 2022
 * Author		: KarimHmidi
 *********************************************************************/

/*
 *
 * Includes
 *
 *********************************************************************/
#include "cmsis_os.h"
#include "tasks_defs.h"

//WR
/* #include "typedefs.h" */
#include "../Common/typedefs.h"

#include "lwip/udp.h"
#include <string.h>

/*
 *
 * Defines
 *
 **********************************************************************/

/*
 *
 * Variable defines
 *
 **********************************************************************/

osThreadId_t usart2TaskHandle;
const osThreadAttr_t usart2Task_attributes = {
  .name = "usart2Task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

extern UART_HandleTypeDef huart2;
uint8_t USART2_TxData[5] = {0};
HAL_StatusTypeDef st = HAL_OK;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * @brief  Function implementing the usart2Task thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void usart2Task(void *argument)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500UL);

//	uint8_t Test[20] = "Hello World !!!\r\n"; //Data to send

	for (;;)
	{
		USART2_TxData[0]++;

		st = HAL_UART_Transmit(&huart2, &USART2_TxData[0], sizeof USART2_TxData[0], 10);

		osDelay(xDelay500ms);
	}
}
