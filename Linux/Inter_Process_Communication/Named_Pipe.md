# 命名管道

fifo - 先进先出的特殊文件, 命名管道，又称有名管道。

## 命名管道描述
一个先进先出（FIFO）的特殊文件（一个命名管道）类似一个管道，但它是作为文件系统的一部分来访问的。可以同时有多个进程打开它进行读写。当进程间通过 FIFO 交换数据时，内核会在其内部传送所有数据，而不会写入文件系统。

即，FIFO 特殊文件在文件系统中没有任何内容：文件系统中的文件条目只是作为一个参照点而已，使得进程可以用文件系统中的一个名字(innode号)对其进行访问。

内核会为至少有一个进程打开了的 FIFO 特殊文件维护单独一个管道对象。在数据经由 FIFO 传输之前，FIFO 的两端（读和写）必须同时打开。一般来说，打开 FIFO 的行为会阻塞，直至另一端也被打开。一个进程可以使用非阻塞模式打开一个 FIFO。这种情况下，即使写端没有打开， 打开读端还是会成功。但是，如果读端没有打开，打开写端会失败，并且得到 一个 ENXIO （设备或地址不存在）。

在 Linux 下，不管是阻塞还是非阻塞模式，打开一个 FIFO 用作同时读写都会成功。 POSIX 对于这种情况未进行定义。这个可以用来在读端不可用的情况下打开写端。一个进程在同时用同一个  FIFO  的两端来实现自己和自己通信的时候要特别小心， 应避免出现死锁。

## 命名管道的特点

1. 不同于无名管道只能在有亲缘关系的进程间通信，命名管道可以在非亲缘关系的进程间通信；
2.  FIFO 文件存在于文件系统，与一个路径名关联，但是其内容存在与内存中，无法直接打开文件查看内容；
3.  创建 FIFO 的进程即使退出了，FIFO 文件仍然存在与文件系统中供后续使用；
4.  有名管道可用open打开，用read、write、close、unlink等操作，但同样不可lseek；
5.  一个以只写方式打开管道的进程会被阻塞，直到另一个进程以只读方式打开该管道；
6.  一个以只读方式打开管道的进程会被阻塞，直到另一个进程以只写方式打开该管道；

### 命名管道创建函数
```C
#include<sys/types.h>
#include<sys/stat.h>
 
int mkfifo(const char* pathname, mode_t mode);
/*
功能：
    以mode权限创建有名管道pathname
参数：
    pathname：创建FIFO文件的路径名，相对路径、绝对路径都可。
    mode：文件的权限，与open函数的mode参数一样。权限列表如下
            0 | --- | 无权限
            1 | --x | 只具有执行权限
            2 | -w- | 只具有写权限
            3 | -wx | 具有写和执行全新啊
            4 | r-- | 只具有读权限
            5 | r-x | 具有读和执行权限
            6 | rw- | 具有读和写权限
            7 | rwx | 具有读、写和执行权限
返回值：
    成功：0
    失败：若文件存在则返回-1
*/
```

## mkfifo 示例
```c
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
 
int main(int argc, const char* argv[]) {
    int ret = -1;

    /* 创建权限为0644的有名管道，无法使用windows的共享文件夹，因为Windows不支持FIFO */
    ret = mkfifo("fifotest", 0644);
    if (-1 == ret) {
        perror("mkfifo");
        return 1;
    }
    printf("fifo file created.\n");
    return 0;
}
```

## 命名管道的使用

### 创建并写入 FIFO
```c
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
```

### 读取 FIFO 中的文件内容
```c
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
    fd = open("fifotest", O_RDONLY);
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
```

