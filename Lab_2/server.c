#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

void error(char *m){
	perror(m);
}

int main(int argc, char *argv[]){
	int sockfd, newsockfd, port, client,  n;
	char buffer[256];
	struct sockaddr_in serv_addr, client_addr;
	if (argc < 2)
		error("Error, no port provided\n");
	port = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Error opening socket");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port); //  host to network

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Error binding to socket\n");
	printf("Server is listening");
}
