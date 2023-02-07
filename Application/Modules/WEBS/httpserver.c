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
 * File Name    : httpsserver.c
 * Version      :
 * Description  :
 * Creation Date: Jan 01, 2023
 * Author		: KarimHmidi
 *********************************************************************/

/*
 *
 * Includes
 *
 *********************************************************************/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include <stdio.h>
#include "httpserver.h"
#include "cmsis_os.h"

/*
 *
 * Defines
 *
 **********************************************************************/
//#define CAN2_ZMV_SIMULATION 1



/*
 *
 * Variable defines
 *
 **********************************************************************/
char colour;


/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * @brief  HTTP Web server
  * @param  *arg
  * @retval None
  *
  *********************************************************************/
static void webServer(struct netconn *conn)
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
			// Get the data pointer
			// and length of the data
			// inside a netbuf
			//
			netbuf_data(inbuf, (void**)&buf, &buflen);

			//
			// Check if request
			// to get the index.html
			//
			if (strncmp((char const *)buf,"GET /index.html",15)==0)
			{
				fs_open(&file, "/index.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

			if (strncmp((char const *)buf,"GET /styles.css",15)==0)
			{
				fs_open(&file, "/styles.css");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

//			if (strncmp((char const *)buf,"GET /img/stm32.jpg",18)==0)
//			{
//				fs_open(&file, "/img/stm32.jpg");
//				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
//				fs_close(&file);
//			}

//			if (strncmp((char const *)buf,"GET /img/logo.jpg",17)==0)
//			{
//				fs_open(&file, "/img/logo.jpg");
//				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
//				fs_close(&file);
//			}

//			if (strncmp((char const *)buf,"GET /buttoncolor=",17)==0)
//			{
//				colour = buf[17];
//			}
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
	// Delete the buffer
	// (netconn_recv gives
	// us ownership, so we have
	// to make sure to deallocate
	// the buffer)
	//
	netbuf_delete(inbuf);
}


/**
  *
  * @brief  HTTP web server task
  * @param  *arg
  * @retval None
  *
  *********************************************************************/
static void websTask(void *arg)
{
	struct netconn *conn, *newconn;
	err_t err, accept_err;

	//
	// Create a new TCP connection handle
	//
	conn = netconn_new(NETCONN_TCP);

	if (conn!= NULL)
	{
		//
		// Bind to port 80 (HTTP)
		// with default IP address
		//
		err = netconn_bind(conn, IP_ADDR_ANY, 80);

		if (err == ERR_OK)
		{
			//
			// Put the connection into LISTEN state
			//
			netconn_listen(conn);

			//
			// Infinite loop
			//
			for(;;)
			{
				//
				// accept any incoming connection
				//
				accept_err = netconn_accept(conn, &newconn);

				if(accept_err == ERR_OK)
				{
					//
					// serve connection
					//
					webServer(newconn);

					//
					// delete connection
					//
					netconn_delete(newconn);
				}
			}
		}
	}
}

/**
  *
  * @brief  Creates the HTTP web server task
  * @param  *arg
  * @retval None
  *
  *********************************************************************/

void websInit()
{
  sys_thread_new("webs_task", websTask, NULL, 2 * DEFAULT_THREAD_STACKSIZE, osPriorityNormal);
}
