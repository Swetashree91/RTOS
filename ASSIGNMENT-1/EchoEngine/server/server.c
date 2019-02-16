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
struct mb_send2{
	long type;
	char text[5];
}mbuff2;

struct mb_recv2{
	long typ;
	char txt[5];
}mbuf2;
struct mb_send3{
	long type;
	char text[5];
}mbuff3;

struct mb_recv3{
	long typ;
	char txt[5];
}mbuf3;
struct mb_send4{
	long type;
	char text[5];
}mbuff4;

struct mb_recv4{
	long typ;
	char txt[5];
}mbuf4;
struct mb_send5{
	long type;
	char text[5];
}mbuff5;

struct mb_recv5{
	long typ;
	char txt[5];
}mbuf5;

int main(void){

	int mid1,mid2;
	int mid3,mid4;
	int mid5,mid6;
	int mid7,mid8;
	int mid9,mid10;

	key_t key1,key2,key3,key4,key5,key6,key7,key8,key9,key10;
	int i,j;
	char text[5];

	if((key1=ftok("man1.txt",'a'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((key3=ftok("man3.txt",'b'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((key5=ftok("man5.txt",'c'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((key7=ftok("man7.txt",'d'))== -1){
		perror("ftok\n");
		exit(1);
	}
	if((key9=ftok("man9.txt",'e'))== -1){
		perror("ftok\n");
		exit(1);
	}
	
	while(1){
	if((mid1=msgget(key1,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	else if((mid3 = msgget(key3,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	else if((mid5 = msgget(key5,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	else if((mid7 = msgget(key7,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	else if((mid9 = msgget(key9,0777 | IPC_CREAT))==-1){
		perror("msgget\n");
		exit(1);
	}
	
	//client A
	if(msgrcv(mid1,&mbuff1,sizeof(mbuff1),1,0) != -1){
		for(i = 0; i<5;i++){
		if(mbuff1.text[i] >= 'A' && mbuff1.text[i] <= 'Z')
			mbuff1.text[i] = mbuff1.text[i] + 32;
		else if(mbuff1.text[i] >= 'a' && mbuff1.text[i] <= 'z')
			mbuff1.text[i] = mbuff1.text[i] - 32;
		else 
			mbuff1.text[i] = mbuff1.text[i] + 0;	
	}
	printf("\nData received from Client A.\n");
	key2=ftok("man2.txt",'a');
	mid2=msgget(key2,0777 | IPC_CREAT);
	mbuf1.typ = 1;
	for(i = 0; i<5;i++){
		mbuf1.txt[i] = mbuff1.text[i];
	 }
	msgsnd(mid2, &mbuf1, sizeof(mbuf1), 0);
	}

 	//client B
	
	if(msgrcv(mid3,&mbuff2,sizeof(mbuff2),1,0) != -1){
		for(i = 0; i<5;i++){
		if(mbuff2.text[i] >= 'A' && mbuff2.text[i] <= 'Z')
			mbuff2.text[i] = mbuff2.text[i] + 32;
		else if(mbuff2.text[i] >= 'a' && mbuff2.text[i] <= 'z')
			mbuff2.text[i] = mbuff2.text[i] - 32;
		else 
			mbuff2.text[i] = mbuff2.text[i] + 0;	
	}
	printf("\nData received from Client B.\n");
	key4=ftok("man4.txt",'b');
	mid4=msgget(key4,0777 | IPC_CREAT);
	mbuf2.typ = 1;
	for(i = 0; i<5;i++){
		mbuf2.txt[i] = mbuff2.text[i];
	 }
	msgsnd(mid4, &mbuf2, sizeof(mbuf2), 0);
	}
	//client C

	if(msgrcv(mid5,&mbuff3,sizeof(mbuff3),1,0) != -1){
		for(i = 0; i<5;i++){
		if(mbuff3.text[i] >= 'A' && mbuff3.text[i] <= 'Z')
			mbuff3.text[i] = mbuff3.text[i] + 32;
		else if(mbuff3.text[i] >= 'a' && mbuff3.text[i] <= 'z')
			mbuff3.text[i] = mbuff3.text[i] - 32;
		else 
			mbuff3.text[i] = mbuff3.text[i] + 0;	
	}
	printf("\nData received from Client C.\n");
	key6=ftok("man6.txt",'c');
	mid6=msgget(key6,0777 | IPC_CREAT);
	mbuf3.typ = 1;
	for(i = 0; i<5;i++){
		mbuf3.txt[i] = mbuff3.text[i];
	 }
	msgsnd(mid6, &mbuf3, sizeof(mbuf3), 0);
	}	
	//client D
	
	if(msgrcv(mid7,&mbuff4,sizeof(mbuff4),1,0) != -1){
		for(i = 0; i<5;i++){
		if(mbuff4.text[i] >= 'A' && mbuff4.text[i] <= 'Z')
			mbuff4.text[i] = mbuff4.text[i] + 32;
		else if(mbuff4.text[i] >= 'a' && mbuff4.text[i] <= 'z')
			mbuff4.text[i] = mbuff4.text[i] - 32;
		else 
			mbuff4.text[i] = mbuff4.text[i] + 0;	
	}
	printf("\nData received from Client D.\n");
	key8=ftok("man8.txt",'d');
	mid8=msgget(key8,0777 | IPC_CREAT);
	mbuf4.typ = 1;
	for(i = 0; i<5;i++){
		mbuf4.txt[i] = mbuff4.text[i];
	 }
	msgsnd(mid8, &mbuf4, sizeof(mbuf4), 0);
	}
	//client E

	if(msgrcv(mid9,&mbuff5,sizeof(mbuff5),1,0) != -1){
		for(i = 0; i<5;i++){
		if(mbuff5.text[i] >= 'A' && mbuff5.text[i] <= 'Z')
			mbuff5.text[i] = mbuff5.text[i] + 32;
		else if(mbuff5.text[i] >= 'a' && mbuff5.text[i] <= 'z')
			mbuff5.text[i] = mbuff5.text[i] - 32;
		else 
			mbuff5.text[i] = mbuff5.text[i] + 0;	
		}
		printf("\nData received from Client E.\n");
		key10=ftok("man10.txt",'e');
		mid10=msgget(key10,0777 | IPC_CREAT);
		mbuf5.typ = 1;
		for(i = 0; i<5;i++){
			mbuf5.txt[i] = mbuff5.text[i];
	 	}
		msgsnd(mid10, &mbuf5, sizeof(mbuf5), 0);
		}

	}
	
	
	msgctl(mid2,IPC_RMID,NULL);	
	msgctl(mid4,IPC_RMID,NULL);
	msgctl(mid6,IPC_RMID,NULL);
	msgctl(mid8,IPC_RMID,NULL);
	msgctl(mid10,IPC_RMID,NULL);

	return 0;
}

	
