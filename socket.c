#include "socket.h"

static int sendtoClient(int clientSocket,char *format, ...)
{
    char buffer[1024];
    bzero(buffer, 1024);
    va_list aptr;
    va_start(aptr, format);
    vsprintf(buffer, format, aptr);
    va_end(aptr);

    send(clientSocket, buffer, strlen(buffer), 0);
    logger(INFO,"Server: %s\n", buffer);
    return EXIT_SUCCESS;
}
static int serverCreate(void *NEW_SOCKET)
{
    serverInit_t* SOCKET = (serverInit_t*)NEW_SOCKET; 
    if ((SOCKET->socketValues.server_sock = socket(AF_INET, SOCK_STREAM, 0))< 0 )
    {
        logger(ERROR, "Socket Error\n");
        return SOCKET_SERVER_CREATE_ERROR;
    }
    logger(DEBUG, "TCP server socket created.\n");

    memset(&SOCKET->socketValues.server_addr, '\0', sizeof(struct sockaddr_in));
    SOCKET->socketValues.server_addr.sin_family = AF_INET;
    SOCKET->socketValues.server_addr.sin_port = htons(SOCKET->socketValues.port);
    SOCKET->socketValues.server_addr.sin_addr.s_addr = inet_addr(SOCKET->socketValues.ip);

    if ((bind(SOCKET->socketValues.server_sock, (struct sockaddr *)&SOCKET->socketValues.server_addr, sizeof(struct sockaddr_in))) < 0)
    {
        logger(ERROR, "Bind error\n");
        return SOCKET_BIND_ERROR;
    }
    logger(INFO, "Bind to the port number: %d\n", SOCKET->socketValues.port);

    listen(SOCKET->socketValues.server_sock, 10);
    logger(INFO, "Listening...\n\n");

    return SOCKET_SUCCESS;
}
static int serverListen(void *NEW_SOCKET,void(*DATA_PARSER)(char*))
{
    serverInit_t* SOCKET = (serverInit_t*)NEW_SOCKET; 

    struct sockaddr_in client_addr;
    socklen_t addr_size;
    int client_sock;
    char buffer[1024];

    while (1)
    {     
        addr_size = sizeof(client_addr);
        client_sock = accept(SOCKET->socketValues.server_sock, (struct sockaddr *)&client_addr, &addr_size);
        logger(INFO, "Client connected.\n");

        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        logger(INFO, "Client: %s\n", buffer);
        (*DATA_PARSER)(buffer);
        //Send Client
        //SOCKET->SendToClient(client_sock,"Hello World %d",12);
        close(client_sock);
        logger(INFO, "Client disconnected.\n\n");
    }
    logger(WARNING, "Server Closed");
    close(SOCKET->socketValues.server_sock);

    return SOCKET_SUCCESS;
}
static int serverClose(void *NEW_SOCKET)
{
    serverInit_t* SOCKET = (serverInit_t*)NEW_SOCKET; 
    close(SOCKET->socketValues.server_sock);
    return 0 ;
}
serverInit_t* NEW_SERVER_INIT(char* IP,int PORT)
{
    serverInit_t* NEW_SOCKET = (serverInit_t*)calloc(1,sizeof(serverInit_t));
    if (NEW_SOCKET == NULL)
    {
        printf("Allocation Error\n");
        return NULL;
    }
    
    if ((strcmp(IP,"localhost") == 0 ) || (strcmp(IP,"LOCALHOST")) == 0 )
        NEW_SOCKET->socketValues.ip = "127.0.0.1";
    else if ((strcmp(IP,"public") == 0 ) || (strcmp(IP,"PUBLIC")) == 0)
        NEW_SOCKET->socketValues.ip = "0.0.0.0";
    else 
        NEW_SOCKET->socketValues.ip = IP;

    NEW_SOCKET->socketValues.port = PORT;
    NEW_SOCKET->Create = serverCreate;
    NEW_SOCKET->Listen = serverListen;
    NEW_SOCKET->Close = serverClose;
    NEW_SOCKET->SendToClient = sendtoClient;
    
    return NEW_SOCKET;
}

static int createClient(void* NEW_CLIENT)
{
    clientInit_t* CLIENT = (clientInit_t*)NEW_CLIENT;
    if ((CLIENT->socketValues.server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        logger(ERROR, "Socket error\n");
        return SOCKET_CLIENT_CREATE_ERROR;
    }
    
    logger(DEBUG, "TCP client socket created.\n");

    memset(&CLIENT->socketValues.server_addr, '\0', sizeof(struct sockaddr_in));
    CLIENT->socketValues.server_addr.sin_family = AF_INET;
    CLIENT->socketValues.server_addr.sin_port = htons(CLIENT->socketValues.port);
    CLIENT->socketValues.server_addr.sin_addr.s_addr = inet_addr(CLIENT->socketValues.ip);

    return SOCKET_SUCCESS;
}
static int sendtoServer(void* NEW_CLIENT,char *format, ...)
{
    clientInit_t* CLIENT = (clientInit_t*)NEW_CLIENT;
    if ( connect(CLIENT->socketValues.server_sock,(struct sockaddr *)&CLIENT->socketValues.server_addr, sizeof(struct sockaddr_in)) != SOCKET_SUCCESS )
    {
        logger(ERROR,"TCP Server Socket not Found\n");
        return SOCKET_CONNECTION_ERROR;
    }
    char buffer[1024] = { 0 };

    va_list aptr;
    va_start(aptr, format);
    vsprintf(buffer, format, aptr);
    va_end(aptr);
    
    send(CLIENT->socketValues.server_sock, buffer, strlen(buffer), 0);

    logger(INFO,"Client: %s\n", buffer);
    
    close(CLIENT->socketValues.server_sock);
    logger(DEBUG,"Disconnected from the server.\n");
    return SOCKET_SUCCESS;
}
clientInit_t* NEW_CLIENT_INIT(char* IP,int PORT)
{
    clientInit_t* NEW_SOCKET = (clientInit_t*)calloc(1,sizeof(clientInit_t));
    if (NEW_SOCKET == NULL)
    {
        printf("Allocation Error\n");
        return NULL;
    }
    
    if ((strcmp(IP,"localhost") == 0 ) || (strcmp(IP,"LOCALHOST") == 0))
        NEW_SOCKET->socketValues.ip = "127.0.0.1";
    else if ((strcmp(IP,"public") == 0 ) || (strcmp(IP,"PUBLIC") == 0))
        NEW_SOCKET->socketValues.ip = "0.0.0.0";
    else 
        NEW_SOCKET->socketValues.ip = IP;

    NEW_SOCKET->socketValues.port = PORT;
    NEW_SOCKET->Create = createClient;
    NEW_SOCKET->SendToServer = sendtoServer;

    return NEW_SOCKET;
}
