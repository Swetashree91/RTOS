#include<stdio.h>  
#include<stdlib.h> 
#include <unistd.h> 
#include<sys/types.h> 
#include<sys/socket.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h> 
#include<netdb.h>

#define PORT 3090

int main() {
 struct sockaddr_in address;
 int sock_fd, addrlen, val, new_socket;
char buffer[1000],c;

FILE *fp1,*fp2,*fp3,*fp4,*fp5;
 
 sock_fd = socket(AF_INET, SOCK_STREAM, 0);
 if (sock_fd < 0) {
  printf("\nError creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
memset(&address, '0', sizeof(address));
address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons( PORT ); 
 
 val = bind(sock_fd, (struct sockaddr *) &address, sizeof(address));
 if (val < 0) {
  printf("\nError in binding!\n");
  exit(1);
 }
 
 printf("Waiting for a connection...\n");
 listen(sock_fd, 5);

 while(1) { 
 	int addrlen = sizeof(address); 
 	new_socket = accept(sock_fd, (struct sockaddr *) &address, &addrlen);
 	if (new_socket < 0) {
  	printf("\nError accepting connection!\n");
   	exit(1);
  	}
printf("\nConnection accepted.\n");

inet_ntop(AF_INET, &(address.sin_addr), "127.0.0.1", 100);

   while(1)
	{
   	 fp1 = 0;
    	fp1 = fopen("sensor1.txt","r"); 
 	fp2 = 0;
   	fp2 = fopen("sensor2.txt","r");  
 	fp3 = 0;
    	fp3 = fopen("sensor3.txt","r");  
	fp4 = 0;
    	fp4 = fopen("sensor4.txt","r"); 
	fp5 = 0; 
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
}
  close(new_socket);
}
return 0;
}
