#include "socket.h"
#include "frozen.h"

char* jsonObject = ".Datas";
char* jsonData1 = "{CodeID: %d}";
char* jsonData2 = "{Status: %d}";

void parser(char *buff)
{
    struct json_token token;
    int len = strlen(buff);
    int value0 = 0 ; 
    int value1 = 0 ;
    for (int i = 0; json_scanf_array_elem(buff, len,jsonObject, i, &token) > 0; i++)
    {
        json_scanf(token.ptr, token.len,jsonData1, &value0);
        json_scanf(token.ptr, token.len,jsonData2, &value1);
        logger(INFO,"Incoming Data {ID = %d Status = %d}\n",value0,value1);
    }
}

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

    serverInit_t* localSocket = NEW_SERVER_INIT(IP,PORT);
    localSocket->Create(localSocket);
    localSocket->Listen(localSocket,parser);
    localSocket->Close(localSocket);


    return EXIT_SUCCESS;
}


