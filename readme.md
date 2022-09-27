# Sockets in C

Socket Proses

## Extra Libs

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `frozen.c\h` | `Open Source Lib` | Json Library|
| `logger.c\h` | `My Lib` | Logger Library|
| `socket.c\h` | `My Lib` | Socket Library|


## Create TCP Server
```c
sockets_t serverCreate(socket_t* SOCKET);
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `SOCKET` | `socket_t*` | Socket Structure|


## Set TCP Socket
```c
sockets_t setServer(socket_t *SOCKET,char* IP,int PORT);
(char*));
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `SOCKET` | `socket_t*` | Socket Structure|
| `IP` | `char*` | Server Ip |
| `PORT` | `int` | Server Port|

## Listen TCP Socket
```c
sockets_t serverListen(socket_t *SOCKET,void (*DATA_PARSE)(char*));
```
| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `SOCKET` | `socket_t*` | Socket Structure|
| `(*DATA_PARSE)` | `void` | Data Parse Function |

## Send from Client to Server Data
```c
sockets_t sendtoServer(socket_t *SOCKET,char *format, ...);
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `SOCKET` | `socket_t*` | Socket Structure|
| `format` | `char *` | Data Format|
| `...` |`all type`   | Data|

## Send from Server to Client Data
```c
sockets_t sendtoClient(socket_t *SOCKET,int clientSocket,char *format, ...);
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `SOCKET` | `socket_t*` | Socket Structure|
| `clientSocket` | `int` | Client Socket Variable|
| `format` | `char *` | Data Format|
| `...` |`all type`   | Data|

## Download Code

Clone Project

```bash
  git clone https://github.com/seff34/Sockets-In-C
```


  
