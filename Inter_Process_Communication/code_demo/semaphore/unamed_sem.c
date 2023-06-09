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
    int sem_id,i;

    /* semget创建一个IPC_PRIVATE的共享内存段，并返回内存段的semid */
    if((sem_id = semget(IPC_PRIVATE,3,0777|IPC_CREAT|IPC_EXCL)) < 0){
        perror("get sem_id error:");
    }
    printf("get sem_id = %d\n",sem_id);

    /* 信号量初始化 */
    union semun arg;
    arg.val = 1;
    if(semctl(sem_id, 0, SETVAL, arg) != 0){
        perror("SETVAL error:");
    }

    /* 要在共享内存创建后fork */
    pid = fork();

    if(pid > 0){
        printf("parent process!\n");
        while(1){
            P(sem_id,1);
            for(i=0;i<3;i++){
                sleep(1);
                printf("parent doing some thing!\n");
            }
            V(sem_id,1);
            // sleep(1);
        }
        printf("parent step out while sucess!\n");
        wait(NULL);

        /* semctl命令删除内核中的共享内存段 */
        if(semctl(sem_id,0,IPC_RMID) == 0){
            printf("parent remove sem_id sucess!\n");
        }
    }else if(pid == 0){
        printf("child process!\n");
        while(1){
            P(sem_id,1);
            for(i=0;i<2;i++){
                sleep(1);
                printf("child doing some thing!\n");
            }
            V(sem_id,1);
        }
    }

    return 0;
}
