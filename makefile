CC = gcc
CFLAGS = -std=gnu99 -Wall

CODES=socketClient socketServer

.PHONY: all

all: $(CODES)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBS) 

socketClient:client.o logger.o socket.o frozen.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

socketServer:server.o logger.o socket.o frozen.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *~ *.o $(CODES)