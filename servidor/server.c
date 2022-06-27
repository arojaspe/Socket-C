#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <arpa/inet.h>

//add headers 
#include "node.h"
#include "search.h"


//server parameters
#define PORT 			8080
#define SERVER_ADDRESS	"127.0.0.1"
#define BUF_SIZE        100


//buffer for differents variables
char buffer[1024] = { 0 };
char * hello = "Hello from server";
char source_id[60];
char dst_id[60];
char hour[60];
char answer[60];

//definition thread function
void *connection_handler(void *);

int main(int argc, char const* argv[])
{
	//listening socket and connection socket file descriptors
	int server_fd, new_socket, valread; 
	struct sockaddr_in address;         
	int opt = 1;
	int addrlen = sizeof(address);

	//creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,sizeof(address))< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	//set the socket for listening (queue backlog of 3)
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	//array for several threads 
	pthread_t thread_id[40];
    int i = 0;

    while(1){

		//accept socket connetion from one new client
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) {
    		perror("accept");
		    exit(EXIT_FAILURE);
	    }

		//create one new thread for each new client
		int * newsock = malloc(sizeof(int));
		* newsock = new_socket;
    	pthread_create(&thread_id[i++], NULL, connection_handler, newsock);
		pthread_detach(thread_id[i++]);

		//condition only 32 clients at the same time 
		if(i >= 32){
          i = 0;
          while(i < 32){
            pthread_join(thread_id[i++],NULL);
          }
          i = 0;
        }

	    //printf("Answer message sent\n");
        // closing the connected socket
	    //close(new_socket);
    }
	
	// closing the listening socket
	//shutdown(server_fd, SHUT_RDWR);

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	return 0;
}


void *connection_handler(void *socket_desc){

	int valread;

    //Get the socket descriptor
    int new_socket = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];

	while(1){
		
		//message for to check 
		valread = read(new_socket, buffer, 1024);
		printf("%s\n", buffer);
		send(new_socket, hello, strlen(hello), 0);
		//printf("Hello message sent\n");

		//read origin id from client
		valread = read(new_socket,source_id,60);
		int source = atoi(source_id);
		printf("Source: %d\n",source);
		send(new_socket, hello, strlen(hello), 0);
		//printf("Hello message sent\n");

		//read destination id from client
		valread = read(new_socket,dst_id,60);
		int dst = atoi(dst_id);
		printf("Dst: %d\n",dst);
		send(new_socket, hello, strlen(hello), 0);
		printf("Hello message sent\n");

		//read hour from client
		valread = read(new_socket,hour,60);
		int timeHour = atoi(hour);
		printf("Hour: %d\n",timeHour);

		//Getting the time for each query 
		char tim[128];
		time_t rawtime = time(NULL);
		struct tm *ptm = localtime(&rawtime);
		strftime(tim, 124, "%Y-%m-%dT%H:%M:%S", ptm);

		//Getting ip from client socket 
		struct sockaddr_in * pV4Addr = (struct sockaddr_in*)&new_socket;
		struct in_addr ipAddr = pV4Addr->sin_addr;
		char strip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &ipAddr, strip,INET_ADDRSTRLEN );

		//write to server log file
		FILE * file = fopen("log.txt","a");
		fprintf(file,"[Fecha %s] Cliente [%s] [búsqueda - %d - %d - %d]\n",tim,strip,source,dst,timeHour);
		fclose(file);

		//search in binary file  source/dst/hour
		int ret = snprintf(answer, sizeof answer, "%f", searchMean(source,dst,timeHour));
		send(new_socket, answer, strlen(answer), 0);

		if(read_size == 0){
        	puts("Client disconnected");
        	fflush(stdout);
    	}

	    else if(read_size == -1){
    	    perror("recv failed");
    	}
	}    
    return 0;
} 
