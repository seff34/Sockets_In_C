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

enum {
    PROSES_ERROR   = -1,
    PROSES_SUCCESS = 0,
    PROSES_FAIL    = 1,
    SOCKET_SERVER_CREATE_ERROR = 9601,
    SOCKET_CLIENT_CREATE_ERROR = 9602,
    SOCKET_BIND_ERROR = 9603,
    SOCKET_CONNECTION_ERROR = 9604
}socketsReturns_t; 

sockets_t serverCreate(socket_t *SOCKET);
sockets_t sendtoServer(socket_t *SOCKET,char *format, ...);
sockets_t serverListen(socket_t *SOCKET,void (*DATA_PARSE)(char*));
sockets_t setServer(socket_t *SOCKET,char* IP,int PORT);
sockets_t sendtoClient(socket_t *SOCKET,int clientSocket,char *format, ...);


#endif