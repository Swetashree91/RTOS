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
	FILE *fp;

	int opt = 1; 
	int master_s , len , new_s , client_s[5] , activity, i , readvalue , sockd; 
	int max; 
	struct sockaddr_in address; 
	char response[100] = "\n Hi There!!!\n";	
	char buffer[100] = "\0"; 
	
	fd_set readfds; 
	
	for (i = 0; i < 5; i++) 
	{ 
		client_s[i] = 0; 
	} 
	
	if( (master_s = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	if( setsockopt(master_s, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 ) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT ); 
		
	if (bind(master_s, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}  
	
	if (listen(master_s, 5) < 0) 
	{ 
		perror("listen FAILED"); 
		exit(1); 
	} 
		 
	len = sizeof(address); 
	printf("\nWaiting for connections ..."); 
		
	while(1) 
	{ 
		FD_ZERO(&readfds); 
		FD_SET(master_s, &readfds); 
		max = master_s; 
	 
		for ( i = 0 ; i < 5 ; i++) 
		{ 
			sockd = client_s[i]; 
			if(sockd > 0) 
				FD_SET( sockd , &readfds); 
			
			if(sockd > max) 
				max = sockd; 
		} 
	
		activity = select( max + 1 , &readfds , NULL , NULL , NULL); 
	
		if ((activity < 0) && (errno!=EINTR)) 
		{ 
			printf("\nselect error"); 
		} 
	
		if (FD_ISSET(master_s, &readfds)) 
		{ 
			if ((new_s = accept(master_s,(struct sockaddr *)&address, (socklen_t*)&len))<0) 
			{ 
				perror("\naccept error."); 
				exit(1); 
			} 
			
			printf("New connection \n 1)socket fd is %d , \n2)ip is : %s , \n3)port : %d \n" , new_s , inet_ntoa(address.sin_addr), ntohs (address.sin_port));
			if( send(new_s, buffer, strlen(buffer), 0) != strlen(buffer) ) 
			{ 
				perror("\nsend error"); 
				exit(1);
			} 
			memset(buffer,0,sizeof(buffer));		 
			for (i = 0; i < 5; i++) 
			{ 
				if( client_s[i] == 0 ) 
				{ 
					client_s[i] = new_s; 	
					break; 
				} 
			} 
		} 
		
		for (i = 0; i < 5; i++) 
		{ 
			sockd = client_s[i]; 
				
			if (FD_ISSET(sockd,&readfds)) 
			{ 
				memset(buffer,0,sizeof(buffer));
				readvalue = read(sockd,buffer,1024);
				if(readvalue == 0)
				
				{ 
					getpeername(sockd , (struct sockaddr*)&address ,(socklen_t*)&len); 
					close(sockd); 
					client_s[i] = 0; 
				} 
				else
				{ 	
					fp = fopen(buffer, "r");
					if(!fp) {
						printf("\nFile  %s is not there!\n",buffer);
						memset(buffer,0,sizeof(buffer));
						strcpy(buffer,"NIL");
						send(sockd , buffer , strlen(buffer) , 0 ); 
						memset(buffer,0,sizeof(buffer));
						continue;
						}
					
					fscanf(fp,"%[^\t\n]", buffer);
					fclose(fp);
					buffer[readvalue] = '\0'; 
					send(sockd , buffer , sizeof(buffer) , 0 );
					memset(buffer,0,sizeof(buffer));
					
				} 
			 } 
		} 
	
	} 
	
	return 0; 
} 
