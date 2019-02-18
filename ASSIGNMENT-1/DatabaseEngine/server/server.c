#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_queue { 
    long mtype; 
    char mtext[100]; 
}buf;

struct msg_queue sfunc(char file[], int no){
    FILE *fp;
    buf.mtype = 1 + no;
    char string1[100];	
    int length = strlen(file);
	file[length-1] = file[length] ;
    fp = fopen(file,"r");
    if(fp == NULL){
        strcpy(buf.mtext, "Data not found");
        return buf;
    }
    char final[100] ;
    while(fgets(string1, strlen(string1), fp) != NULL){
        strcat(final, string1);
    }   

    fclose(fp);
    strcpy(buf.mtext, final);
    return buf;
}

int main()
{
    
    struct msg_queue buf;
    int msgid;
    key_t key;

    if((key = ftok("man.txt", 'b')) == -1){
        perror("ftok");
        exit(1);
    } 

    if ((msgid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    while(1) { 
        
        
        msgrcv(msgid, &buf, sizeof buf.mtext, 1, 0);
        
        int len = strlen(buf.mtext);
    
	char no = buf.mtext[len];
        printf("%s", buf.mtext);
               
        if(no == '1'){  
            buf = sfunc(buf.mtext,1);
        }
        else if(no == '2'){
            buf = sfunc(buf.mtext,2);    
        }
        else if(no == '3'){
            buf = sfunc(buf.mtext,3);    
        }
        else if(no == '4'){
            buf = sfunc(buf.mtext,4);    
        }
        else if(no == '5'){
            buf = sfunc(buf.mtext,5);    
        }        
       
        msgsnd(msgid, &buf, len, 0);
            
    }

    return 0;
}
