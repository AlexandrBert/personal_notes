#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    /* 父进程循环 */
    if (pid > 0){
        alarm(8);
        /* 使用waitpid以阻塞的方式回收进程 */
        if(waitpid(pid,NULL,0) == 0){
            kill(pid,9);
        }
        // wait(NULL);//使用waitpid后会阻塞并回收子进程资源无需再利用wait回收
        while(1);
        
    }
    if(pid == 0){
        printf("raise before!\n");
        raise(SIGTSTP); //子进程自杀，直接调用_exit()，而不是库函数exit()
        printf("raise after!\n");
        exit(0);
    }

    return 0;
}