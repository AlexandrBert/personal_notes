# Linux 字符设备驱动的应用

## 编写应用程序操作设备节点
1. 编写应用字符设备驱动的源码；
    -  使用 open() 函数打开字符设备。
    -  使用 read()/write() 函数操作字符设备。
    -  使用 close() 函数关闭字符设备。
2. 使用交叉编译工具链编译源码，生成可执行程序 app_my_dev；
3. 将可执行程序传输到目标机，赋予可执行权限；
4. 执行可执行程序，观察执行结果。

### 涉及函数
1. write() 函数
- 函数原型 ： `ssize_t write(int fd, const void *buf, size_t count)` 。
- 功能描述 ： 向指定的文件描述符 fd ，写入 count 个字节的 buf 内存中的数据。
- 参数 ：
    - fd ： 文件描述符。
    - buf ： 指向缓冲区的指针。
    - count ： 缓冲区大小。
- 返回值 ： 成功返回写入的字节数，失败返回 -1，错误号存于 errno 中。

2. read() 函数
- 函数原型 ： `ssize_t read(int fd, void *buf, size_t count)` 。
- 功能描述 ： 从指定的文件描述符 fd ，读取 count 个字节到 buf 内存中。
- 参数 ：
    - fd ： 文件描述符。
    - buf ： 指向缓冲区的指针。
    - count ： 缓冲区大小。
- 返回值 ： 成功返回读取的字节数，失败返回 -1，错误号存于 errno 中。

3. open() 函数
- 函数原型 ： `int open(const char *pathname, int flags)` 。
- 功能描述 ： 打开文件。
- 参数 ：
    - pathname ： 文件路径。
    - flags ： 打开文件的方式。
- 返回值 ： 成功返回文件描述符，失败返回 -1，错误号存于 errno 中。

4. close() 函数
- 函数原型 ： `int close(int fd)` 。
- 功能描述 ： 关闭文件。
- 参数 ：
    - fd ： 文件描述符。
- 返回值 ： 成功返回 0，失败返回 -1，错误号存于 errno 中。

5. ioctl() 函数
- 函数原型 ： `int ioctl(int fd, int cmd, ...)` 。
- 功能描述 ： 控制设备。
- 参数 ：
    - fd ： 文件描述符。
    - cmd ： 控制命令。
    - ... ： 控制参数。
- 返回值 ： 成功返回 0，失败返回 -1，错误号存于 errno 中。

6. lseek() 函数
- 函数原型 ： `off_t lseek(int fd, off_t offset, int whence)` 。
- 功能描述 ： 改变文件偏移量。
- 参数 ：
    - fd ： 文件描述符。
    - offset ： 文件偏移量。
    - whence ： 偏移量改变的方式。
- 返回值 ： 成功返回新的文件偏移量，失败返回 -1，错误号存于 errno 中。

### 源码
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char val;

    fd = open("/dev/my_dev", O_RDWR);
    if(fd < 0) {
        printf("can't open /dev/my_dev");
        return -1;
    }

    val = 0x12;
    write(fd, &val, 1);
    printf("write to /dev/my_dev :: val = 0x%x\n", val);
    read(fd, &val, 1);
    printf("write from /dev/my_dev :: val = 0x%x\n", val);

    close(fd);
}

```

## 使用 cat 和 echo 命令操作设备节点

对于驱动已经实现了 cat 和 echo 命令的操作，用户可以使用 cat 和 echo 命令来操作设备节点。

### 涉及函数
1. simple_strtoul() 函数
- 函数原型 ： `unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base)` 。
- 功能描述 ： 将一个字符串转换成unsigend long long型数据。
- 参数 ：
    - cp ： 待转换的字符串。
    - endp ： 转换后的数据存放的地址，为 NULL 时表示直接将 cp 转换成十进制 ull 数据。
    - base ： 转换的进制基数。如果设置为 0 ，表示通过cp来自动判断基数，函数自动识别基数，并按10进制输出。例如"0xa",就会把字符串当做16进制处理，输出的为10。
- 返回值 ： 转换后数据。

### cat 和 echo 命令实现
修改驱动程序中的 my_dev_read() 函数和 my_dev_write() 函数，实现 cat 和 echo 命令的操作。
```c
/* cat命令时,将会调用该函数 */
static ssize_t my_dev_read(struct file *file, char __user *buf, size_t count,
		loff_t *offset)
{
	int ret;
    char temp[16];
    char status;

    if(*offset > 0)
        return 0;

    /* 将输入的char类型转化为十进制数值字符串形式存入缓存中 */
    count = sprintf(temp, "%u\n", val);

	ret = copy_to_user(buf, temp, count+1);
    if(ret < 0) {
        printk("ret = %d\n", ret);
        status = -EFAULT;
    } else {
        *offset += count;
        status = count;
    }

	return status;
}

/* echo命令时,将会调用该函数 */
static ssize_t my_dev_write(struct file *file, const char __user *buf,
		size_t count, loff_t *offset)
{
	int ret;
    char temp[16];
    char status;

    memset(temp, 0, 16);

	ret = copy_from_user(&val, buf, count);
    if(ret < 0)
    {
        printk("ret = %d\n", ret);
        status = -EFAULT;
        goto err;
    }
    
    /* 将一个字符串转换成unsigend long long型十进制数据。 */
    val = simple_strtoul(temp, NULL, 16);

    if(!status)
        status = count;

err:
	return status;
}
```
