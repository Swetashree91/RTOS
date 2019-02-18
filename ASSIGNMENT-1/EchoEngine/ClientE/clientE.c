#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/time.h>

struct mb_send5{
	long type;
	char text[5];
}mbuff5;

struct mb_recv5{
	long typ;
	char txt[5];
}mbuf5;


int main(void){
	struct timeval t1,t2;	
	int mid9,mid10;
	key_t key9,key10;

	if((key9=ftok("/home/sweta/rtos/assgn1/Server/man9.txt",'e'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((mid9=msgget(key9,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	mbuff5.type = 1;
	printf("\nEnter a character: ");
	
	
	scanf("%s",mbuff5.text);
	gettimeofday(&t1,NULL);

	msgsnd(mid9,&mbuff5,sizeof(mbuff5),0);	
	
	if(msgctl(mid9,IPC_RMID,NULL)==-1){
		perror("msgctl\n");
		exit(1);
	}

	key10=ftok("/home/sweta/rtos/assgn1/Server/man10.txt",'e');
	mid10=msgget(key10,0777 | IPC_CREAT);
	msgrcv(mid10,&mbuf5,sizeof(mbuf5),1,0);	
	gettimeofday(&t2,NULL);
	printf("\nData received from server:  %s\n",mbuf5.txt);
	printf("\n time by B:%lu",t2.tv_usec-t1.tv_usec);
	return 0;
}

	
