#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>



struct mb_send4{
	long type;
	char text[5];
}mbuff4;

struct mb_recv4{
	long typ;
	char txt[5];
}mbuf4;

int main(void){
	int mid7,mid8;
	key_t key7,key8;

	if((key7=ftok("/home/sweta/rtos/assgn1/Server/man7.txt",'d'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mid7=msgget(key7,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	printf("\nEnter a character: ");
	
	mbuff4.type = 1;
	gets(mbuff4.text);

	msgsnd(mid7,&mbuff4,sizeof(mbuff4),0);	
	
	if(msgctl(mid7,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}
	
	//letter received from server
	key8=ftok("/home/sweta/rtos/assgn1/Server/man8.txt",'d');
	mid8=msgget(key8,0777 | IPC_CREAT);
	msgrcv(mid8,&mbuf4,sizeof(mbuf4),1,0);	
	printf("\nData received from server:  %s\n",mbuf4.txt);

	return 0;
}

	
