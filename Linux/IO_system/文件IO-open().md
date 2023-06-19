# LINUX 文件IO

## 函数原型

在程序中使用open系统调用可以打开一个文件，它的原型如下：

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);

Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
openat():
    Since glibc 2.10:
        _POSIX_C_SOURCE >= 200809L
    Before glibc 2.10:
        _ATFILE_SOURCE
```

open的其中第一个参数为文件路径名，第二个参数为打开文件的方式和读写模式，第三个参数为权限标志。open函数返回的文件描述符可以作为后面IO操作的参数。

## 概述
1. open()系统调用打开由路径名指定的文件。如果指定的文件不存在，则可以选择（如果在标志中指定了O_CREAT）由open()创建。

2. open()的返回值是一个文件描述符，它是一个小的非负整数，在后续的系统调用（read(2)、write(2)、lseek(2)、fcntl(2)等）中用于引用打开的文件。成功调用返回的文件描述符将是进程当前未打开的最低编号文件描述符。

3. 默认情况下，新的文件描述符设置为在execve(2)之间保持打开状态（即，在fcntl(2)中描述的FD_CLOEXEC文件描述符标志最初被禁用）；下面描述的O_CLOEXEC标志可用于更改此默认值。文件偏移量设置为文件开头（参见lseek(2)）。

4. 对open()的调用创建新的打开文件描述符，在全局打开文件表中创建一个条目。打开文件描述符记录了文件偏移量和文件状态标志（参见下文）。文件描述符是对打开文件描述符的引用；如果pathname随后被删除或修改以引用不同的文件，则不会影响此引用。有关打开文件描述符的详细信息，请参阅NOTES。

5. 标志参数必须包括以下访问模式之一：O_RDONLY，O_WRONLY或O_RDWR。这些请求分别打开文件以只读，只写或读/写方式。

6. 此外，可以将一个或多个文件创建标志和文件状态标志按位或操作在标志中。文件创建标志为O_CLOEXEC、O_CREAT、O_DIRECTORY、O_EXCL、O_NOCTTY、O_NOFOLLOW、O_TMPFILE和O_TRUNC。文件状态标志是下面列出的所有其余标志。这两组标志之间的区别在于，文件创建标志影响打开操作本身的语义，而文件状态标志影响随后的输入/输出操作的语义。文件状态标志可以检索并（在某些情况下）修改；有关详细信息，请参阅fcntl(2)。

7. 文件创建标志和文件状态标志的完整列表如下：

    - **O_APPEND**  
    以追加模式打开文件。在每次write(2)之前，文件偏移量都定位在文件末尾，就像使用lseek(2)一样。文件偏移量的修改和写操作作为一个单独的原子步骤执行。
    如果多个进程同时向文件追加数据，则在NFS文件系统上可能会导致文件损坏。这是因为NFS不支持向文件追加，所以客户端内核必须模拟它，这不能在没有竞争条件的情况下完成。

    - **O_ASYNC**
    启用信号驱动的I/O：当输入或输出在此文件描述符上变得可能时生成一个信号（默认情况下为SIGIO，但可以通过fcntl(2)更改）。此功能仅适用于终端、伪终端、套接字以及（自Linux 2.6以来）管道和FIFO。有关详细信息，请参阅fcntl(2)。请参阅下面的BUGS。

    - **O_CLOEXEC（自Linux 2.6.23）**  
    为新文件描述符启用close-on-exec标志。指定此标志允许程序避免进行其他fcntl(2)F_SETFD操作以设置FD_CLOEXEC标志。  
    请注意，在一些多线程程序中使用此标志是必要的，因为使用单独的fcntl(2)F_SETFD操作设置FD_CLOEXEC标志无法避免其中一个线程打开文件描述符并尝试在另一个线程做fork(2)加上execve的同时设置其close-on-exec标志(2)。根据执行顺序，比赛可能导致由open()返回的文件描述符意外泄漏到由fork(2)创建的子进程执行的程序中。 （这类竞争原则上对任何创建文件描述符的系统调用是可能的，各种其他Linux系统调用提供了等效的O_CLOEXEC标志来处理此问题。）