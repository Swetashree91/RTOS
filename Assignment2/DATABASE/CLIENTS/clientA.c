#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> 	 

#define PORT 8090 

int main() 
{ 
	struct timeval t1,t2;	
	int sock;
	struct sockaddr_in server;
	char message[100] , server_reply[100];
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("\nCould not create socket");
	}
	printf("\nSocket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8090 );

	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("\nconnection failed.");
		exit(1);
	}
	
	printf("\nconnected\n");
	
	while(1)
	{
		printf("\nEnter file name : ");
		scanf("%s" , message);
		gettimeofday(&t1,NULL);

		if( send(sock , message , sizeof(message) , 0) < 0)
		{
			printf("\nSend failed");
			return -1;
		}
		memset(server_reply,0,sizeof(server_reply));
		
		if(recv(sock , server_reply , 1024 , 0) < 0)
		{
			printf("\nreceive failed");
			break;
		}
		gettimeofday(&t2,NULL);
		printf("\nServer reply : %s",server_reply);
		memset(server_reply,0,sizeof(server_reply));
		printf("\ntime by A:%lu",t2.tv_usec-t1.tv_usec);
	}
	
	close(sock);
	return 0;
}




	
