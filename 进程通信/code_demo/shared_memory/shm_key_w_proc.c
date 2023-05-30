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

volatile sig_atomic_t keep_running = 1;

void my_sighandle(int signum)
{
    if(signum == SIGINT){
        keep_running=0;
        printf("sighandle signum = %d\n",signum);
    } 
}

int
main(int argc, char *argv[])
{
    int shm_id;
    SHM_DATA *p=NULL;
    key_t shm_key = ftok(".",200);

    /* shmget创建一个IPC_PRIVATE的共享内存段，并返回内存段的shmid */
    if((shm_id = shmget(shm_key,4096,0777|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno == EEXIST){
            if (shm_id = shmget(shm_key,0,0) == -1) {
                perror("Failed to get shared memory status");
            } else {
                printf("shm_id = %d!\n",shm_id);
            }
        }
    }

    /* 设置SIGUSR2信号量处理函数 */
    signal(SIGUSR1,my_sighandle);
    signal(SIGINT,my_sighandle);
    /* attach具有shmid为shm_id的共享内存段 */
    p = (SHM_DATA *)shmat(shm_id,NULL,0);
    if(p == (void *) -1){
        perror("w_proc attach shm_id error:");
    } else {
        printf("w_proc attach shm_id sucess!\n");
    }

    p->wpid = getpid();

    pause();

    while(1)
    {
        /* 对共享内存段返回的地址进行数据写入 */
        printf("w_proc input words:\n");
        fgets(p->data,128,stdin);
        printf("->w_proc write shm_data name is %s\n",p->data);
        kill(p->rpid,SIGUSR2);
        pause();
        if(keep_running == 0){
            break;
        }
    }

    /* 将用户空间的地址删除，不会删除内核的共享内存 */
    if(shmdt(p) != 0){
        perror("w_proc detach shm_id error:");
    }
    printf("w_proc detach shm_id sucess!\n");

    /* shmctl命令删除内核中的共享内存段 */
    if(shmctl(shm_id,IPC_RMID,NULL) == 0){
        printf("w_proc remove shm_id sucess!\n");
    }

    return 0;
}
