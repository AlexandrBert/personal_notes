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

typedef struct shm_private
{
    /* data */
    char name[32];
    int age;
    int gender;
}SHM_P;


int
main(int argc, char *argv[])
{
    pid_t pid;
    int shm_id;
    SHM_P *p=NULL;
    char str[]="hello world!\0";
    SHM_P rbuf;

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

    /* attach具有shmid为shm_id的共享内存段 */
    p = (SHM_P *)shmat(shm_id,NULL,0);
    if(p == (void *) -1){
        perror("attach shm_id error:");
    } else {
        printf("attach shm_id sucess!\n");
    }

    if(pid > 0){
        /* 对共享内存段返回的地址进行数据写入 */
        memcpy(p->name,str,sizeof(p->name));
        printf("->parent write shm_data name is %s\n",p->name);
        printf("->parent write shm_data age is %d\n",p->age);
        printf("->parent write shm_data gender is %d\n",p->gender);
        sleep(8);
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
        /* 对共享内存段返回的地址进行数据写入 */
        memcpy(&rbuf,p,sizeof(SHM_P));
        printf("->child read shm_data name is %s\n",rbuf.name);
        printf("->child read shm_data age is %d\n",rbuf.age);
        printf("->child read shm_data gender is %d\n",rbuf.gender);
        sleep(5);
        /* 将用户空间的地址删除，不会删除内核的共享内存 */
        if(shmdt(p) != 0){
            perror("child detach shm_id error:");
        }
        printf("child detach shm_id sucess!\n");
        
    }

    return 0;
}
