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
 * File Name    : dina_cx_task.c
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
#include "typedefs.h"
#include "lwip/udp.h"
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"
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

osThreadId_t udpsTaskHandle;
const osThreadAttr_t udpsTask_attributes = {
  .name = "udpsTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osMessageQueueId_t canUdpQueueHandle;
const osMessageQueueAttr_t canUdpQueue_attributes = {
  .name = "canUdpQueue"
};

DINA_TO_LJU_CYCLIC_FRAME_Tx_U udp_tx = {0};
ZMV_CAN_FRAME_Rx_U zmv_recv = {0};
ALL_ENCODERS_POS_U pos = {0};

extern ZMV_CAN_FRAME_Rx_U zmv_can2_rx;


static struct netconn *conn;
static struct netbuf *buf;
static struct netbuf *rxbuf;
err_t err;
err_t recv_err;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * @brief  Implemntation of the UDP server udpsTask thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void udpsTask(void *argument)
{
	ip_addr_t dest_addr;

	//
	// Create a new connection identifier
	//
	conn = netconn_new(NETCONN_UDP);


	if (conn != NULL)
	{
		//
		// Bind connection to the port 55152
		//
		err = netconn_bind(conn, IP_ADDR_ANY, 55152);

		if (err == ERR_OK)
		{
			//
			// The destination IP address of the computer
			//
			IP_ADDR4(&dest_addr, 192, 168, 84, 210);

			//
			// connect to the destination at port 55151
			//
			err = netconn_connect(conn, &dest_addr, 55151);

			if (err == ERR_OK)
			{
				osDelay(1000);

				//
				// Infinite loop
				//
				for (;;)
				{
					//
					// No queue
					//
					memcpy(zmv_recv.frame, zmv_can2_rx.frame, sizeof zmv_recv.frame);

					//
					// Check if we have a message
					// from the CAN2 task (using queue message)
					//
//				    if (osOK != osMessageQueueGet(canUdpQueueHandle, &zmv_recv, 0U, 0U)) //portMAX_DELAY))
//					{
				    	//
				    	// TODO: Error
				    	//
//				    	memset(udp_tx.frame, 0, sizeof udp_tx.frame);
//				    	memset(pos.all, 0, sizeof pos.all);
//					}
//				    else
//				    {
//						//
						// UDP frame header
						//
						udp_tx.data.addr_dina 				= 205;	// TODO: Make it dynamic
						udp_tx.data.addr_lju 				= 210;  // TODO: Make it dynamic
						udp_tx.data.message_id				= 0x2;
						udp_tx.data.message_cnt.always_one 	= 1;
						udp_tx.data.frame_crc.byte.LB 		= 123; // TODO: Calculate the CRC of the frame

						//
						// Encoder 1
						//
						udp_tx.data.encoder_1.position.byte.LB 	= pos.encoder._1.byte.LSB = zmv_recv.data.encoder_1.byte.pos_LSB;
						udp_tx.data.encoder_1.position.byte.MB 	= pos.encoder._1.byte.MLB = zmv_recv.data.encoder_1.byte.pos_MLB;
						udp_tx.data.encoder_1.position.byte.HB 	= pos.encoder._1.byte.MHB = zmv_recv.data.encoder_1.byte.pos_MHB;
						//
						udp_tx.data.encoder_1.speed.byte.LB 	= zmv_recv.data.encoder_1.byte.speed_LSB;
						udp_tx.data.encoder_1.speed.byte.HB 	= zmv_recv.data.encoder_1.byte.speed_MSB;
						//
						udp_tx.data.encoder_1.status_1.value 	= zmv_recv.data.encoder_1.byte.status_1;
						udp_tx.data.encoder_1.status_2.value 	= zmv_recv.data.encoder_1.byte.status_2;

						//
						// Encoder 2
						//
						udp_tx.data.encoder_2.position.byte.LB 	= pos.encoder._2.byte.LSB = zmv_recv.data.encoder_2.byte.pos_LSB;
						udp_tx.data.encoder_2.position.byte.MB 	= pos.encoder._2.byte.MLB = zmv_recv.data.encoder_2.byte.pos_MLB;
						udp_tx.data.encoder_2.position.byte.HB 	= pos.encoder._2.byte.MHB = zmv_recv.data.encoder_2.byte.pos_MHB;
						//
						udp_tx.data.encoder_2.speed.byte.LB 	= zmv_recv.data.encoder_2.byte.speed_LSB;
						udp_tx.data.encoder_2.speed.byte.HB 	= zmv_recv.data.encoder_2.byte.speed_MSB;
						//
						udp_tx.data.encoder_2.status_1.value	= zmv_recv.data.encoder_2.byte.status_1;
						udp_tx.data.encoder_2.status_2.value	= zmv_recv.data.encoder_2.byte.status_2;

						//
						// Encoder 3
						//
						udp_tx.data.encoder_3.position.byte.LB 	= pos.encoder._3.byte.LSB = zmv_recv.data.encoder_3.byte.pos_LSB;
						udp_tx.data.encoder_3.position.byte.MB 	= pos.encoder._3.byte.MLB = zmv_recv.data.encoder_3.byte.pos_MLB;
						udp_tx.data.encoder_3.position.byte.HB 	= pos.encoder._3.byte.MHB = zmv_recv.data.encoder_3.byte.pos_MHB;
						//
						udp_tx.data.encoder_3.speed.byte.LB 	= zmv_recv.data.encoder_3.byte.speed_LSB;
						udp_tx.data.encoder_3.speed.byte.HB 	= zmv_recv.data.encoder_3.byte.speed_MSB;
						//
						udp_tx.data.encoder_3.status_1.value	= zmv_recv.data.encoder_3.byte.status_1;
						udp_tx.data.encoder_3.status_2.value	= zmv_recv.data.encoder_3.byte.status_2;

						//
						// Encoder 4
						//
						udp_tx.data.encoder_4.position.byte.LB 	= pos.encoder._4.byte.LSB = zmv_recv.data.encoder_4.byte.pos_LSB;
						udp_tx.data.encoder_4.position.byte.MB 	= pos.encoder._4.byte.MLB = zmv_recv.data.encoder_4.byte.pos_MLB;
						udp_tx.data.encoder_4.position.byte.HB 	= pos.encoder._4.byte.MHB = zmv_recv.data.encoder_4.byte.pos_MHB;
						//
						udp_tx.data.encoder_4.speed.byte.LB 	= zmv_recv.data.encoder_4.byte.speed_LSB;
						udp_tx.data.encoder_4.speed.byte.HB 	= zmv_recv.data.encoder_4.byte.speed_MSB;
						//
						udp_tx.data.encoder_4.status_1.value	= zmv_recv.data.encoder_4.byte.status_1;
						udp_tx.data.encoder_4.status_2.value	= zmv_recv.data.encoder_4.byte.status_2;

						//
						// Encoder 5
						//
						udp_tx.data.encoder_5.position.byte.LB 	= pos.encoder._5.byte.LSB = zmv_recv.data.encoder_5.byte.pos_LSB;
						udp_tx.data.encoder_5.position.byte.MB 	= pos.encoder._5.byte.MLB = zmv_recv.data.encoder_5.byte.pos_MLB;
						udp_tx.data.encoder_5.position.byte.HB 	= pos.encoder._5.byte.MHB = zmv_recv.data.encoder_5.byte.pos_MHB;
						//
						udp_tx.data.encoder_5.speed.byte.LB 	= zmv_recv.data.encoder_5.byte.speed_LSB;
						udp_tx.data.encoder_5.speed.byte.HB 	= zmv_recv.data.encoder_5.byte.speed_MSB;
						//
						udp_tx.data.encoder_5.status_1.value	= zmv_recv.data.encoder_5.byte.status_1;
						udp_tx.data.encoder_5.status_2.value	= zmv_recv.data.encoder_5.byte.status_2;

						//
						// Encoder 6
						//
						udp_tx.data.encoder_6.position.byte.LB 	= pos.encoder._6.byte.LSB = zmv_recv.data.encoder_6.byte.pos_LSB;
						udp_tx.data.encoder_6.position.byte.MB 	= pos.encoder._6.byte.MLB = zmv_recv.data.encoder_6.byte.pos_MLB;
						udp_tx.data.encoder_6.position.byte.HB 	= pos.encoder._6.byte.MHB = zmv_recv.data.encoder_6.byte.pos_MHB;
						//
						udp_tx.data.encoder_6.speed.byte.LB 	= zmv_recv.data.encoder_6.byte.speed_LSB;
						udp_tx.data.encoder_6.speed.byte.HB 	= zmv_recv.data.encoder_6.byte.speed_MSB;
						//
						udp_tx.data.encoder_6.status_1.value	= zmv_recv.data.encoder_6.byte.status_1;
						udp_tx.data.encoder_6.status_2.value	= zmv_recv.data.encoder_6.byte.status_2;

						//
						// TODO: This is only for test reasons
						//
//						memcpy(udp_tx.data.logic_data, zmv_recv.data.designer.dina_std, sizeof zmv_recv.data.designer.dina_std);

						//
						// Logic data dummy
						//
						memset(udp_tx.data.logic_data, 0xff, sizeof udp_tx.data.logic_data);
//				    }

					//
					// Create a new netbuf
					//
					buf = netbuf_new();

					//
					// Heart beat!
					//
					udp_tx.data.message_cnt.alive_cnt += 1;

					//
					// refer the netbuf to the data to be sent
					//
					netbuf_ref(buf, &udp_tx.frame, sizeof udp_tx.frame);

					//
					// send the netbuf to the client
					//
					netconn_send(conn,buf);

					//
					// delete the netbuf
					//
					netbuf_delete(buf);

//					//
//					// Receive data from the client
//					//
//					recv_err = netconn_recv(conn, &rxbuf);
//
//					if (recv_err == ERR_OK)
//					{
//						//
//						// copy the data into our buffer (smsg)
//						//
//						sprintf (smsg, "\"%s\" was sent by the Server\n", (char *) rxbuf->p->payload);
//						udpsend(smsg);  // send the message to the server
//						netbuf_delete(rxbuf);  // delete the netbuf
//					}

					osDelay(50);
				}
			}
		}
	}
	else
	{
		netconn_delete(conn);
	}
}

/**
  *
  * @brief  Old implementation of the UDP server udpsTask thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

//void udpsTask(void *argument)
//{
//	ip_addr_t PC_IPADDR;
//
//	//
//	// Set the IP Address of
//	// UDP Client
//	//
//	IP_ADDR4(&PC_IPADDR, 192, 168, 100, 123);
//
//	struct udp_pcb* my_udp = udp_new();
//	udp_connect(my_udp, &PC_IPADDR, 55151);
//	struct pbuf* udp_buffer = NULL;
//
//	//
//	// Infinite loop
//	//
//	for (;;)
//	{
//		memcpy(zmv_recv.frame, zmv_can2_rx.frame, sizeof zmv_recv.frame);
//
//		//
//		// Check if we have a message
//		// from the CAN2 task
//		//
////	    if (osOK != osMessageQueueGet(canUdpQueueHandle, &zmv_recv, 0U, 0U)) //portMAX_DELAY))
////		{
////	    	//
////	    	// TODO: Error
////	    	//
////	    	memset(udp_tx.frame, 0, sizeof udp_tx.frame);
////		}
////	    else
////	    {
////	    	//
//	    	// UDP frame header
//	    	//
//	    	udp_tx.data.addr_dina 				= 100;
//	    	udp_tx.data.addr_lju 				= 123;
//	    	udp_tx.data.message_id				= 0x2;
//	    	udp_tx.data.message_cnt.always_one 	= 1;
//	    	udp_tx.data.frame_crc.byte.LB 		= 123; // TODO: Calculate the CRC of the frame
//
//			//
//			// Encoder 1
//			//
//			udp_tx.data.encoder_1.position.byte.LB 	= zmv_recv.data.encoder_1.byte.pos_LSB;
//			udp_tx.data.encoder_1.position.byte.MB 	= zmv_recv.data.encoder_1.byte.pos_MLB;
//			udp_tx.data.encoder_1.position.byte.HB 	= zmv_recv.data.encoder_1.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_1.speed.byte.LB 	= zmv_recv.data.encoder_1.byte.speed_LSB;
//			udp_tx.data.encoder_1.speed.byte.HB 	= zmv_recv.data.encoder_1.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_1.status_1.value 	= zmv_recv.data.encoder_1.byte.status_1;
//			udp_tx.data.encoder_1.status_2.value 	= zmv_recv.data.encoder_1.byte.status_2;
//
//			//
//			// Encoder 2
//			//
//			udp_tx.data.encoder_2.position.byte.LB 	= zmv_recv.data.encoder_2.byte.pos_LSB;
//			udp_tx.data.encoder_2.position.byte.MB 	= zmv_recv.data.encoder_2.byte.pos_MLB;
//			udp_tx.data.encoder_2.position.byte.HB 	= zmv_recv.data.encoder_2.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_2.speed.byte.LB 	= zmv_recv.data.encoder_2.byte.speed_LSB;
//			udp_tx.data.encoder_2.speed.byte.HB 	= zmv_recv.data.encoder_2.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_2.status_1.value	= zmv_recv.data.encoder_2.byte.status_1;
//			udp_tx.data.encoder_2.status_2.value	= zmv_recv.data.encoder_2.byte.status_2;
//
//			//
//			// Encoder 3
//			//
//			udp_tx.data.encoder_3.position.byte.LB 	= zmv_recv.data.encoder_3.byte.pos_LSB;
//			udp_tx.data.encoder_3.position.byte.MB 	= zmv_recv.data.encoder_3.byte.pos_MLB;
//			udp_tx.data.encoder_3.position.byte.HB 	= zmv_recv.data.encoder_3.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_3.speed.byte.LB 	= zmv_recv.data.encoder_3.byte.speed_LSB;
//			udp_tx.data.encoder_3.speed.byte.HB 	= zmv_recv.data.encoder_3.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_3.status_1.value	= zmv_recv.data.encoder_3.byte.status_1;
//			udp_tx.data.encoder_3.status_2.value	= zmv_recv.data.encoder_3.byte.status_2;
//
//			//
//			// Encoder 4
//			//
//			udp_tx.data.encoder_4.position.byte.LB 	= zmv_recv.data.encoder_4.byte.pos_LSB;
//			udp_tx.data.encoder_4.position.byte.MB 	= zmv_recv.data.encoder_4.byte.pos_MLB;
//			udp_tx.data.encoder_4.position.byte.HB 	= zmv_recv.data.encoder_4.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_4.speed.byte.LB 	= zmv_recv.data.encoder_4.byte.speed_LSB;
//			udp_tx.data.encoder_4.speed.byte.HB 	= zmv_recv.data.encoder_4.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_4.status_1.value	= zmv_recv.data.encoder_4.byte.status_1;
//			udp_tx.data.encoder_4.status_2.value	= zmv_recv.data.encoder_4.byte.status_2;
//
//			//
//			// Encoder 5
//			//
//			udp_tx.data.encoder_5.position.byte.LB 	= zmv_recv.data.encoder_5.byte.pos_LSB;
//			udp_tx.data.encoder_5.position.byte.MB 	= zmv_recv.data.encoder_5.byte.pos_MLB;
//			udp_tx.data.encoder_5.position.byte.HB 	= zmv_recv.data.encoder_5.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_5.speed.byte.LB 	= zmv_recv.data.encoder_5.byte.speed_LSB;
//			udp_tx.data.encoder_5.speed.byte.HB 	= zmv_recv.data.encoder_5.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_5.status_1.value	= zmv_recv.data.encoder_5.byte.status_1;
//			udp_tx.data.encoder_5.status_2.value	= zmv_recv.data.encoder_5.byte.status_2;
//
//			//
//			// Encoder 6
//			//
//			udp_tx.data.encoder_6.position.byte.LB 	= zmv_recv.data.encoder_6.byte.pos_LSB;
//			udp_tx.data.encoder_6.position.byte.MB 	= zmv_recv.data.encoder_6.byte.pos_MLB;
//			udp_tx.data.encoder_6.position.byte.HB 	= zmv_recv.data.encoder_6.byte.pos_MHB;
//			//
//			udp_tx.data.encoder_6.speed.byte.LB 	= zmv_recv.data.encoder_6.byte.speed_LSB;
//			udp_tx.data.encoder_6.speed.byte.HB 	= zmv_recv.data.encoder_6.byte.speed_MSB;
//			//
//			udp_tx.data.encoder_6.status_1.value	= zmv_recv.data.encoder_6.byte.status_1;
//			udp_tx.data.encoder_6.status_2.value	= zmv_recv.data.encoder_6.byte.status_2;
//
//			//
//			// TODO: This is only for test reasons
//			//
//	//		memcpy(udp_tx.data.logic_data, zmv_recv.data.designer.dina_std, sizeof zmv_recv.data.designer.dina_std);
//
//			//
//			// Logic data dummy
//			//
//			memset(udp_tx.data.logic_data, 0xff, sizeof udp_tx.data.logic_data);
////	    }
//
//		//
//		// !! PBUF_RAM is critical for correct operation
//		//
////		udp_buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof UDP_Tx, PBUF_RAM);
////		Or
//		udp_buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof udp_tx.frame, PBUF_RAM);
//
//		if (udp_buffer != NULL)
//		{
//			//
//			// Heart beat!
//			//
//			udp_tx.data.message_cnt.alive_cnt += 1;
//
////			memcpy(udp_buffer->payload, &udp_tx, sizeof udp_tx);
////			Or
//			memcpy(udp_buffer->payload, &udp_tx.frame, sizeof udp_tx.frame);
//			udp_send(my_udp, udp_buffer);
//			pbuf_free(udp_buffer);
//		}
//
//	    osDelay(50);
//	}
//
//}

/**
  *
  * @brief  Function implementing the udpTask thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

//void udpClientInit(void)
//{
//	sys_thread_new("dina_Cx_Task", udpTask, NULL, 4 * DEFAULT_THREAD_STACKSIZE, osPriorityNormal);
//}
