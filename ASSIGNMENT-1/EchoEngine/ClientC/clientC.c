#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/time.h>


struct mb_send3{
	long type;
	char text[5];
}mbuff3;

struct mb_recv3{
	long typ;
	char txt[5];
}mbuf3;


int main(void){
	struct timeval t1,t2;
	int mid5,mid6;
	key_t key5,key6;

	if((key5=ftok("/home/sweta/rtos/assgn1/Server/man5.txt",'c'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mid5=msgget(key5,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	mbuff3.type = 1;
	printf("\nEnter a character: ");
	
	
	scanf("%s",mbuff3.text);
	gettimeofday(&t1,NULL);

	msgsnd(mid5,&mbuff3,sizeof(mbuff3),0);	
	
	if(msgctl(mid5,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}
	
	//letter received from server
	key6=ftok("/home/sweta/rtos/assgn1/Server/man6.txt",'c');
	mid6=msgget(key6,0777 | IPC_CREAT);
	msgrcv(mid6,&mbuf3,sizeof(mbuf3),1,0);
	gettimeofday(&t2,NULL);
	printf("\nData received from server:  %s\n",mbuf3.txt);
	printf("\n time by B:%lu",t2.tv_usec-t1.tv_usec);
	return 0;
}

	
