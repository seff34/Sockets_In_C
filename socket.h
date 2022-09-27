#ifndef __SOCKET__H
#define __SOCKET__H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "logger.h"

/*
socket_t localSocket;   
setServer(&localSocket,"127.0.0.1",5000);

//serverCreate(&localSocket);
//serverListen(&localSocket,&parser);

sendtoServer(&localSocket,"{Datas: [{CodeID: %d,Status: %d}]}",25,152);
*/

typedef struct
{
    struct sockaddr_in server_addr; 
    int server_sock;
    int port; 
    char ip[15];
}socket_t;

typedef int16_t sockets_t;

enum socketsReturns_t{
    PROSES_ERROR   = -1,
    PROSES_SUCCESS = 0,
    PROSES_FAIL    = 1,
    SOCKET_SERVER_CREATE_ERROR = 9601,
    SOCKET_CLIENT_CREATE_ERROR = 9602,
    SOCKET_BIND_ERROR = 9603,
    SOCKET_CONNECTION_ERROR = 9604
}; 

/**
 * @brief  Create TCP Server
 * @param  [in] SOCKET Struct
 * @return [int16_t] Function Execute Result
 * @retval [socketsReturns_t] Look Function Retvals
 */
sockets_t serverCreate(socket_t *SOCKET);

/**
 * @brief  Set TCP Server
 * @param  [in] SOCKET Struct
 * @param  [in] IP Server IP
 * @param  [in] PORT Server Port 
 * @return [int16_t] Function Execute Result
 * @retval [socketsReturns_t] Look Function Retvals
 */
sockets_t setServer(socket_t *SOCKET,char* IP,int PORT);

/**
 * @brief  Listen TCP Server
 * @param  [in] SOCKET Struct
 * @param  [in] DATA_PARSE Parse Function 
 * @return [int16_t] Function Execute Result
 * @retval [socketsReturns_t] Look Function Retvals
 */
sockets_t serverListen(socket_t *SOCKET,void (*DATA_PARSE)(char*));

/**
 * @brief  Send from Client to Server Data
 * @param  [in] SOCKET Struct
 * @param  [in] format Send Arguments
 * @return [int16_t] Function Execute Result
 * @retval [socketsReturns_t] Look Function Retvals
 */
sockets_t sendtoServer(socket_t *SOCKET,char *format, ...);

/**
 * @brief  Send from Server to Client Data
 * @param  [in] SOCKET Struct
 * @param  [in] clientSocket Client Socket Variable
 * @param  [in] format Send Arguments
 * @return [int16_t] Function Execute Result
 * @retval [socketsReturns_t] Look Function Retvals
 */
sockets_t sendtoClient(socket_t *SOCKET,int clientSocket,char *format, ...);


#endif