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
 * File Name    : webs.h
 * Version      :
 * Description  :
 * Creation Date: Jan 10, 2022
 * Author		: KarimHmidi
 *********************************************************************/

#ifndef WEBS_WEBS_H_
#define WEBS_WEBS_H_

/*
 *
 * Includes
 *
 *********************************************************************/
#include "lwip/apps/httpd.h"
#include "lwip/api.h"


/*
 *
 * Prototypes
 *
 *********************************************************************/
void webServer(struct netconn *conn);
void websInit();
uint16_t SSI_Handler (int iIndex, char *pcInsert, int iInsertLen);
//void httpd_cgi_handler(struct fs_file *file, const char* uri, int iNumParams, char **pcParam, char **pcValue);
//const char *CGIForm_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
//const char *CGILED_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);


/*
 *
 * Defines
 *
 *********************************************************************/
//const tCGI FORM_CGI = {"/form.cgi", CGIForm_Handler};
//const tCGI LED_CGI = {"/led.cgi", CGILED_Handler};


#endif /* WEBS_WEBS_H_ */
