#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
					
pthread_t tid[3];                			 	
int count = 0; 											
char text[100];	
pthread_mutex_t tid_lock[3],lock;					

void initialization_c(){  
	for(int i = 0; i < 3; i++){
		pthread_mutex_init(&(tid_lock[i]), NULL);				
		pthread_mutex_lock(&(tid_lock[i]));					
	}
	pthread_mutex_init(&lock, NULL);  			
	pthread_mutex_lock(&lock);								
}

int create_c(void *(*func)(void *)){
	pthread_create(&(tid[count++]), NULL, func, NULL);						
	pthread_mutex_lock(&lock);	 //locking central lock for the bellow cs					
	return (count - 1);
}
void yield_c(int cid){
	pthread_mutex_unlock(&lock);		//unlocking central lock to enable a thread to function			
	pthread_mutex_lock(&(tid_lock[cid]));	//locking that individual thread so that it can function only once			
}

void * printmsg(void *arg) 
{ 
	int cid = count - 1;   
	
	while(1){
		yield_c(cid);
		printf("Message by thread: %d ::: message: %s\n", cid+1, text);  
	}

	return NULL; 
} 

void send_c(int cid, char *msg){
	strcpy(text, msg);									
	pthread_mutex_unlock(&(tid_lock[cid]));					
	pthread_mutex_lock(&lock);								
}

void kill(int cid){
	pthread_cancel(tid[cid]);						
	pthread_mutex_destroy(&(tid_lock[cid])); 				
}

int main(void) 
{ 
	initialization_c();
	int ccr1,ccr2,ccr3;
	ccr1 = create_c(&printmsg);
	ccr2 = create_c(&printmsg);
	ccr3 = create_c(&printmsg);
	
	send_c(ccr3, "There3");
	send_c(ccr1, "Hi1");
	send_c(ccr2, "Hi2");
	send_c(ccr2, "There2");
	send_c(ccr1, "There1");
	send_c(ccr3, "Hi3");

	kill(ccr1);
	kill(ccr2);
	kill(ccr3);

	return 0; 
} 
