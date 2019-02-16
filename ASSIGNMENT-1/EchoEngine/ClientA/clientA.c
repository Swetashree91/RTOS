#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>



struct mb_send1{
	long type;
	char text[5];
}mbuff1;

struct mb_recv1{
	long typ;
	char txt[5];
}mbuf1;

int main(void){
	
	int mid1,mid2;
	key_t key1,key2;

	if((key1=ftok("/home/sweta/rtos/assgn1/Server/man1.txt",'a'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mid1=msgget(key1,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	printf("\nEnter a character: ");
	
	mbuff1.type = 1;
	
	gets(mbuff1.text);
	
	msgsnd(mid1,&mbuff1,sizeof(mbuff1),0);	
	
	if(msgctl(mid1,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}
	
	//letter received from server
	key2=ftok("/home/sweta/rtos/assgn1/Server/man2.txt",'a');
	mid2=msgget(key2,0777 | IPC_CREAT);
	msgrcv(mid2,&mbuf1,sizeof(mbuf1),1,0);	
	printf("\nData received from server:  %s\n",mbuf1.txt);

	return 0;
}

	
