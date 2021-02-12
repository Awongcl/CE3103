#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

// Error message
void error(char *m){
	perror(m);
}

int main(int argc, char *argv[]){
	int sockfd, newsockfd, port, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	if (argc < 2)
		error("Error, no port provided\n");
	// Convert stringto interger
	port = atoi(argv[1]);
	// socket returns a non-negative value if success
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    		error("setsockopt(SO_REUSEADDR) failed");
	if(sockfd < 0)
		error("Error opening socket");
	// Copy 0's to address of serv_address 
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	//  
	serv_addr.sin_family = AF_INET;
	// INADDR_ANY binds to all available interfaces
	serv_addr.sin_addr.s_addr = INADDR_ANY;  //struct sin_addr -> unsigned long s_addr
	serv_addr.sin_port = htons(port); //  host to network
	// htons converts unsigned short integer to network byte order
	// Returns -1 id binding fails
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Error binding to socket\n");
	printf("Server is listening on port %i \n",port);
	listen(sockfd,2); // Backlog = 2, maax length of queue of pending connections
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd < 0)
		error("Error on accept");
	n = read(newsockfd, buffer, 255);
	if (n < 0)
		error("Error reading from socket\n");
	printf("Message received: %s\n", buffer);
	int result = atoi(buffer);
	result =  result*5;    
	result = htons(result);
	printf("%d\n",ntohs(result));
	//printf(&result);
	n = write(newsockfd,&result,sizeof(result));
	if(n<0)
		error("Error writing back to socket\n");

	return 0;
}
