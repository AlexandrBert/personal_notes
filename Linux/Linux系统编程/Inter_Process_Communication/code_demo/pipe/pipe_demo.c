#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char sendbuf[] = "hello world!";
    char readbuf[128];

    /* 一定要在fork之前申请pipe，否则子进程与父进程之间无法通信 */
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* fork出一个子进程，子进程拥有单独的内存执行空间，父子进程都会运行此行往后的所有语句 */
    cpid = fork();

    if (cpid == -1) {
        perror("fork 生成子进程失败");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Child reads from pipe */
        close(pipefd[1]);          /* Close unused write end */
        read(pipefd[0], readbuf, sizeof(sendbuf));
        printf("子进程读取字符串结束：%s！\n",readbuf);
        close(pipefd[0]);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[0]);          /* Close unused read end */
        write(pipefd[1], sendbuf, sizeof(sendbuf));
        printf("父进程写入字符串结束:%s！\n",sendbuf);
        close(pipefd[1]);          /* Reader will see EOF */
    }
    while(1);
}
