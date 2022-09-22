#!/bin/bash

#arm-linux-gnueabihf-gcc main.c logger.c socket.c -o client -std=gnu99 -Wall -Wextra -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16 -mthumb -lrt -lm -lpthread
gcc server.c logger.c socket.c frozen.c -o socketServer -std=gnu99 -Wall
gcc client.c logger.c socket.c frozen.c -o socketClient -std=gnu99 -Wall
