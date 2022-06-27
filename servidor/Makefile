CC = gcc
CFLAGS = -g -Wall -pthread
SERVER = server

all: $(SERVER) 

$(SERVER) :$(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

clean:
	$(RM) $(server) 