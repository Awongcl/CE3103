#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

// Error message
void error(char *m){
	perror(m);
	exit(0);
}

int main(int argc, char *argv[]){
	int sockfd, port, n;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;   // Host entity
	
	if (argc < 3)    // [hostname] [port] 
		error("Error, no port provided\n");
	// Convert stringto interger
	port = atoi(argv[2]);
	//printf("%i\n",port);
	// socket returns a non-negative value if success
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Error opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL)
		error("Error, no such host\n");
	// Start with a clean address structure
	memset((char *) &serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET; // Internet socket
	bcopy ((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port); //  host to network
	// htons converts unsigned short integer to network byte order
	// Returns -1 id binding fails
	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
		error("Error connecting to server\n");
	printf("Please enter the message\n");
	fgets(buffer,255,stdin);
	// Send data to server
	n = write(sockfd, buffer, strlen(buffer));
	if(n < 0)  // returns 0 if success
		error("Error writing to server\n");
	n = read(sockfd, buffer, 255);
	if(n < 0)
		error("Error reading from server\n");
	printf("Result after multiplying by 5: %s\n",buffer);
	return 0;
}
