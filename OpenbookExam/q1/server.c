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
struct sockaddr_in address;
int sock_fd, val, new_socket;
int opt = 1,addr_length;
char buffer[1000];
char temp[5],humid[5],gas1[5],gas2[5],gas3[5];
struct timeval t;

FILE *fp;
 
 sock_fd = socket(AF_INET, SOCK_STREAM, 0);
 if (sock_fd < 0) {
  printf("\nError creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons( PORT ); 
 
 if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("\nbind failed"); 
		exit(EXIT_FAILURE); 
	} 
 
 printf("Waiting for a connection...\n");
 listen(sock_fd, 1);
addr_length = sizeof(address);
while(1) {
 	new_socket = accept(sock_fd, (struct sockaddr *) &address, &addr_length);
	printf("\n new socket fd : %d",new_socket);
 	if (new_socket < 0) {
  		printf("\nError accepting connection.\n");
   		exit(1);
		}
  	
  while(1){
	 memset(buffer, 0, sizeof(buffer));
    	 gettimeofday(&t,NULL);
      	 if(recvfrom(new_socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &address, &addr_length)<0) {
     		printf("\nError in receiving .\n");  
     		exit(1);
    		}
    	 if(strcmp(buffer,"get data")==0) {

      		fp = fopen("sensor1.txt", "r");
      		fscanf(fp, "%s", temp);
      		fclose(fp);
     
      		fp = fopen("sensor2.txt", "r");
      		fscanf(fp, "%s", humid);
      		fclose(fp);
      
      		fp = fopen("sensor3.txt", "r");
      		fscanf(fp, "%s", gas1);
     		fclose(fp);
      
      		fp = fopen("sensor4.txt", "r");
      		fscanf(fp, "%s", gas2);
      		fclose(fp);
      
      		fp = fopen("sensor5.txt", "r");
      		fscanf(fp, "%s", gas3);
      		fclose(fp);
		memset(buffer, 0, sizeof(buffer));
      		sprintf(buffer,"%lu %s %s %s %s %s",t.tv_usec,temp,humid,gas1,gas2,gas3);
       
       		if(sendto(new_socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &address, addr_length)<0)  {   
       			printf("\nError sending sensor data.");  
       			exit(1);     
    		}
	
 		printf("\nSent sensor data: %s", buffer);
	}
	}
  	close(new_socket);
}
	return 0;
}
