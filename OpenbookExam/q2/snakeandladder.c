#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>

pthread_t thread_id[4];
int count = 0;

pthread_mutex_t tid_lock[4];
pthread_mutex_t lock;

char str[1000];
int winner = 0;

int create_c(void *(*f)())
{
    pthread_create(&(thread_id[count++]), NULL, f, NULL);  //thread creation when invoked - 4 threads for 4 players
    pthread_mutex_lock(&lock);  //locking of main lock
    return count - 1;
}

void send_c(int cid)   //for playing
{
    pthread_mutex_unlock(&(tid_lock[cid]));  //unlock that particular mutex which wants to play
    pthread_mutex_lock(&lock);
}

void kill_c(int cid)
{
    pthread_cancel(thread_id[cid]);
    pthread_mutex_destroy(&(tid_lock[cid]));
}

void yield_c(int cid){
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&(tid_lock[cid]));
   
}

void* players()
{
    srand(time(0));
    int cid = count - 1;
    int level = 0;
    int die;
    while(1)
    {

        die = rand() % 6 + 1;
        level = level + die;
        if(level >= 100)
        {
            winner = cid + 1;
            printf("Winner: Player %d\n", cid+1);

        }
        yield_c(cid);   //waits

    }

}

int main()
{    
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        pthread_mutex_init(&(tid_lock[i]), NULL);
        pthread_mutex_lock(&(tid_lock[i]));
    }
    pthread_mutex_init(&lock,NULL);
    pthread_mutex_lock(&lock);

    struct timeval t1, t2;

    int ccr1 = create_c(&players);
    int ccr2 = create_c(&players);
    int ccr3 = create_c(&players);
    int ccr4 = create_c(&players);

    gettimeofday(&t1, NULL);


    while(1)
    {
        if(winner > 0)
            break;
        send_c(ccr1);
        if(winner > 0)
            break;
        send_c(ccr2);
        if(winner > 0)
            break;
        send_c(ccr3);
        if(winner > 0)
            break;
        send_c(ccr4);

    }

    gettimeofday(&t2, NULL);
    printf("\ntotal time:%lu\n",t2.tv_usec-t1.tv_usec);
    
    kill_c(ccr1);
    kill_c(ccr2);
    kill_c(ccr3);
    kill_c(ccr4);

    return 0;
} 
