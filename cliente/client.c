#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

//server parameters
#define SERVER_ADDRESS 	"127.0.0.1"
#define PORT 			8080

//search parameters
char source_id[60];
char dst_id[60];
char hour[60];
char answer[60];

void menu();
void selector();
int read_option();

int main(int argc, char const* argv[])
{
	/**/
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;

	//messages
	char * hello = "Hello from client";
	char buffer[1024] = { 0 };
	

	//sockect creation
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	//assign ip, port, protocol
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	//convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, SERVER_ADDRESS, &serv_addr.sin_addr)<= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	//show the menu options
	while(1){
		
		menu();

		//send search parameters to server
		send(sock, hello, strlen(hello), 0);
		//printf("Hello message sent\n");

		//receive answer
		valread = read(sock, buffer, 1024);
		//printf("%s\n", buffer);

		send(sock,source_id,strlen(source_id),0);
		//printf("source sent\n");
		valread = read(sock, buffer, 1024);
		//printf("%s\n", buffer);

		send(sock,dst_id,strlen(dst_id),0);
		//printf("dst sent\n");
		valread = read(sock, buffer, 1024);
		//printf("%s\n", buffer);

		send(sock,hour,strlen(hour),0);
		//printf("hout sent\n");
		valread = read(sock, answer, 60);
		printf("Mean: %s\n\n", answer);

	}

	//closing the connected socket
	close(client_fd);
	return 0;
}

void menu(){
	printf("1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora \n4. Buscar tiempo de viaje medio \n5. Salir\n \nSeleccione la opción: "); 
	selector();
}

void selector(){
	switch(read_option()){
        case 1:
			while(1){	
				fgets(source_id,60,stdin);
				int x = atoi(source_id);
				if(x<=1160 && x>0){
					break;
				}
				printf("Por favor, seleccione un valor entre 1 y 1160\n");
				printf("Source: ");
			}
			system("clear");
            menu();            
            break;
        case 2:
			while(1){	
				fgets(dst_id,60,stdin);
				int x = atoi(dst_id);
				if(x<=1160 && x>0){
					break;
				}
				printf("Por favor, seleccione un valor entre 1 y 1160\n");
				printf("Dst: ");
			}
			system("clear");
            menu();
            break;
        case 3:
            while(1){	
				fgets(hour,60,stdin);
				int x = atoi(hour);
				if(x<=24 && x>0){
					break;
				}
				printf("Por favor, seleccione un valor entre 1 y 24\n");
				printf("Hour: ");
			}
			system("clear");
            menu();
            break;
        case 4:
            printf("Buscando...\n");
            break;
        case 5:
            printf("Saliendo....");
            exit(EXIT_SUCCESS);
            break;
        default:
			printf("1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora \n4. Buscar tiempo de viaje medio \n5. Salir\n \nSeleccione la opción: "); 
            printf("Elija una opción válida: \n");
            selector();
    }
}

int read_option(){
    int *answer_option;
    answer_option = malloc(sizeof(int));
    scanf("%d", answer_option);
	system("clear");
    return *answer_option;
    free(answer_option);
}