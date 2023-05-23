#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int
main(int argc, char *argv[])
{
    int shm_id;
    /* 使用ftok()创建的key可以实现无亲缘关系的进程间通信 */
    key_t shm_key = ftok(".",200);

    if(shm_key == -1){
        perror("get shm_key error:");
    } else {
        printf("get shm_key sucess!shm_key = %x\n",shm_key);
        if((shm_id = shmget(shm_key,4096,0666|IPC_CREAT|IPC_EXCL)) < 0){
            perror("get shm_id error:");
        }else{
            printf("get shm sucess!\n");
        }
    }

    return 0;
}
