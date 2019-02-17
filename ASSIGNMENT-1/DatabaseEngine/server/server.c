
#include <stdio.h> 
#include <unistd.h> 
#include<stdlib.h>
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
	int i;
	char text1[100];
	char path[100];
	FILE *fp;
	
	if((key1=ftok("123.txt",'b'))== -1){
		perror("ftok\n");
		exit(1);
	}
	
	if((mida=msgget(key1,0644 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	key2=ftok("man3.txt",'a');
	midb=msgget(key2,0644 | IPC_CREAT);
	msg2.typ = 1;
		while(1){
		msgrcv(mida,&msg1,sizeof(msg1),1,0);
		printf("\nData received from Client A. : %s\n",msg1.text);
			strcpy(path,msg1.text);
			fp = fopen(path,"r");	
			if(fp == NULL){
				printf("\nfile not found.\n"); 
				strcpy(msg2.txt,"\nfile not found.\n");
				msgsnd(midb, &msg2, sizeof(msg2), 0);
				exit(0);
			}
			else {
				printf("/n file found.\n");
				strcpy(msg2.txt,"\nfile found.\n");
				msgsnd(midb, &msg2, sizeof(msg2), 0);
				}
		
	
			fclose(fp);
		}

	msgctl(midb,IPC_RMID,NULL);
	return 0;

 }
