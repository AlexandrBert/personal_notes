# LINUX 文件IO

Linux系统的文件IO（Input/Output）操作是指对磁盘文件进行读写操作，是计算机系统中重要的基础操作之一。下面是关于Linux文件IO的详细介绍：

1. 文件描述符(File Descriptors)

在Linux系统中，所有的I/O操作都通过文件描述符(File Descriptors)来进行。每一个进程启动时，都有3个默认打开的文件描述符分别为0, 1和2, 分别对应标准输入(STDIN_FILENO)，标准输出(STDOUT_FILENO)和标准错误(STDERR_FILENO)。

2. 打开文件

在程序中使用open系统调用可以打开一个文件，它的原型如下：

```C
int open(const char *pathname, int flags, mode_t mode);
```

其中第一个参数为文件路径名，第二个参数为打开文件的方式和读写模式，第三个参数为权限标志。open函数返回的文件描述符可以作为后面IO操作的参数。

3. 关闭文件

在完成文件读写操作后，需要关闭文件，以释放相应的资源。close()函数可以关闭一个文件，它原型如下：

```C
int close(int fd);
```

其中，fd为要关闭的文件描述符。如果成功关闭文件，返回值为0，失败则返回-1。

4. 读取文件内容

读取文件内容可以使用系统调用read函数，其原型如下：

```C
ssize_t read(int fd, void *buf, size_t count);
```

其中，fd为文件描述符；buf为读取数据的缓存区；count为要读取的字节数。

read函数返回实际读取到的数据的字节数。如果返回值为0，则表示已经读到文件结尾(EOF)；如果返回值为-1，则表示读取出现了错误，可以通过errno变量来获取相应的错误信息。

5. 写入文件内容

写入文件内容可以使用write函数，其原型如下：

```C
ssize_t write(int fd, const void *buf, size_t count);
```

其中，fd为文件描述符；buf为写入数据的缓存区；count为写入数据的字节数。

write函数返回实际写入的字节数。如果返回值小于0，则表示出现了写入错误。

6. 定位文件指针

在操作文件时，需要知道当前读写位置。lseek系统调用可以让我们改变文件指针的位置，其原型如下：

```C
off_t lseek(int fd, off_t offset, int whence);
```

其中，fd为文件描述符；offset为偏移量；whence参数用于指定偏移量的计算方式。常用的计算方式包括SEEK_SET(从文件开头开始计算)，SEEK_CUR(从当前位置开始计算)和SEEK_END(从文件结尾开始计算)。

lseek函数返回当前文件指针的位置，以字节为单位。如果返回值为-1，则表示出现了错误。

7. 文件截断操作

truncate方法可以截断文件并清空文件尾部，原型如下：

```C
int truncate(const char *path, off_t length);
```

其中，path为文件路径名；length为截断后的文件大小。如果执行成功，truncate函数返回0，否则返回-1。

ftruncate方法与truncate类似，不过它是根据文件描述符来操作的:

```C
int ftruncate(int fd, off_t length);
```

其中，fd为文件描述符，length为截断后的长度。如果执行成功，ftruncate函数返回0，否则返回-1。

通过以上几个系统调用，我们可以对Linux系统中的文件进行各种读写操作，在实际应用开发中非常有用。同时需要注意防止I/O操作时出现的异常状况。
