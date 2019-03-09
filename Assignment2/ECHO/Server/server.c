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
	int opt = 1; 
	int master_s , len , new_s , client_socket[5] , activity, i , valread , sd; 
	int max; 
	struct sockaddr_in address; 
		
	char buffer[5]; 
	
	fd_set readfds; 
	
	char *message;
	
	for (i = 0; i < 5; i++) 
	{ 
		client_socket[i] = 0; 
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
			sd = client_socket[i]; 
			if(sd > 0) 
				FD_SET( sd , &readfds); 
			
			if(sd > max) 
				max = sd; 
		} 
	
		activity = select( max + 1 , &readfds , NULL , NULL , NULL); 
	
		if ((activity < 0) && (errno!=EINTR)) 
		{ 
			printf("select error"); 
		} 
	
		if (FD_ISSET(master_s, &readfds)) 
		{ 
			if ((new_s = accept(master_s,(struct sockaddr *)&address, (socklen_t*)&len))<0) 
			{ 
				perror("accept"); 
				exit(1); 
			} 
			
			printf("New connection , socket fd is %d , \nip is : %s , \nport : %d \n" , new_s , inet_ntoa(address.sin_addr), ntohs (address.sin_port)); 
		
			if( send(new_s, message, strlen(message), 0) != strlen(message) ) 
			{ 
				perror("send error"); 
				exit(1);
			} 
			
			for (i = 0; i < 5; i++) 
			{ 
				if( client_socket[i] == 0 ) 
				{ 
					client_socket[i] = new_s; 	
					break; 
				} 
			} 
		} 
		
		for (i = 0; i < 5; i++) 
		{ 
			sd = client_socket[i]; 
				
			if (FD_ISSET( sd , &readfds)) 
			{ 
				if ((valread = read(sd,buffer,1024)) == 0) 
				{ 	
					getpeername(sd , (struct sockaddr*)&address ,(socklen_t*)&len); 
					close( sd ); 
					client_socket[i] = 0; 
				} 
				else
				{ 
					for(i = 0; i<5;i++){
						if(buffer[i] >= 'A' && buffer[i] <= 'Z')
							buffer[i] = buffer[i] + 32;
						else if(buffer[i] >= 'a' && buffer[i] <= 'z')
							buffer[i] = buffer[i] - 32;
						else 
							buffer[i] = buffer[i] + 0;	
					}
						
					buffer[valread] = '\0'; 
					send(sd , buffer , strlen(buffer) , 0 ); 
					
				} 
			} 
		} 
	} 
	
	return 0; 
} 
