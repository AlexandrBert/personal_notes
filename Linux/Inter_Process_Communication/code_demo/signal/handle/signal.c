#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void my_sighandler(int signum)
{
    int i=0;
    while(i<10)
    {
        printf("this is my_handler\n");
        sleep(1);
        i++;
    }
}

int main(int argc, char *argv[])
{

    /* 设置进程信号处理函数 */
    // signal(SIGALRM,my_sighandler);
    signal(SIGALRM,SIG_IGN);/* 设置为SIG_IGN处理则遇到前面的信号时直接忽略 */
    // signal(SIGKILL|SIGSTOP,SIG_IGN);/* SIGKILL和SIGSTOP无法被忽略 */

    printf("raise before!\n");
    raise(SIGALRM);
    /* 信号接收后，合法的使用信号处理函数时，会先执行my_sighandler，结束后才会执行后面语句 */
    printf("raise after!\n");

    return 0;
}