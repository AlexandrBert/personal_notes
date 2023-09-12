#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
 
#define SIZE 64
 
int main(int argc, const char* argv[]) {
 
    int ret = -1;
    int fds[2];
    pid_t pid = -1;
    char buf[SIZE];
 
    // 1. 创建无名管道
    ret = pipe(fds);
    if (-1 == ret) {
        perror("pipe创建失败！\n");
        return 1;
    }
 
    // 2. 创建子进程。需要在创建无名管道之后
    pid = fork();
    if (-1 == pid) {
        perror("fork");
        return 1;
    }
 
    // 子进程 读管道
    if (0 == pid) {
        close(fds[1]);  // 关闭写端
 
        /*设置读端非阻塞*/
        ret = fcntl(fds[0], F_GETFL);  // 获取读端缓冲区状态
        ret |= O_NONBLOCK; //将读端缓冲区加入非阻塞状态
        fcntl(fds[0], F_SETFL, ret); // 将新状态设置进入
 
        ret = read(fds[0], buf, SIZE); // 读管道
        printf("子进程读取结束\n");
        if (ret < 0) {
            perror("read");
            exit(-1);
        }
        printf("子进程读到的内容：%s\n", buf);
        close(fds[0]);  // 关闭读端
        exit(0); // 子进程退出
    } else {
        // 父进程 写管道
        /* sleep(1)让父进程陷入睡眠，使得子进程无法读到数据 */
        sleep(1);
        close(fds[0]); // 关闭读端
    
        ret = write(fds[1], "ABCDEFG", 7);  // 写管道
        if (-1 == ret) {
            perror("write");
            // return 1;
        }
        printf("父进程写了%d字节.\n", ret);
        close(fds[1]);  // 关闭写端
    }

    while(1);

    return 0;
}