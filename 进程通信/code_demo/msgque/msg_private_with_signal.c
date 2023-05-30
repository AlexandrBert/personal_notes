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

struct msgbuf {
           long mtype;
           char mtext[128];
       };

void my_sighandle(int signum)
{
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int msg_id,i=0;
    char *p=NULL;
    char str[]="hello world!\0";
    char rbuf[128];
    struct msgbuf smsg;
    struct msgbuf rmsg;

    /* msgget创建一个IPC_PRIVATE的消息队列，并返回内存段的msgid */
    if((msg_id = msgget(IPC_PRIVATE,0777|IPC_CREAT|IPC_EXCL)) < 0){
        perror("Failed to get message queue ：");
    }
    /* 要在共享内存创建后fork */
    pid = fork();

    if(pid > 0){
        /* 设置SIGUSR2信号量处理函数 */
        signal(SIGUSR2,my_sighandle);
        smsg.mtype = 1;
        while(i<3)
        {
            i++;
            /* 对发送消息进行数据写入 */
            printf("parent input words:\n");
            fgets(smsg.mtext,128,stdin);
            /* 对发送消息缓存发送到消息队列 */
            if (msgsnd(msg_id, (void *) &smsg, sizeof(smsg.mtext),
                IPC_NOWAIT) == -1) {
                perror("msgsnd error");
            }
            printf("->parent sent msg_data is %s\n",smsg.mtext);
            kill(pid,SIGUSR1);
            pause();
        }

        wait(NULL);

        /* 三次之后利用msgctl命令删除内核中的共享内存段 */
        if(msgctl(msg_id,IPC_RMID,NULL) == 0){
            printf("parent remove msg_id sucess!\n");
        }
    }else if(pid == 0){
        /* 设置SIGUSR2信号量处理函数 */
        signal(SIGUSR1,my_sighandle);
        rmsg.mtype = 1;
        while(i<3)
        {
            i++;
            pause();
            /* 对共享内存段返回的地址进行数据写入 */
            if (msgrcv(msg_id, (void *) &rmsg, sizeof(rmsg.mtext),0,
                IPC_NOWAIT) == -1) {
                perror("msgrcv error");
            }
            printf("->child read msg_data is %s\n",rmsg.mtext);
            kill(getppid(),SIGUSR2);
        }
        
    }

    return 0;
}
