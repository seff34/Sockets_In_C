#include "socket.h"
#include "frozen.h"

int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        logger(ERROR,"%s <Server Ip> <Server Port>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    char* IP = (char*)malloc(sizeof(char) * 15);
    strcpy(IP,argv[1]);
    int PORT = atoi(argv[2]);

    clientInit_t* localSocket = NEW_CLIENT_INIT(IP,PORT);
    localSocket->Create(localSocket);
    localSocket->SendToServer(localSocket,"{{Datas:[CodeID: %d,Status: %d]}}",12,24);

    return EXIT_SUCCESS;
}


