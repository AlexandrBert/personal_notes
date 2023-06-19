#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
 
#define SIZE 128
 
int main(int argc, const char* argv[]) {
    int i = 0;
    int ret = -1;
    int fd = -1;
    char buf[SIZE];

    /* 创建权限为0644的有名管道，无法使用windows的共享文件夹，因为Windows不支持FIFO */
    if((mkfifo("/home/ljf/Desktop/fifotest",O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
    {
		perror("mkfifo");
        return 1;
    }
    printf("fifo file created.\n");
 
    // 1. 以只写的方式打开一个管道文件
    fd = open("/home/ljf/Desktop/fifotest", O_WRONLY);
    if (-1 == fd) {
        perror("open");
        return 1;
    }
    printf("writeonly open success.\n");
 
    // 2. 写管道
    while (1) {
        memset(buf, 0, SIZE);
        sprintf(buf, "hello %d", i++);
        ret = write(fd, buf, strlen(buf));
        if (ret <= 0) {
            perror("write");
            break;
        }
        printf("写入%d个字节.\n", ret);
        sleep(1);
    }
 
    // 3. 关闭FIFO文件
    close(fd);
 
    return 0;
}