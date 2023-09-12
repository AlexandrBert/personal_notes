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

void my_sighandle(int signum)
{
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int shm_id,i=0;
    char *p=NULL;
    char str[]="hello world!\0";
    char rbuf[128];

    /* shmget创建一个IPC_PRIVATE的共享内存段，并返回内存段的shmid */
    if((shm_id = shmget(IPC_PRIVATE,4096,0777|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno == EEXIST){
            if (shm_id = shmget(IPC_PRIVATE,0,0) == -1) {
                perror("Failed to get shared memory status");
            } else {
                printf("shm_id = %d!\n",shm_id);
            }
        }
    }
    /* 要在共享内存创建后fork */
    pid = fork();

    if(pid > 0){
        /* 设置SIGUSR2信号量处理函数 */
        signal(SIGUSR2,my_sighandle);
        /* attach具有shmid为shm_id的共享内存段 */
        p = (char *)shmat(shm_id,NULL,0);
        if(p == (void *) -1){
            perror("parent attach shm_id error:");
        } else {
            printf("parent attach shm_id sucess!\n");
        }

        while(i<3)
        {
            i++;
            /* 对共享内存段返回的地址进行数据写入 */
            printf("parent input words:\n");
            fgets(p,128,stdin);
            printf("->parent write shm_data name is %s\n",p);
            kill(pid,SIGUSR1);
            pause();
        }

        wait(NULL);
        /* 将用户空间的地址删除，不会删除内核的共享内存 */
        if(shmdt(p) != 0){
            perror("parent detach shm_id error:");
        }
        printf("parent detach shm_id sucess!\n");

        /* shmctl命令删除内核中的共享内存段 */
        if(shmctl(shm_id,IPC_RMID,NULL) == 0){
            printf("parent remove shm_id sucess!\n");
        }
    }else if(pid == 0){
        /* 设置SIGUSR2信号量处理函数 */
        signal(SIGUSR1,my_sighandle);
        /* attach具有shmid为shm_id的共享内存段 */
        p = (char *)shmat(shm_id,NULL,0);
        if(p == (void *) -1){
            perror("child attach shm_id error:");
        } else {
            printf("child attach shm_id sucess!\n");
        }
        while(i<3)
        {
            i++;
            pause();
            /* 对共享内存段返回的地址进行数据写入 */
            memcpy(rbuf,p,128);
            printf("->child read shm_data name is %s\n",rbuf);
            kill(getppid(),SIGUSR2);
        }

        /* 将用户空间的地址删除，不会删除内核的共享内存 */
        if(shmdt(p) != 0){
            perror("child detach shm_id error:");
        }
        printf("child detach shm_id sucess!\n");
        
    }

    return 0;
}
