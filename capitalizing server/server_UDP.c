/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void convertToUpperCase(char *sPtr) {
  	while(*sPtr != '\0') {
     	if (islower(*sPtr))
          *sPtr = toupper(*sPtr);
   	}
}

int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	//char reply[1000];
	char ackMsg[] = "ack";
	int numOfLines = 0;
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//create a socket
	
	servaddr.sin_family = AF_INET;	//address family	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//IP address in the network byte order
	servaddr.sin_port = htons(32000);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);

	n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);
	sendto(sockfd,ackMsg,3,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

	printf("mesg = %s\n", mesg);
	numOfLines = atoi(mesg);	
	printf("numOfLines = %d\n", numOfLines);

	while (numOfLines > 0) {	
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);
		convertToUpperCase(mesg);
				
		sendto(sockfd,mesg,n,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		
		numOfLines--;
	}

	return 0;
}