#include <stdio.h>
#include <stdlib.h>
#include <error.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/time.h>

struct msg_queue { 
    long mtype; 
    char mtext[100]; 
};

int main() 
{ 
    struct timeval t1, t2;
    struct msg_queue buf;
    key_t key; 
    int msgid;
    
    if((key = ftok("/home/sweta/rtos/assgn1a/Server/man.txt", 'b')) == -1){
        perror("ftok");
        exit(1);
    } 
  
    if((msgid = msgget(key, 0644)) == -1){
        perror("msgget");
        exit(1);
    } 

    while(1) {
        buf.mtype = 1; 
        
        printf("Enter file name: ");
        
        if(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
            int len = strlen(buf.mtext);
            
            if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
            strcat(buf.mtext, "4");
            
            gettimeofday(&t1, NULL);
            
            msgsnd(msgid, &buf, len+1, 0);
               

        }
        msgctl(msgid,IPC_RMID,NULL);
        msgrcv(msgid, &buf, sizeof buf.mtext, 5, 0);
        
        gettimeofday(&t2, NULL);
        
        printf("time by D: %lu\n",t2.tv_usec - t1.tv_usec);  
    }
    
    return 0; 
} 
