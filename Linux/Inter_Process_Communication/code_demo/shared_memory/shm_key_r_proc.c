#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

typedef struct shm_data
{
    /* data */
    int wpid;
    int rpid;
    char data[256];
}SHM_DATA;


void my_sighandle(int signum)
{
}

int
main(int argc, char *argv[])
{
    int shm_id;
    SHM_DATA *p=NULL;
    key_t shm_key = ftok(".",200);

    /* shmget创建一个IPC_PRIVATE的共享内存段，并返回内存段的shmid */
    if((shm_id = shmget(shm_key,4096,0777|IPC_CREAT)) < 0){
        if(errno == EEXIST){
            if (shm_id = shmget(shm_key,0,0) == -1) {
                perror("Failed to get shared memory status");
            } else {
                printf("shm_id = %d!\n",shm_id);
            }
        }
    }

    /* 设置SIGUSR2信号量处理函数 */
    signal(SIGUSR2,my_sighandle);
    /* attach具有shmid为shm_id的共享内存段 */
    p = (SHM_DATA *)shmat(shm_id,NULL,0);
    if(p == (void *) -1){
        perror("r_proc attach shm_id error:");
    } else {
        printf("r_proc attach shm_id sucess!\n");
    }

    p->rpid = getpid();
    kill(p->wpid,SIGUSR1);

    while(1)
    {
        pause();
        /* 对共享内存段返回的地址进行数据写入 */
        printf("->r_proc read shm_data data is %s\n",p->data);
        kill(p->wpid,SIGUSR1);
    }

    /* 将用户空间的地址删除，不会删除内核的共享内存 */
    if(shmdt(p) != 0){
        perror("w_proc detach shm_id error:");
    }
    printf("w_proc detach shm_id sucess!\n");

    return 0;
}
