CC = gcc
CFLAGS = -g -Wall
CLIENT = client

all: $(CLIENT) 

$(CLIENT) :$(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT).c

clean:
	$(RM) $(CLIENT) a