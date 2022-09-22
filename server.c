#include "socket.h"
#include "frozen.h"

char* jsonObject = ".Datas";
char* jsonData1 = "{CodeID: %d}";
char* jsonData2 = "{Status: %d}";

void parser(char *buff)
{
    struct json_token token;
    int len = strlen(buff);
    int value0,value1;
    for (int i = 0; json_scanf_array_elem(buff, len,jsonObject, i, &token) > 0; i++)
    {
        json_scanf(token.ptr, token.len,jsonData1, &value0);
        json_scanf(token.ptr, token.len,jsonData2, &value1);
    }
    flogger(INFO,"Incoming Data {ID = %d Status = %d}\n",value0,value1);
}

int main(const int argc, const char *argv[])
{
    (void)argv;
    (void)argc;

    socket_t localSocket;
    setServer(&localSocket,"127.0.0.1",5000);

    serverCreate(&localSocket);
    serverListen(&localSocket,&parser);

    //sendtoServer(&localSocket,"{Datas: [{CodeID: %d,Status: %d}]}",25,152);

    return EXIT_SUCCESS;
}


