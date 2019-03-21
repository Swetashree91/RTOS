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
  
#define PORT 5220


int main() {  
int sock_fd, val;  
char buffer[1000]; 
int opt = 1; 
struct sockaddr_in serv_addr;

struct timeval t;
 
FILE *fp;
 
 sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
 if (sock_fd < 0) {  
  printf("Error creating socket!\n");  
  exit(1);  
 }  
 printf("\nSocket created.\n");   

if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}  
serv_addr.sin_family = AF_INET; 
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
serv_addr.sin_port = htons( PORT );     

if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
{ 
	printf("\nConnection Failed \n"); 
	return -1; 
	}
memset(buffer, 0, 1000);
 
fp=fopen("data.txt","w");

fprintf(fp,"Time Temp Humidity  Gas1  Gas2  Gas3\n");
fseek(fp,5,SEEK_SET);
fclose(fp);
printf("data required.\n"); 
	while(1) {
  		if((recv(sock_fd,buffer,sizeof(buffer),0)) < 0) {
			printf("\nCould not receive.");
			exit(1);
		}
		else {
			gettimeofday(&t,NULL);
			fp=fopen("data.csv","a");
			printf("recvd data : %s",buffer);
			fprintf(fp,"%lu",t.tv_usec);
			fseek(fp,5,SEEK_SET);
			fprintf(fp,"%s\n",buffer);
   			fclose(fp); 
		     }
		}
	fclose(fp);
 	return 0;    
}
