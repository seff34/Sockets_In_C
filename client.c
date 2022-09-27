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

    socket_t localSocket;
    setServer(&localSocket,IP,PORT);

    sendtoServer(&localSocket,"{Datas: [{CodeID: %d,Status: %d}]}",25,152);

    return EXIT_SUCCESS;
}


