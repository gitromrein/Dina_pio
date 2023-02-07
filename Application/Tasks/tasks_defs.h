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
 * File Name    : tasks_defs.h
 * Version      : 
 * Description  : 
 * Creation Date: Nov 30, 2022
 * Author		: KarimHmidi
 *********************************************************************/

#ifndef TASKS_TASKS_DEFS_H_
#define TASKS_TASKS_DEFS_H_

/*
 *
 * Includes
 *
 *********************************************************************/
//#include "cmsis_os.h"

/*
 *
 * Defines
 *
 **********************************************************************/
/* Definition for the network semaphore */
//extern osSemaphoreId_t netSemaphoreHandle;
//extern const osSemaphoreAttr_t netSemaphore_attributes;

/* Definition for canUdpQueue */
extern osMessageQueueId_t canUdpQueueHandle;
extern const osMessageQueueAttr_t canUdpQueue_attributes;

/* Definitions for udpTask */
extern osThreadId_t udpsTaskHandle;
extern const osThreadAttr_t udpsTask_attributes;

/* Definitions for can1Task */
extern osThreadId_t can1TaskHandle;
extern const osThreadAttr_t can1Task_attributes;

/* Definitions for can2Task */
extern osThreadId_t can2TaskHandle;
extern const osThreadAttr_t can2Task_attributes;

/* Definition for usart8Task */
extern osThreadId_t usart2TaskHandle;
extern const osThreadAttr_t usart2Task_attributes;

extern osThreadId_t websTaskHandle;
extern const osThreadAttr_t websTask_attributes;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/*
 *
 * Prototypes defines
 *
 **********************************************************************/
void udpsTask(void *argument);
void can1Task(void *argument);
void can2Task(void *argument);
void usart2Task(void *argument);
void websTask(void *argument);
//void udpClientInit(void);



#endif /* TASKS_TASKS_DEFS_H_ */
