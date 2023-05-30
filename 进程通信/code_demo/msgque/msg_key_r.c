#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

typedef struct msg_data
{
    /* data */
    int age;
    char name[256];
}MSG_DATA;

struct msgbuf {
           long mtype;
           MSG_DATA mtext;
       };

void my_sighandle(int signum)
{
}

int
main(int argc, char *argv[])
{
    int msg_id;
    struct msgbuf rmsg;
    key_t msg_key = ftok(".",200);

    /* msgget创建一个IPC_PRIVATE的共享内存段，并返回内存段的msgid */
    if((msg_id = msgget(msg_key,0777|IPC_CREAT)) < 0){
        perror("msgget error");
    }

    while(1)
    {
        /* msgflg设置为0，以阻塞方式读取 */
        if (msgrcv(msg_id, (void *) &rmsg, sizeof(rmsg.mtext),0,0) == -1) {
                perror("msgrcv error");
            }
        printf("read msg age is %d\n",rmsg.mtext.age);    
        printf("read msg name is %s\n",rmsg.mtext.name);

    }

    return 0;
}
