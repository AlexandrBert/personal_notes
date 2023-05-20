#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
 
#define SIZE 128
 
int main(int argc, const char* argv[]) { // 读管道
 
    int ret = -1;
    int fd = -1;
    char buf[SIZE];
 
    // 1. 以只读的方式打开一个管道文件
    fd = open("/home/ljf/Desktop/fifotest", O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return 1;
    }
    printf("readonly open success.\n");
 
    // 2. 循环读管道
    while (1) {
        memset(buf, 0, SIZE);
        ret = read(fd, buf, SIZE);
        if (ret <= 0) {
            perror("read");
            break;
        }
        printf("读出buf：%s\n", buf);
    }
 
    // 3. 关闭FIFO文件
    close(fd);
 
    return 0;
}