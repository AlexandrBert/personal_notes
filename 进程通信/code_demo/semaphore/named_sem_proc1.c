#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

struct sembuf sem_op[5];

union semun
   {
     int val;				/* <= value for SETVAL */
     struct semid_ds *buf;		/* <= buffer for IPC_STAT & IPC_SET */
     unsigned short int *array;		/* <= array for GETALL & SETALL */
     struct seminfo *__buf;		/* <= buffer for IPC_INFO */
   };

/* 定义P和V操作函数 */
void P(int semid,int n)
{
    struct sembuf buf;
    buf.sem_num = 0;    // 操作的信号量标识符为0
    buf.sem_op  = -n;   // 执行的操作为减少n个信号量
    buf.sem_flg = 0;
    if(semop(semid, &buf, 1) == -1){
        perror("P op error:");
        return;
    };
}

void V(int semid,int n)
{
    struct sembuf buf;
    buf.sem_num = 0;    // 操作的信号量标识符为0
    buf.sem_op  = n;    // 执行的操作为增加n个信号量
    buf.sem_flg = 0;
    if(semop(semid, &buf, 1) == -1){
        perror("V op error:");
        return;
    };
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int sem_id,i=0;
    key_t sem_key;
    sem_key = ftok(".",200);

    /* semget创建一个IPC_PRIVATE的共享内存段，并返回内存段的semid */
    if((sem_id = semget(sem_key,3,0777|IPC_CREAT|IPC_EXCL)) < 0){
        perror("get sem_id error:");
    }
    printf("get sem_id = %d\n",sem_id);

    /* 信号量初始化 */
    union semun arg;
    arg.val = 1;
    if(semctl(sem_id, 0, SETVAL, arg) != 0){
        perror("SETVAL error:");
    }

    while(1){
        P(sem_id,1);
        sleep(1);
        i++;
        printf("process1 doing some thing!-----%d\n",i);
        V(sem_id,1);
        usleep(100);
    }

    return 0;
}
