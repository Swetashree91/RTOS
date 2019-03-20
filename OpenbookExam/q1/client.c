#include<stdio.h>  
#include<stdlib.h> 
#include <unistd.h> 
#include<sys/types.h> 
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h> 
#include<netdb.h>
#include <sys/time.h>
  
#define PORT 3090


int main() {  
int sock_fd, val;  
char buffer[1000];  
struct sockaddr_in serv_addr;

struct timeval t;
 
FILE *fp;
 
 sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
 if (sock_fd < 0) {  
  printf("Error creating socket!\n");  
  exit(1);  
 }  
 printf("Socket created...\n");   

memset(&serv_addr, '0', sizeof(serv_addr));  
serv_addr.sin_family = AF_INET; 
serv_addr.sin_addr.s_addr = INADDR_ANY; 
serv_addr.sin_port = htons( PORT );     

if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address.\n"); 
		return -1; 
	} 

	if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}
memset(buffer, 0, 1000);
 
fp=fopen("data.csv","w");

fprintf(fp,"Time Temp Humidity  Gas1  Gas2  Gas3\n");
printf("data required.\n"); 
	while(1) {
  		if((recv(sock_fd,buffer,sizeof(buffer),0)) < 0) {
			printf("\nCould not receive.");
			exit(1);
		}
		gettimeofday(&t,NULL);
		fprintf(fp,"%lu",t.tv_usec);
		fprintf(fp,"%s\n",buffer);
   		printf("\n");
		}
	fclose(fp);
 	return 0;    
}
