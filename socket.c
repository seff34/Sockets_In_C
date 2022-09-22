#include "socket.h"

sockets_t serverCreate(socket_t *SOCKET)
{
    int localPort = SOCKET->port;

    if ((SOCKET->server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        logger(ERROR, "Socket error\n");
        return SOCKET_SERVER_CREATE_ERROR;
    }
    logger(INFO, "TCP server socket created.\n");

    memset(&SOCKET->server_addr, '\0', sizeof(struct sockaddr_in));
    SOCKET->server_addr.sin_family = AF_INET;
    SOCKET->server_addr.sin_port = htons(localPort);
    SOCKET->server_addr.sin_addr.s_addr = inet_addr(SOCKET->ip);

    if ((bind(SOCKET->server_sock, (struct sockaddr *)&SOCKET->server_addr, sizeof(struct sockaddr_in))) < 0)
    {
        logger(ERROR, "Bind error\n");
        return SOCKET_BIND_ERROR;
    }
    logger(INFO, "Bind to the port number: %d\n", localPort);

    listen(SOCKET->server_sock, 10);
    logger(INFO, "Listening...\n\n");

    return PROSES_SUCCESS;
}

sockets_t serverListen(socket_t *SOCKET,void (*DATA_PARSE)(char*))
{
    struct sockaddr_in client_addr;
    socklen_t addr_size;
    int client_sock;
    char buffer[1024];

    while (1)
    {     
        addr_size = sizeof(client_addr);
        client_sock = accept(SOCKET->server_sock, (struct sockaddr *)&client_addr, &addr_size);
        logger(INFO, "Client connected.\n");

        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        logger(INFO, "Client: %s\n", buffer);

        (*DATA_PARSE)(buffer);

        //Send Client
        //sendtoClient(SOCKET,client_sock,"Hello World %d",12);

        close(client_sock);
        logger(INFO, "Client disconnected.\n\n");
    }
    logger(WARNING, "Server Closed");
    close(SOCKET->server_sock);

    return PROSES_SUCCESS;
}

sockets_t setServer(socket_t *SOCKET,char* IP,int PORT)
{
    strcpy(SOCKET->ip,IP);
    SOCKET->port = PORT;
    return PROSES_SUCCESS;
}

sockets_t sendtoServer(socket_t *SOCKET,char *format, ...)
{
    int localPort = SOCKET->port;
    char buffer[1024];

    if ((SOCKET->server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        logger(ERROR, "Socket error\n");
        return SOCKET_CLIENT_CREATE_ERROR;
    }
    logger(INFO, "TCP client socket created.\n");

    memset(&SOCKET->server_addr, '\0', sizeof(struct sockaddr_in));
    SOCKET->server_addr.sin_family = AF_INET;
    SOCKET->server_addr.sin_port = htons(localPort);
    SOCKET->server_addr.sin_addr.s_addr = inet_addr(SOCKET->ip);

    if ( connect(SOCKET->server_sock, (struct sockaddr *)&SOCKET->server_addr, sizeof(struct sockaddr_in)) != PROSES_SUCCESS )
    {
        logger(ERROR,"TCP Server Socket not Found\n");
        return SOCKET_CONNECTION_ERROR;
    }
    logger(DEBUG,"Connected to the server.\n");

    bzero(buffer, 1024);
    va_list aptr;
    va_start(aptr, format);
    vsprintf(buffer, format, aptr);
    va_end(aptr);

    send(SOCKET->server_sock, buffer, strlen(buffer), 0);
    logger(INFO,"Client: %s\n", buffer);

    close(SOCKET->server_sock);
    logger(DEBUG,"Disconnected from the server.\n");

    return PROSES_SUCCESS;
}

sockets_t sendtoClient(socket_t *SOCKET,int clientSocket,char *format, ...)
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