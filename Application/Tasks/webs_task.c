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
 * File Name    : webs_task.c
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
#include <string.h>
#include <stdio.h>
#include "fs.h"

//WR
/* #include "typedefs.h" */
#include "../Common/typedefs.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"

//WR
/* #include "webs.h" */
#include "../Modules/WEBS/webs.h"
	
#include "cmsis_os.h"

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

osThreadId_t websTaskHandle;
const osThreadAttr_t websTask_attributes = {
  .name = "websTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};



/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * @brief  Function implementing the websTask thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void websTask(void *argument)
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
