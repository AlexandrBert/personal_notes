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
        printf("this is my_handler, signum = %d\n",signum);
        sleep(1);
        i++;
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();
    int i=0;

    /* 父进程循环 */
    if (pid > 0){
        signal(SIGCHLD,my_sighandler);
        // wait(NULL);//阻塞并回收子进程资源，如果不做处理会导致子进程变成僵尸进程
        while(1)
        {
            /* 使用waitpid以非阻塞的方式回收进程 */
            if(waitpid(pid,NULL,WNOHANG) != 0){
                printf("child process is end...\n");
            }
            printf("parent process is running...\n");
            sleep(1);
            i++;
            if(i>20){
                exit(0);
            }
        };
        
    }
    if(pid == 0){
        printf("raise before!\n");
        sleep(10);
        raise(SIGKILL); //子进程自杀，直接调用_exit()，而不是库函数exit()
        printf("raise after!\n");
        sleep(10);
        exit(0);
    }

    return 0;
}