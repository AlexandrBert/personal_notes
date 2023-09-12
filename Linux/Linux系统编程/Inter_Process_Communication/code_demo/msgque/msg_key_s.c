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
    int msg_id;
    struct msgbuf smsg;
    smsg.mtype = 1;
    key_t msg_key = ftok(".",200);

    /* msgget创建一个IPC_PRIVATE的共享内存段，并返回内存段的msgid */
    if((msg_id = msgget(msg_key,0777|IPC_CREAT|IPC_EXCL)) < 0){
        perror("msgget error");
    }

    /* 设置SIGUSR2信号量处理函数 */
    signal(SIGINT,my_sighandle);

    while(1)
    {
        /* 对共享内存段返回的地址进行数据写入 */
        smsg.mtext.age = 18;
        printf("input name:\n");
        fgets(smsg.mtext.name,sizeof(smsg.mtext.name),stdin);
        if (msgsnd(msg_id, (void *) &smsg, sizeof(smsg.mtext),
                IPC_NOWAIT) == -1) {
                perror("msgsnd error");
            }
        printf("->w_proc write msg is %s\n",smsg.mtext.name);
        if(keep_running == 0){
            break;
        }
    }

    /* msgctl命令删除内核中的共享内存段 */
    if(msgctl(msg_id,IPC_RMID,NULL) == 0){
        printf("w_proc remove msg_id sucess!\n");
    }

    return 0;
}
