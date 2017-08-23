/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr;
	int numOfline = 0;
	char recvline[1000];

	if (argc != 3){
		printf("usage: %s <IP address> <Number of lines>\n",argv[0]);
		return -1;
	}

	numOfline = atoi(argv[2]);
	char str[15];	
	sprintf(str, "%d", numOfline);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(32000);

	sendto(sockfd, str, strlen(str), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

	n = recvfrom(sockfd,recvline,10000,0,NULL,NULL);	
	printf("%s\n", recvline);
	printf("%c\n", recvline[0]);
	printf("%c\n", recvline[1]);
	printf("%c\n", recvline[2]);

	if (recvline[0] == 'a' && recvline[1] == 'c' && recvline[2] == 'k') {
		char msg[] = "Client Messege";
		sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

		n = recvfrom(sockfd,recvline,10000,0,NULL,NULL);
		recvline[n] = 0;
		printf("%s\n",recvline);
	}
	
	return 0;
}