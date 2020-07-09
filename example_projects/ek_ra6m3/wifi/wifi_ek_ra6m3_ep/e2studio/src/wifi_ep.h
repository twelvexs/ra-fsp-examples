/***********************************************************************************************************************
 * File Name    : wifi_ep.h
 * Description  : Contains declarations of data structures and functions used in wifi_ep.c.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#ifndef WIFI_EP_H_
#define WIFI_EP_H_

#include "wifi_thread.h"
#include "ctype.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define EP_INFO             "\r\nThe example project demonstrates the functionalities of WiFi_OnChip_Silex " \
		                    "\r\nrunning on Renesas RA MCUs using Renesas Silex UART Pmod hardware. " \
		                    "\r\nThe project gives user option to either scan WiFi networks or manually "\
		                    "\r\nenter network credentials in JlinkRTTViewer and connect. Then it performs "\
		                    "\r\nping operation on user entered URL or IP address.  If successful, "\
		                    "\r\n'Ping Successful'message printed on JlinkRTTViewer. The project also "\
		                    "\r\ndemonstrates TCP socket operations in client mode. It tries connecting to "\
		                    "\r\nthe user entered TCP server IP address and port number. It is expected "\
		                    "\r\nthat TCP socket in server mode would be running on user PC and listening "\
		                    "\r\non a free port before the EP tries to connect. Once connected to the TCP "\
		                    "\r\nserver, the user should send 'on' or 'off' message from the server. "\
		                    "\r\nBased on the message, on-board user LED would turn on/off and the same "\
                            "\r\nwould be displayed on JlinkRTTViewer. If an invalid message is received, "\
                            "\r\nthen previous LED state would be maintained. After receiving messages from "\
                            "\r\nthe server, appropriate acknowledgment  messages are sent to the server.\r\n"

/* Macros and variables for RTT operations */
#define BUFF_LEN                    (32U)
#define BYTES_RECEIVED_ZERO         (0U)

/* Macros and variables for network operations */
#define WIFI_MAX_TRY                (5U)
#define MAX_WIFI_SCAN_RESULTS       (20U)
#define PING_COUNT                  (4U)
#define PINT_INTERVAL_MS            (100U)
#define SOCKET_TCP                  (0U)
#define IPV4                        (4U)

/* Macros for WiFi operation Timeout */
#define WIFI_ONCHIP_SILEX_TIMEOUT_400MS                     (400U)
#define WIFI_ONCHIP_SILEX_TIMEOUT_15SEC                     (15000U)
#define WIFI_ONCHIP_SILEX_TIMEOUT_20SEC                     (20000U)

/* Macro for WiFi error return */
#define WIFI_ONCHIP_SILEX_ERR_ERROR                         (-1)

/* Converting from MCU byte-order to network byte-order */
#define SOCKETS_htonl( ulIn )    ( ( uint32_t ) ( ( ( ulIn & 0xFF ) << 24 ) | ( ( ulIn & 0xFF00 ) << 8 ) | ( ( ulIn & 0xFF0000 ) >> 8 ) | ( ( ulIn & 0xFF000000 ) >> 24 ) ) )

/* Macro for Menu Options */
#define SCAN_AP         (1U)
#define ENTER_SSID      (2U)
#define EXIT            (3U)

/* Macros for array indexing */
#define INDEX_ZERO      (0U)
#define INDEX_ONE       (1U)
#define INDEX_TWO       (2U)
#define INDEX_THREE     (3U)
#define IP_BUFF_LEN     (4U)

/* Structure for WiFi parameters */
typedef struct
{
    char ssid[BUFF_LEN];
    char pwd[BUFF_LEN];
    uint32_t security;
    uint8_t ip_addr_device[4];
    fsp_err_t status;
}WiFiParameters_t;

/* Structure for socket parameters */
typedef struct
{
    uint32_t id;
    uint32_t ip_addr_server;
    uint32_t port;
    uint8_t send_buff[BUFF_LEN];
    uint8_t recv_buff[BUFF_LEN];
    uint32_t status;
}SocketPrameters_t;

/***********************************************************************************************************************
 * User-defined APIs
 **********************************************************************************************************************/

/*
 * function declarations
 */
void user_input(char * user_buff);
fsp_err_t scan_and_select(void);
fsp_err_t manual_connect(void);
fsp_err_t dns_query(char * dns, uint8_t * ip_addr);
fsp_err_t ping(uint8_t * ip_addr);
fsp_err_t tcp_socket_create();
fsp_err_t tcp_socket_connect(uint32_t ip_addr, uint32_t port);
fsp_err_t tcp_send_data(uint8_t * p_data);
fsp_err_t tcp_recv_data(uint8_t * p_data);
fsp_err_t network_connectivity_check(void);
void wifi_deinit(void);

#endif /* WIFI_EP_H_ */
