#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>


#define HOST "127.0.0.1"
#define PORT "4242"
#define BUF_SIZE 64


void handle_errors(int status, char* message){
	if (status!=0){
			fprintf(stderr, "%s : %s\n", message, strerror(errno));
			abort();
		}
}


int main(int argc, char *argv[]){


	// define server_info hints
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	// get server_info
	struct addrinfo *server_info;
	int status = getaddrinfo(HOST, PORT, &hints, &server_info);
	handle_errors(status, "Error on getaddrinfo");

	// create socket
	int sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	status = connect(sockfd, server_info->ai_addr, server_info->ai_addrlen);
	handle_errors(status, "Error on connect");

	printf("Connected.\n");
	char buf[BUF_SIZE];

	for(;;){

		if (argc>1){
			printf("Sending Bonjour\n");
			strcpy(buf, "Bonjour\n");
			send(sockfd, buf, BUF_SIZE-1, 0);
			sleep(1);
		}
		else {
			fgets(buf, BUF_SIZE, stdin);
			send(sockfd, buf, BUF_SIZE-1, 0);
		}

	}



	// cleanup
	//freeaddrinfo(&hints);
	close(sockfd);


	return EXIT_SUCCESS;
}
