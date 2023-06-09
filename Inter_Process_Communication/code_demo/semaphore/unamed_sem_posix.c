#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;

void *fun()
{
    int i;
    sem_wait(&sem);
    for(i=0;i<10;i++){
        usleep(100);
        printf("child thread is doing something!\n");
    }
}

int
main(int argc, char *argv[])
{
    pthread_t thread_id;
    int sem_id;
    int i;

    /* 信号量初始化 */
    sem_init(&sem,0,0);
    if(0 != pthread_create(&thread_id,NULL,fun,NULL)){
        perror("create thread:");
    }

    for(i=0;i<10;i++){
            usleep(100);
            printf("parent is doing something!\n");
        }
    sem_post(&sem);
    while(1);

    return 0;
}
