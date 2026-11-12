#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4242
#define HOST "192.168.1.190" // Macbook 192.168.1.190
#define BUF_SIZE 64
#define BACKLOG_SIZE 6


int main(void){

	// create IP4 stream socket
	int sockfd_listen;
	if ((sockfd_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error on socket creation");
		exit(EXIT_FAILURE);
    }

	// define address for socket
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));       // met à zéro tous les champs
	address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, HOST, &address.sin_addr) <= 0) {
	    perror("Error on inet_pton (defining address)");
	   	exit(EXIT_FAILURE);
    }



	// bind socket and address together
	int status = bind(sockfd_listen, (struct sockaddr *)&address, sizeof(address));
	if (status!=0) perror("Error on binding listening socket\n");

	// listening for clients
	status = listen(sockfd_listen, BACKLOG_SIZE);
	if (status!=0) perror("Error on listen call\n");
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
				ssize_t n = recv(sockfd, buf, BUF_SIZE-1, 0);
				if(n==0) break; // connection terminated
				buf[n] = '\0';
				printf("Pid %d : %s", getpid(), buf);

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
