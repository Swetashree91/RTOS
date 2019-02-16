#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>



struct mb_send2{
	long type;
	char text[5];
}mbuff2;

struct mb_recv2{
	long typ;
	char txt[5];
}mbuf2;

int main(void){
	int mid3,mid4;
	key_t key3,key4;

	if((key3=ftok("/home/sweta/rtos/assgn1/Server/man3.txt",'b'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mid3=msgget(key3,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	printf("\nEnter a character: ");
	
	mbuff2.type = 1;
	//	
	gets(mbuff2.text);

	msgsnd(mid3,&mbuff2,sizeof(mbuff2),0);	
	
	if(msgctl(mid3,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}
	
	//letter received from server
	key4=ftok("/home/sweta/rtos/assgn1/Server/man4.txt",'b');
	mid4=msgget(key4,0777 | IPC_CREAT);
	msgrcv(mid4,&mbuf2,sizeof(mbuf2),1,0);	
	printf("\nData received from server:  %s\n",mbuf2.txt);

	return 0;
}

	
