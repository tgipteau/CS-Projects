#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "4242"
#define BUF_SIZE 64
#define BACKLOG_SIZE 6

// Macbook 192.168.1.190

void handle_errors(int status, char* message){
	if (status!=0){
			fprintf(stderr, "%s : %s\n", message, strerror(errno));
			abort();
		}
}

int main(void){

	// define self_info hints
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE; // Passive Open for server side
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	// get self_info
	struct addrinfo *self_info;
	int status = getaddrinfo(NULL, PORT, &hints, &self_info);
	handle_errors(status, "Error on getaddrinfo");


	// create listen socket
	int sockfd_listen = socket(self_info->ai_family, self_info->ai_socktype, self_info->ai_protocol);

	status = bind(sockfd_listen, self_info->ai_addr, self_info->ai_addrlen);
	handle_errors(status, "Error on binding listening socket");

	// listening for clients
	status = listen(sockfd_listen, BACKLOG_SIZE);
	handle_errors(status, "Error on listen call");
	printf("Listening started.\n");

	char buf[BUF_SIZE];

	for(;;){
		// parent accepts and sends to children
		printf("Pid %d : Waiting on accept...\n", getpid());
		sleep(1);
		int sockfd = accept(sockfd_listen, NULL, NULL);
		pid_t pid = fork();


		if (pid==0){
			printf("Accepted connection on pid %d\n", getpid());
			// child closes listen socket, handles communication
			close(sockfd_listen);

			for (;;){

				// recv loop
				/* ssize_t n = recv(sockfd, buf, BUF_SIZE-1, 0);
				if(n==0) break; // connection terminated
				buf[n] = '\0';
				printf("Pid %d : %s", getpid(), buf);*/

				printf("Red or green : ");
				scanf("%s", buf);
				send(sockfd, buf, BUF_SIZE, 0);

			}

			printf("Pid %d : Disconnected\n", getpid());

			close(sockfd); // disconnected.
			exit(0);
		}


	}

	// cleanup
	close(sockfd_listen);

	return EXIT_SUCCESS;
}
