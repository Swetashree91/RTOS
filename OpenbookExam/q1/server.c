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
struct sockaddr_in address;
int sock_fd, val, new_socket;
int opt = 1;
char buffer[1000],c;

FILE *fp1,*fp2,*fp3,*fp4,*fp5;
 
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
 listen(sock_fd, 5);

 		int addrlen = sizeof(address); 
 		new_socket = accept(sock_fd, (struct sockaddr *) &address, &addrlen);
		printf("\n new socket fd : %d",new_socket);
 		if (new_socket < 0) {
  		printf("\nError accepting connection!\n");
   		exit(1);
		}
  	
printf("\nConnection accepted.\n");
  	
 while(1)
	{
	fp1 = fopen("sensor1.txt","r"); 
   	fp2 = fopen("sensor2.txt","r");  
    	fp3 = fopen("sensor3.txt","r"); 
    	fp4 = fopen("sensor4.txt","r"); 
    	fp5 = fopen("sensor5.txt","r");	
  	c = fgetc(fp1); 
      	int i=0;
      	while (c != EOF) { 
         buffer[i] = c;
         i++;
         c = fgetc(fp1);
       	} 
         buffer[i] = ' ';
         i++;
  	c = fgetc(fp2); 
      	while (c != EOF) { 
         buffer[i] = c;
         i++;
         c = fgetc(fp2);
       	} 
         buffer[i] = ' ';
         i++;
  	c = fgetc(fp3); 
     	while (c != EOF) { 
         buffer[i] = c;
         i++;
         c = fgetc(fp3);
       	}  
         buffer[i] = ' ';
         i++; 
	c = fgetc(fp4); 
      	while (c != EOF) { 
         buffer[i] = c;
         i++;
         c = fgetc(fp4);
       	}  
         buffer[i] = ' ';
         i++;
 	c = fgetc(fp5); 
      	while (c != EOF) { 
         buffer[i] = c;
         i++;
         c = fgetc(fp5);
      	 } 
	if(send(new_socket,buffer,sizeof(buffer),0) < 0) {   
     		printf("\nError sending data.\n");  
     		exit(1); 
    	}
	
 	printf("Sent data: %s\n", buffer);
	sleep(2);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);

  	//close(new_socket);
}
return 0;
}
