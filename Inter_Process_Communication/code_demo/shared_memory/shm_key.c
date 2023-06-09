#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    struct shmid_ds shm_stat;
    int shm_id;
    char *p=NULL;
    char str[]="hello world!\0";
    /* 使用ftok()创建的key可以实现无亲缘关系的进程间通信 */
    key_t shm_key = ftok(".",200);

    if(shm_key == -1){
        perror("get shm_key error:");
    } else {
        printf("get shm_key sucess!\nshm_key = %x\n",shm_key);

        /* shmget创建一个根据唯一key创建的共享内存段，并返回内存段的shmid */
        if((shm_id = shmget(shm_key,4096,0777|IPC_CREAT|IPC_EXCL)) < 0){
            if(errno == EEXIST){
                if (shm_id = shmget(shm_key,4096,0) == -1) {
                    perror("Failed to get shared memory status");
                } else {
                    printf("shm_id = %d!\n",shm_id);
                }
            }
        }
    }

    system("ipcs -m");
    /* attach具有shmid为shm_id的共享内存段 */
    p = (char *)shmat(shm_id,NULL,0);
    if(p == (void *) -1){
        perror("attach shm_id error:");
    } else {
        printf("attach shm_id sucess!\n");

        /* 对共享内存段返回的地址进行数据写入 */
        strncpy(p,str,128);
        printf("shm_data is %s\n",p);

        /* 将用户空间的地址删除，不会删除内核的共享内存 */
        if(shmdt(p) != 0){
            perror("detach shm_id error:");
        }
        printf("detach shm_id sucess!\n");
    }

    /* shmctl命令删除内核中的共享内存段 */
    if(shmctl(shm_id,IPC_RMID,NULL) == 0){
        printf("remove shm_id sucess!\n");
    }

    return 0;
}
