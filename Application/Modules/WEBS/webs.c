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
 * File Name    : webs.c
 * Version      :
 * Description  :
 * Creation Date: Jan 10, 2022
 * Author		: KarimHmidi
 *********************************************************************/

/*
 *
 * Includes
 *
 *********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "typedefs.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "webs.h"
#include "cmsis_os.h"

/*
 *
 * Variables defines
 *
 *********************************************************************/

extern DINA_TO_LJU_CYCLIC_FRAME_Tx_U udp_tx;
extern ZMV_CAN_FRAME_Rx_U zmv_can2_rx;
extern ZMV_CAN_FRAME_Rx_U zmv_can1_rx;

extern ALL_ENCODERS_POS_U pos;

FBV_ZOMBIE_U fbv_webs = {0};


/**
  *
  * @brief  HTTP Web server
  * @param  *conn
  * @retval None
  *
  *********************************************************************/
void webServer(struct netconn *conn)
{
	struct netbuf *inbuf;
	struct fs_file file;
	char* buf;
	err_t recv_err;
	u16_t buflen;

	//
	// Read the data from the port,
	// blocking if nothing yet there
	//
	recv_err = netconn_recv(conn, &inbuf);

	if (recv_err == ERR_OK)
	{
		if (netconn_err(conn) == ERR_OK)
		{
			//
			// Get the data pointer and length of
			// the data inside a netbuf
			//
			netbuf_data(inbuf, (void**)&buf, &buflen);

			//
			// Check if request
			// to get the index.html
			//
			if (strncmp((char const *)buf, "GET /index.html", 15) == 0)
			{
				fs_open(&file, "/index.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /jscript.js", 15) == 0)
			{
				fs_open(&file, "/jscript.js");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /settings.html", 18) == 0)
			{
				fs_open(&file, "/settings.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /setjscript.js", 18) == 0)
			{
				fs_open(&file, "/setjscript.js");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /styles.css", 15) == 0)
			{
				fs_open(&file, "/styles.css");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /canframes.html", 19) == 0)
			{
				fs_open(&file, "/canframes.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /canjscript.js", 18) == 0)
			{
				fs_open(&file, "/canjscript.js");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /img/favicon.ico", 20) == 0)
			{
				fs_open(&file, "/img/favicon.ico");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /img/dina_logo_yellow.png", 29) == 0)
			{
				fs_open(&file, "/img/dina_logo_yellow.png");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf,"GET /zombieFBV",14)==0)
			{
				char c = buf[14];
				fbv_webs.byte.B1.fbi1 = atoi(&c);
				c = buf[15];
				fbv_webs.byte.B1.fbi2 = atoi(&c);
				c = buf[16];
				fbv_webs.byte.B1.fbi3 = atoi(&c);
				c = buf[17];
				fbv_webs.byte.B1.fbi4 = atoi(&c);
				c = buf[18];
				fbv_webs.byte.B1.fbi5 = atoi(&c);
				c = buf[19];
				fbv_webs.byte.B1.fbi6 = atoi(&c);
				c = buf[20];
				fbv_webs.byte.B1.fbi7 = atoi(&c);
				c = buf[21];
				fbv_webs.byte.B1.fbi8 = atoi(&c);

			}
			else if (strncmp((char const *)buf, "GET /getFBVBytes", 16) == 0)
			{
				//
				// Send the same data to
				// the client again.
				// TODO: Send the value of other bytes
				//
				char *checkboxesData;
				checkboxesData = pvPortMalloc(300);
				int length  = sprintf(checkboxesData, "[%u, %u, %u, %u, %u, %u, %u, %u]",
													fbv_webs.byte.B1.fbi1,
													fbv_webs.byte.B1.fbi2,
													fbv_webs.byte.B1.fbi3,
													fbv_webs.byte.B1.fbi4,
													fbv_webs.byte.B1.fbi5,
													fbv_webs.byte.B1.fbi6,
													fbv_webs.byte.B1.fbi7,
													fbv_webs.byte.B1.fbi8);
				//
				// @info The option NETCONN_NOCOPY leads to data
				//		 corruption at transmission.
				//
				netconn_write(conn, (const unsigned char*)checkboxesData, (size_t)length, NETCONN_COPY);
				vPortFree(checkboxesData);
			}
			else if (strncmp((char const *)buf, "GET /getCAN1data", 16) == 0)
			{
				char *canPageData;
				canPageData = pvPortMalloc(500);
				int len = sprintf(canPageData, "[%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u]",
											zmv_can1_rx.data.designer.dina_std[0],
											zmv_can1_rx.data.designer.dina_std[1],
											zmv_can1_rx.data.designer.dina_std[2],
											zmv_can1_rx.data.designer.dina_std[3],
											zmv_can1_rx.data.designer.dina_std[4],
											zmv_can1_rx.data.designer.dina_std[5],
											zmv_can1_rx.data.designer.dina_std[6],
											zmv_can1_rx.data.designer.dina_std[7],
											//
											zmv_can1_rx.data.error.dina_err[0],
											zmv_can1_rx.data.error.dina_err[1],
											zmv_can1_rx.data.error.dina_err[2],
											zmv_can1_rx.data.error.dina_err[3],
											zmv_can1_rx.data.error.dina_err[4],
											zmv_can1_rx.data.error.dina_err[5],
											zmv_can1_rx.data.error.dina_err[6],
											zmv_can1_rx.data.error.dina_err[7],
											//
											zmv_can1_rx.data.encoder_1.byte.status_2,
											zmv_can1_rx.data.encoder_1.byte.status_1,
											zmv_can1_rx.data.encoder_1.byte.speed_MSB,
											zmv_can1_rx.data.encoder_1.byte.speed_LSB,
											zmv_can1_rx.data.encoder_1.byte.pos_MSB,
											zmv_can1_rx.data.encoder_1.byte.pos_MHB,
											zmv_can1_rx.data.encoder_1.byte.pos_MLB,
											zmv_can1_rx.data.encoder_1.byte.pos_LSB,
											//
											zmv_can1_rx.data.encoder_2.byte.status_2,
											zmv_can1_rx.data.encoder_2.byte.status_1,
											zmv_can1_rx.data.encoder_2.byte.speed_MSB,
											zmv_can1_rx.data.encoder_2.byte.speed_LSB,
											zmv_can1_rx.data.encoder_2.byte.pos_MSB,
											zmv_can1_rx.data.encoder_2.byte.pos_MHB,
											zmv_can1_rx.data.encoder_2.byte.pos_MLB,
											zmv_can1_rx.data.encoder_2.byte.pos_LSB,
											//
											zmv_can1_rx.data.encoder_3.byte.status_2,
											zmv_can1_rx.data.encoder_3.byte.status_1,
											zmv_can1_rx.data.encoder_3.byte.speed_MSB,
											zmv_can1_rx.data.encoder_3.byte.speed_LSB,
											zmv_can1_rx.data.encoder_3.byte.pos_MSB,
											zmv_can1_rx.data.encoder_3.byte.pos_MHB,
											zmv_can1_rx.data.encoder_3.byte.pos_MLB,
											zmv_can1_rx.data.encoder_3.byte.pos_LSB,
											//
											zmv_can1_rx.data.encoder_4.byte.status_2,
											zmv_can1_rx.data.encoder_4.byte.status_1,
											zmv_can1_rx.data.encoder_4.byte.speed_MSB,
											zmv_can1_rx.data.encoder_4.byte.speed_LSB,
											zmv_can1_rx.data.encoder_4.byte.pos_MSB,
											zmv_can1_rx.data.encoder_4.byte.pos_MHB,
											zmv_can1_rx.data.encoder_4.byte.pos_MLB,
											zmv_can1_rx.data.encoder_4.byte.pos_LSB,
											//
											zmv_can1_rx.data.encoder_5.byte.status_2,
											zmv_can1_rx.data.encoder_5.byte.status_1,
											zmv_can1_rx.data.encoder_5.byte.speed_MSB,
											zmv_can1_rx.data.encoder_5.byte.speed_LSB,
											zmv_can1_rx.data.encoder_5.byte.pos_MSB,
											zmv_can1_rx.data.encoder_5.byte.pos_MHB,
											zmv_can1_rx.data.encoder_5.byte.pos_MLB,
											zmv_can1_rx.data.encoder_5.byte.pos_LSB,
											//
											zmv_can1_rx.data.encoder_6.byte.status_2,
											zmv_can1_rx.data.encoder_6.byte.status_1,
											zmv_can1_rx.data.encoder_6.byte.speed_MSB,
											zmv_can1_rx.data.encoder_6.byte.speed_LSB,
											zmv_can1_rx.data.encoder_6.byte.pos_MSB,
											zmv_can1_rx.data.encoder_6.byte.pos_MHB,
											zmv_can1_rx.data.encoder_6.byte.pos_MLB,
											zmv_can1_rx.data.encoder_6.byte.pos_LSB,
											/////////////////////////////////////////
											/////////////////////////////////////////
											zmv_can1_rx.data.encoder_1.value.pos,
											zmv_can1_rx.data.encoder_1.value.speed,
											zmv_can1_rx.data.encoder_1.value.status_1,
											zmv_can1_rx.data.encoder_1.value.status_2,
											//
											zmv_can1_rx.data.encoder_2.value.pos,
											zmv_can1_rx.data.encoder_2.value.speed,
											zmv_can1_rx.data.encoder_2.value.status_1,
											zmv_can1_rx.data.encoder_2.value.status_2,
											//
											zmv_can1_rx.data.encoder_3.value.pos,
											zmv_can1_rx.data.encoder_3.value.speed,
											zmv_can1_rx.data.encoder_3.value.status_1,
											zmv_can1_rx.data.encoder_3.value.status_2,
											//
											zmv_can1_rx.data.encoder_4.value.pos,
											zmv_can1_rx.data.encoder_4.value.speed,
											zmv_can1_rx.data.encoder_4.value.status_1,
											zmv_can1_rx.data.encoder_4.value.status_2,
											//
											zmv_can1_rx.data.encoder_5.value.pos,
											zmv_can1_rx.data.encoder_5.value.speed,
											zmv_can1_rx.data.encoder_5.value.status_1,
											zmv_can1_rx.data.encoder_5.value.status_2,
											//
											zmv_can1_rx.data.encoder_6.value.pos,
											zmv_can1_rx.data.encoder_6.value.speed,
											zmv_can1_rx.data.encoder_6.value.status_1,
											zmv_can1_rx.data.encoder_6.value.status_2,
											//
											fbv_webs.all[0],
											fbv_webs.all[1],
											fbv_webs.all[2],
											fbv_webs.all[3],
											fbv_webs.all[4],
											fbv_webs.all[5],
											fbv_webs.all[6],
											fbv_webs.all[7]
											);

				//
				// @info The option NETCONN_NOCOPY leads to data
				//		 corruption at transmission.
				//
				netconn_write(conn, (const unsigned char*)canPageData, (size_t)len, NETCONN_COPY);
				vPortFree(canPageData);
			}
			else if (strncmp((char const *)buf, "GET /getCAN2data", 16) == 0)
			{
				char *canPageData;
				canPageData = pvPortMalloc(500);
				int len = sprintf(canPageData, "[%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u, %lu, %u, %u, %u]",
											zmv_can2_rx.data.designer.dina_std[7],
											zmv_can2_rx.data.designer.dina_std[6],
											zmv_can2_rx.data.designer.dina_std[5],
											zmv_can2_rx.data.designer.dina_std[4],
											zmv_can2_rx.data.designer.dina_std[3],
											zmv_can2_rx.data.designer.dina_std[2],
											zmv_can2_rx.data.designer.dina_std[1],
											zmv_can2_rx.data.designer.dina_std[0],
											//
											zmv_can2_rx.data.error.dina_err[7],
											zmv_can2_rx.data.error.dina_err[6],
											zmv_can2_rx.data.error.dina_err[5],
											zmv_can2_rx.data.error.dina_err[4],
											zmv_can2_rx.data.error.dina_err[3],
											zmv_can2_rx.data.error.dina_err[2],
											zmv_can2_rx.data.error.dina_err[1],
											zmv_can2_rx.data.error.dina_err[0],
											//
											zmv_can2_rx.data.encoder_1.byte.status_2,
											zmv_can2_rx.data.encoder_1.byte.status_1,
											zmv_can2_rx.data.encoder_1.byte.speed_MSB,
											zmv_can2_rx.data.encoder_1.byte.speed_LSB,
											zmv_can2_rx.data.encoder_1.byte.pos_MSB,
											zmv_can2_rx.data.encoder_1.byte.pos_MHB,
											zmv_can2_rx.data.encoder_1.byte.pos_MLB,
											zmv_can2_rx.data.encoder_1.byte.pos_LSB,
											//
											zmv_can2_rx.data.encoder_2.byte.status_2,
											zmv_can2_rx.data.encoder_2.byte.status_1,
											zmv_can2_rx.data.encoder_2.byte.speed_MSB,
											zmv_can2_rx.data.encoder_2.byte.speed_LSB,
											zmv_can2_rx.data.encoder_2.byte.pos_MSB,
											zmv_can2_rx.data.encoder_2.byte.pos_MHB,
											zmv_can2_rx.data.encoder_2.byte.pos_MLB,
											zmv_can2_rx.data.encoder_2.byte.pos_LSB,
											//
											zmv_can2_rx.data.encoder_3.byte.status_2,
											zmv_can2_rx.data.encoder_3.byte.status_1,
											zmv_can2_rx.data.encoder_3.byte.speed_MSB,
											zmv_can2_rx.data.encoder_3.byte.speed_LSB,
											zmv_can2_rx.data.encoder_3.byte.pos_MSB,
											zmv_can2_rx.data.encoder_3.byte.pos_MHB,
											zmv_can2_rx.data.encoder_3.byte.pos_MLB,
											zmv_can2_rx.data.encoder_3.byte.pos_LSB,
											//
											zmv_can2_rx.data.encoder_4.byte.status_2,
											zmv_can2_rx.data.encoder_4.byte.status_1,
											zmv_can2_rx.data.encoder_4.byte.speed_MSB,
											zmv_can2_rx.data.encoder_4.byte.speed_LSB,
											zmv_can2_rx.data.encoder_4.byte.pos_MSB,
											zmv_can2_rx.data.encoder_4.byte.pos_MHB,
											zmv_can2_rx.data.encoder_4.byte.pos_MLB,
											zmv_can2_rx.data.encoder_4.byte.pos_LSB,
											//
											zmv_can2_rx.data.encoder_5.byte.status_2,
											zmv_can2_rx.data.encoder_5.byte.status_1,
											zmv_can2_rx.data.encoder_5.byte.speed_MSB,
											zmv_can2_rx.data.encoder_5.byte.speed_LSB,
											zmv_can2_rx.data.encoder_5.byte.pos_MSB,
											zmv_can2_rx.data.encoder_5.byte.pos_MHB,
											zmv_can2_rx.data.encoder_5.byte.pos_MLB,
											zmv_can2_rx.data.encoder_5.byte.pos_LSB,
											//
											zmv_can2_rx.data.encoder_6.byte.status_2,
											zmv_can2_rx.data.encoder_6.byte.status_1,
											zmv_can2_rx.data.encoder_6.byte.speed_MSB,
											zmv_can2_rx.data.encoder_6.byte.speed_LSB,
											zmv_can2_rx.data.encoder_6.byte.pos_MSB,
											zmv_can2_rx.data.encoder_6.byte.pos_MHB,
											zmv_can2_rx.data.encoder_6.byte.pos_MLB,
											zmv_can2_rx.data.encoder_6.byte.pos_LSB,
											/////////////////////////////////////////
											/////////////////////////////////////////
											zmv_can2_rx.data.encoder_1.value.pos,
											zmv_can2_rx.data.encoder_1.value.speed,
											zmv_can2_rx.data.encoder_1.value.status_1,
											zmv_can2_rx.data.encoder_1.value.status_2,
											//
											zmv_can2_rx.data.encoder_2.value.pos,
											zmv_can2_rx.data.encoder_2.value.speed,
											zmv_can2_rx.data.encoder_2.value.status_1,
											zmv_can2_rx.data.encoder_2.value.status_2,
											//
											zmv_can2_rx.data.encoder_3.value.pos,
											zmv_can2_rx.data.encoder_3.value.speed,
											zmv_can2_rx.data.encoder_3.value.status_1,
											zmv_can2_rx.data.encoder_3.value.status_2,
											//
											zmv_can2_rx.data.encoder_4.value.pos,
											zmv_can2_rx.data.encoder_4.value.speed,
											zmv_can2_rx.data.encoder_4.value.status_1,
											zmv_can2_rx.data.encoder_4.value.status_2,
											//
											zmv_can2_rx.data.encoder_5.value.pos,
											zmv_can2_rx.data.encoder_5.value.speed,
											zmv_can2_rx.data.encoder_5.value.status_1,
											zmv_can2_rx.data.encoder_5.value.status_2,
											//
											zmv_can2_rx.data.encoder_6.value.pos,
											zmv_can2_rx.data.encoder_6.value.speed,
											zmv_can2_rx.data.encoder_6.value.status_1,
											zmv_can2_rx.data.encoder_6.value.status_2
											//
//											fbv_webs.all[0],
//											fbv_webs.all[1],
//											fbv_webs.all[2],
//											fbv_webs.all[3],
//											fbv_webs.all[4],
//											fbv_webs.all[5],
//											fbv_webs.all[6],
//											fbv_webs.all[7]
											);

				//
				// @info The option NETCONN_NOCOPY leads to data
				//		 corruption at transmission.
				//
				netconn_write(conn, (const unsigned char*)canPageData, (size_t)len, NETCONN_COPY);
				vPortFree(canPageData);
			}
			else if (strncmp((char const *)buf, "GET /getCxWdata", 15) == 0)
			{
				char *pagedata;
				pagedata = pvPortMalloc(500);
				int len = sprintf(pagedata, "[%u, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %lu, %u, %u, %u, %u, %u, %u, %u, %u]",
											udp_tx.data.addr_lju,
											udp_tx.data.addr_dina,
											udp_tx.data.message_id,
											udp_tx.data.message_cnt.alive_cnt,
											udp_tx.data.dina_status.sys_status,
											udp_tx.data.dina_error_group.error_group_nr,
											udp_tx.data.dina_status.error,
											//
//											udp_tx.data.encoder_1.position.all[1],
											pos.encoder._1.value,
											udp_tx.data.encoder_1.speed.value,
											udp_tx.data.encoder_1.status_1.value,
											udp_tx.data.encoder_1.status_2.value,
											udp_tx.data.encoder_1.status_3,
											udp_tx.data.encoder_1.status_4,
											udp_tx.data.encoder_1.status_5,
											//
//											udp_tx.data.encoder_2.position.all[1],
											pos.encoder._2.value,
											udp_tx.data.encoder_2.speed.value,
											udp_tx.data.encoder_2.status_1.value,
											udp_tx.data.encoder_2.status_2.value,
											udp_tx.data.encoder_2.status_3,
											udp_tx.data.encoder_2.status_4,
											udp_tx.data.encoder_2.status_5,
											//
//											udp_tx.data.encoder_3.position.all[1],
											pos.encoder._3.value,
											udp_tx.data.encoder_3.speed.value,
											udp_tx.data.encoder_3.status_1.value,
											udp_tx.data.encoder_3.status_2.value,
											udp_tx.data.encoder_3.status_3,
											udp_tx.data.encoder_3.status_4,
											udp_tx.data.encoder_3.status_5,
											//
//											udp_tx.data.encoder_4.position.all[1],
											pos.encoder._4.value,
											udp_tx.data.encoder_4.speed.value,
											udp_tx.data.encoder_4.status_1.value,
											udp_tx.data.encoder_4.status_2.value,
											udp_tx.data.encoder_4.status_3,
											udp_tx.data.encoder_4.status_4,
											udp_tx.data.encoder_4.status_5,
											//
//											udp_tx.data.encoder_5.position.all[1],
											pos.encoder._5.value,
											udp_tx.data.encoder_5.speed.value,
											udp_tx.data.encoder_5.status_1.value,
											udp_tx.data.encoder_5.status_2.value,
											udp_tx.data.encoder_5.status_3,
											udp_tx.data.encoder_5.status_4,
											udp_tx.data.encoder_5.status_5,
											//
//											udp_tx.data.encoder_5.position.all[1],
											pos.encoder._6.value,
											udp_tx.data.encoder_6.speed.value,
											udp_tx.data.encoder_6.status_1.value,
											udp_tx.data.encoder_6.status_2.value,
											udp_tx.data.encoder_6.status_3,
											udp_tx.data.encoder_6.status_4,
											udp_tx.data.encoder_6.status_5,
											udp_tx.data.frame_crc.byte.HB,
											udp_tx.data.frame_crc.byte.LB
											);

//				int len = sprintf(pagedata, "[[\"LJU_ADDR\",%u],[\"DINA_ADDR\",%u],[\"MSG_ID\",%u],[\"HEART_BEAT\",%u]]\n", udp_tx.data.addr_lju, udp_tx.data.addr_dina, udp_tx.data.message_id, udp_tx.data.message_cnt.alive_cnt);

				//
				// @info The option NETCONN_NOCOPY leads to data
				//		 corruption at transmission.
				//
				netconn_write(conn, (const unsigned char*)pagedata, (size_t)len, NETCONN_COPY);
				vPortFree(pagedata);
			}
			else
			{
				/* Load Error page */
				fs_open(&file, "/404.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
		}
	}

	//
	// Close the connection
	// (server closes in HTTP)
	//
	netconn_close(conn);

	//
	// Delete the buffer (netconn_recv gives
	// us ownership, so we have to make sure to
	// deallocate the buffer)
	//
	netbuf_delete(inbuf);
}


/**
  *
  * @brief  Alternative implementation of web server task
  * @param  *arg
  * @retval None
  *
  *********************************************************************/
//static void websTask(void *arg)
//{
//	struct netconn *conn, *newconn;
//	err_t err, accept_err;
//
//	//
//	// Create a new TCP connection handle
//	//
//	conn = netconn_new(NETCONN_TCP);
//
//	if (conn!= NULL)
//	{
//		//
//		// Bind to port 80 (HTTP)
//		// with default IP address
//		//
//		err = netconn_bind(conn, IP_ADDR_ANY, 80);
//
//		if (err == ERR_OK)
//		{
//			//
//			// Put the connection into LISTEN state
//			//
//			netconn_listen(conn);
//
//			//
//			// Infinite loop
//			//
//			for(;;)
//			{
//				//
//				// accept any incoming connection
//				//
//				accept_err = netconn_accept(conn, &newconn);
//
//				if(accept_err == ERR_OK)
//				{
//					//
//					// serve connection
//					//
//					webServer(newconn);
//
//					//
//					// delete connection
//					//
//					netconn_delete(newconn);
//				}
//			}
//		}
//	}
//}

/**
  *
  * @brief  Creates the HTTP web server task
  * @param  *arg
  * @retval None
  *
  *********************************************************************/

//void websInit()
//{
//  sys_thread_new("webs_task", websTask, NULL, 4 * DEFAULT_THREAD_STACKSIZE, osPriorityNormal); //osPriorityHigh); //
//}


/**
  * @brief  SSI handler
  * @param  iIndex
  * @param 	*pcInsert
  * @param	*iInsertLen
  * @retval strlen(pcInsert)
  *
  *********************************************************************/

uint16_t SSI_Handler (int iIndex, char *pcInsert, int iInsertLen)
{
	switch (iIndex)
	{
	case 0:
//		sprintf(pcInsert, "%d", cnt++);
		sprintf(pcInsert, "%d", udp_tx.data.encoder_1.position.byte.HB);
		return strlen(pcInsert);
		break;
	case 1:
//		sprintf(pcInsert, "%d", cnt++);
		sprintf(pcInsert, "%d", udp_tx.data.encoder_1.speed.value);
		return strlen(pcInsert);
		break;
	case 2:
//		sprintf(pcInsert, "%d", cnt++);
		sprintf(pcInsert, "%d", udp_tx.data.encoder_1.status_1.value);
		return strlen(pcInsert);
		break;
	default :
		break;
	}

	return 0;
}


/**
  * @brief  this function must be defined somewhere in the
  * 		application, if the LWIP_HTTPD_CGI_SSI macro is set.
  * 		Refer to the httpd.h file line 114
  * @param  *file
  * @param 	uri
  * @param	iNumParams
  * @param	**pcParam
  * @param	**pcValue
  * @retval Nothing
  *
  *********************************************************************/
void httpd_cgi_handler(struct fs_file *file, const char* uri, int iNumParams, char **pcParam, char **pcValue)
{
	//
	// TODO: I don't know what to do here???????
	//
}

/**
  * @brief  CGI form handler
  * @param  iIndex
  * @param 	*iNumParams[]
  * @param	*pcValue[]
  * @retval
  *
  *********************************************************************/

//const char *CGIForm_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
//{
//	if (iIndex == 0)
//	{
//		for (int i=0; i<iNumParams; i++)
//		{
//			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
//			{
//				memset(name, '\0', 30);
//				strcpy(name, pcValue[i]);
//			}
//
//			else if (strcmp(pcParam[i], "lname") == 0)  // if the fname string is found
//			{
//				strcat(name, " ");
//				strcat(name, pcValue[i]);
//			}
//		}
//	}
//
//	return "/cgiform.html";
//}


/**
  * @brief  CGI form handler
  * @param  iIndex
  * @param 	*iNumParams[]
  * @param	*pcValue[]
  * @retval
  *
  *********************************************************************/

//const char *CGILED_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
//{
//	if (iIndex == 1)
//	{
//		for (int i=0; i<iNumParams; i++)
//		{
//			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
//			{
//				memset(name, '\0', 30);
//				strcpy(name, pcValue[i]);
//			}
//
//			else if (strcmp(pcParam[i], "lname") == 0)  // if the fname string is found
//			{
//				strcat(name, " ");
//				strcat(name, pcValue[i]);
//			}
//		}
//	}
//
//	return ""/cgiled.html";
//}
