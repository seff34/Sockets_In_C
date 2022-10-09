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

typedef struct
{
    struct sockaddr_in server_addr; 
    int server_sock;
    int port; 
    char *ip;
}socket_t;

typedef struct SOCKET_SERVER
{
    socket_t socketValues;
    int(*Create)(void*);
    int(*Listen)(void*,void(char*));
    int(*Close)(void*);
    int(*SendToClient)(int,char*,...);
}serverInit_t;

typedef struct SOCKET_CLIENT
{
    socket_t socketValues;
    int(*Create)(void*);
    int(*SendToServer)(void*,char*,...);
}clientInit_t;

enum socketsReturns_t{
    SOCKET_SUCCESS = 0,
    SOCKET_SERVER_CREATE_ERROR = 9601,
    SOCKET_CLIENT_CREATE_ERROR = 9602,
    SOCKET_BIND_ERROR = 9603,
    SOCKET_CONNECTION_ERROR = 9604
}; 

serverInit_t* NEW_SERVER_INIT(char* IP,int PORT);
clientInit_t* NEW_CLIENT_INIT(char* IP,int PORT);

/*
    serverInit_t* localSocket = NEW_SERVER_INIT("localhost",5002);
    localSocket->Create(localSocket);
    localSocket->Listen(localSocket);
    localSocket->Close(localSocket);

    clientInit_t* localSocket2 = NEW_CLIENT_INIT("localhost",5002);
    localSocket2->Create(localSocket2);
    localSocket2->SendToServer(localSocket2,"Hello World %d",13232);
*/


#endif