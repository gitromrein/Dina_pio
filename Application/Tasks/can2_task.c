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
 * File Name    : can2_task.c
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

#include "stm32h7xx.h"
#include "stm32h7xx_hal_fdcan.h"
#include <stdio.h>
#include <string.h>

/*
 *
 * Defines
 *
 **********************************************************************/
#define CAN_ZMV_SIMULATION 0



/*
 *
 * Variable defines
 *
 **********************************************************************/

osThreadId_t can2TaskHandle;
const osThreadAttr_t can2Task_attributes = {
  .name = "can2Task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

extern FDCAN_HandleTypeDef hfdcan2;
extern FBV_ZOMBIE_U fbv_webs;
FDCAN_FilterTypeDef sFilterConfig_2 = {};
FDCAN_TxHeaderTypeDef TxHeader_2 = {};
FDCAN_RxHeaderTypeDef RxHeader_2 = {};
uint8_t TxData_2[8] = {0};
uint8_t RxData_2[8] = {0};
uint32_t RxMsgerror_2 = 0;
uint32_t TxMsgerror_2 = 0;
uint32_t TxID = 0x788;
uint8_t begin_tx_flg = 0;

ZMV_CAN_FRAME_Rx_U zmv_can2_rx = {}; // Can interface data buffer



/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * CAN2 Rx Callback
  *
  *
  ********************************************************************/

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
	if(RESET != (RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE))
	{
		//
		// Retrieve Rx messages from RX FIFO1
		//
		if (HAL_OK != HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader_2, RxData_2))
		{
			//
			// Error TODO:
			//
			RxMsgerror_2++;
		}
		else
		{
			switch (RxHeader_2.Identifier)
			{
			case 0x788:
				memcpy(zmv_can2_rx.data.designer.dina_std, &RxData_2, sizeof zmv_can2_rx.data.designer.dina_std);
				break;

			case 0x789:
				memcpy(zmv_can2_rx.data.error.dina_err, &RxData_2, sizeof zmv_can2_rx.data.error.dina_err);
				break;

			case 0x78A:
				memcpy(zmv_can2_rx.data.encoder_1.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_1.all);
				break;

			case 0x78B:
				memcpy(zmv_can2_rx.data.encoder_2.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_2.all);
				break;

			case 0x78C:
				memcpy(zmv_can2_rx.data.encoder_3.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_3.all);
				break;

			case 0x78D:
				memcpy(zmv_can2_rx.data.encoder_4.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_4.all);
				break;

			case 0x78E:
				memcpy(zmv_can2_rx.data.encoder_5.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_5.all);
				break;

			case 0x78F:
				memcpy(zmv_can2_rx.data.encoder_6.all, &RxData_2, sizeof zmv_can2_rx.data.encoder_6.all);
				break;

			default:
				break;
			}
		}

		//
		// Reactivate reception notification
		// TODO: Check if it is necessary to do so!
		//
		if (HAL_OK != HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0))
		{

		}

		//
		// Wait with sending FBV data
		// till we receive something from
		// the ZMV
		//
		if (0 == begin_tx_flg)
		{
			begin_tx_flg = 1;
		}

	}
}

/**
  *
  * @brief  Function implementing the can2Task thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void can2Task(void *argument)
{
	//
	// Configure reception filter to Rx FIFO 0
	// on FDCAN1 instance
	//
	sFilterConfig_2.IdType 			= FDCAN_STANDARD_ID;
	sFilterConfig_2.FilterIndex 	= 0;
	sFilterConfig_2.FilterType 		= FDCAN_FILTER_RANGE;
	sFilterConfig_2.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO1;
	sFilterConfig_2.FilterID1 		= 0x788;
	sFilterConfig_2.FilterID2 		= 0x78F;
	sFilterConfig_2.RxBufferIndex 	= 0;

	if (HAL_OK != HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig_2))
	{
		//
		// Error TODO:
		//
	}

	//
	// Activate reception notification.
	// Necessary if interrupt is used
	//
	if (HAL_OK != HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0))
	{
		//
		// Error TODO:
		//
	}

	//
	// Prepare Tx message Header
	//
	TxHeader_2.Identifier 			= 0x409; // FBV Module CAN address //0x790;
	TxHeader_2.IdType 				= FDCAN_STANDARD_ID;
	TxHeader_2.TxFrameType 			= FDCAN_DATA_FRAME;
	TxHeader_2.DataLength 			= FDCAN_DLC_BYTES_8;
	TxHeader_2.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
	TxHeader_2.BitRateSwitch 		= FDCAN_BRS_OFF;
	TxHeader_2.FDFormat 			= FDCAN_CLASSIC_CAN; // FDCAN_FD_CAN;
	TxHeader_2.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS;
	TxHeader_2.MessageMarker 		= 0;

	//
	// Start the FDCAN module
	// on FDCAN1 instance
	//
	if (HAL_OK != HAL_FDCAN_Start(&hfdcan2))
	{
		//
		// Error TODO:
		//
	}

	osDelay(1000);

	//
	// Infinite loop
	//
	for (;;)
	{
		//
		// Copy new data to the tx buffer
		//
//		memcpy(TxData_2, fbv_tx2.all, sizeof TxData_2);
		memcpy(TxData_2, fbv_webs.all, sizeof TxData_2);

		//
		// Add message to TX FIFO
		// of FDCAN instance 2
		// if at least one transmission buffer is free
		//
		if (begin_tx_flg)
		if (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2))
		if (HAL_OK != HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader_2, TxData_2))
		{
			//
			// Error TODO:
			//
			TxMsgerror_2++;
		}

		//
		// Append the data to the message queue
		// and send it to the UDP task!
		//
//		if (osOK != osMessageQueuePut(canUdpQueueHandle, &zmv_can2_rx, 0U, portMAX_DELAY))
//		{
//			//
//			// TODO: Error
//			//
//		}

		osDelay(100);

	}
}




