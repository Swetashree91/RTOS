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
  
#define PORT 5330


int main() {  
int sock_fd,opt = 1;  
char buffer[1000]; 
struct sockaddr_in address;

FILE *fp;
 
sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
if (sock_fd < 0) {  
  	printf("\nError creating socket.\n");  
  	exit(1);  
}  

if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}  
address.sin_family = AF_INET; 
address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
address.sin_port = htons( PORT );     

if (connect(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
{ 
	printf("\nConnection Failed.\n"); 
	exit(1); 
	}
memset(buffer, 0, sizeof(buffer));
 
fp=fopen("data.txt","w");
fprintf(fp,"Time Temp Humidity  Gas1  Gas2  Gas3\n");
fclose(fp);
printf("data required.\n"); 
	
while(1) {
	strcpy(buffer,"get data");
  	sleep(2);
  	if(sendto(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &address, sizeof(address))<0) {
  		printf("\nError sending.");
		exit(1);  
  		}
	memset(buffer, 0, sizeof(buffer));
  	if(recvfrom(sock_fd, buffer, sizeof(buffer), 0, NULL, NULL)<0) { 
   		printf("\nError receiving.\n"); 
		exit(1);   
  		}
  	else {
   	fp = fopen("plant_data.txt","a");
   	printf("Data received from sensor:%s\n",buffer);
   	fprintf(fp,"%s\n",buffer);
   	fclose(fp);
  	}  
 }
return 0;    
}
