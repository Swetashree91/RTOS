#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>



struct mb_send{
	long type;
	char text[100];
}msg1;

struct mb_recv{
	long typ;
	char txt[100];
}msg2;

int main(void){
	
	int mida,midb;
	key_t key1,key2;

	if((key1=ftok("/home/sweta/rtos/assgn1a/Server/123.txt",'b'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mida=msgget(key1,0644 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	printf("\nEnter a file name: ");
	
	fgets(msg1.text,sizeof(msg1.text),stdin);
	msg1.type = 1;
	msgsnd(mida,&msg1,sizeof(msg1),0);	
	printf("\ndata sent to server is : %s",msg1.text);
	if(msgctl(mida,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}
	
	key2=ftok("/home/sweta/rtos/assgn1a/Server/man3.txt",'a');
	midb=msgget(key2,0644 | IPC_CREAT);
	msgrcv(midb,&msg2,sizeof(msg2),1,0);	
	printf("\nData received from server:  %s\n",msg2.txt);

	return 0;
}

	
