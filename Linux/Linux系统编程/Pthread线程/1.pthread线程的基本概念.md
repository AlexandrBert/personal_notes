# 线程的基本概念

## 什么是线程

- Linux man 手册定义（pthreads(7)）：

    POSIX.1规定了一组用于线程编程的接口（函数、头文件等），通常称为 POSIX 线程或 Pthreads 。**一个进程可以包含多个线程，它们都执行同一个程序。这些线程共享相同的全局内存（数据和堆段），但每个线程都有自己的栈（自动变量）。**

    POSIX.1还要求线程共享一系列其他属性（即，这些属性是进程范围的，而不是每个线程独立的）：
    |进程中的线程共享的属性|释义|    
    |:-:|:-:|
    |process ID|进程ID|
    |parent process ID|父进程ID|
    |process group ID and session ID|进程组ID和会话ID|
    |controlling terminal|控制终端|
    |user and group IDs|用户和用户组ID|
    |open file descriptors|打开文件描述符|
    |record locks (see fcntl(2))|记录锁|
    |signal dispositions|信号配置|
    |file mode creation mask (umask(2))|文件权限掩码|
    |current directory (chdir(2)) and root directory (chroot(2))|当前目录和根目录|
    |interval timers (setitimer(2)) and POSIX timers (timer_create(2))|时间间隔定时器和 POSIX 定时器|
    |nice value (setpriority(2))|优先值|
    |resource limits (setrlimit(2))|资源限制|
    |measurements of the consumption of CPU time (times(2)) and resources (getrusage(2))|CPU时间消耗和资源消耗的测量|
    |||

    除了堆栈，POSIX.1还指定每个线程的其他各种属性是不同的，包括:
    |进程中的线程不同属性|释义|    
    |:-:|:-:|
    |thread ID (the pthread_t data type)|线程ID|
    |signal mask (pthread_sigmask(3))|信号掩码|
    |the errno variable|errno变量|
    |alternate signal stack (sigaltstack(2))|替代的信号堆栈|
    |real-time scheduling policy and priority (sched(7))|实时调度策略和优先级|
    |||

    以下 Linux 特有的功能也是每个线程独立的:

    |进程中的线程不同属性|释义|
    |:-:|:-:|
    |capabilities (see capabilities(7))|容量|
    |CPU affinity (sched_setaffinity(2))|CPU亲和力|
    |||

1. **Pthreads函数返回值**  
    大多数Pthreads函数在成功时返回0，失败时返回错误号。请注意，Pthreads函数不会设置errno。对于每个可能返回错误的Pthreads函数，POSIX.1-2001规定该函数不能因为EINTR错误而失败。

2. **线程ID (Thread IDs)**  
    进程中的每个线程都有一个唯一的线程标识符（存储在类型`pthread_t`中）。这个标识符由`pthread_create(3)`的调用者返回，并且线程可以使用`pthread_self(3)`来获取自己的线程标识符。

    线程ID仅在进程内部保证唯一。
    （在所有接受线程ID作为参数的Pthreads函数中，该ID定义为指向与调用者相同进程中的线程。）
    
    在终止的线程被join后或分离的线程终止后，系统可能会重用线程ID。POSIX规定：“如果应用程序尝试使用已结束生命周期的线程ID，行为是未定义的。”

3. **线程安全函数**  
    线程安全函数是指可以在多个线程同时调用时安全地（即无论如何调用，都会产生相同的结果）使用的函数。

    POSIX.1-2001和POSIX.1-2008要求标准中指定的所有函数都必须是线程安全的，除了以下函数：
    ```c
    asctime()
    basename()
    catgets()
    crypt()
    ctermid() if passed a non-NULL argument
    ctime()
    dbm_clearerr()
    dbm_close()
    dbm_delete()
    dbm_error()
    dbm_fetch()
    dbm_firstkey()
    dbm_nextkey()
    dbm_open()
    dbm_store()
    dirname()
    dlerror()
    drand48()
    ecvt() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    encrypt()
    endgrent()
    endpwent()
    endutxent()
    fcvt() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    ftw()
    gcvt() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    getc_unlocked()
    getchar_unlocked()
    getdate()
    getenv()
    getgrent()
    getgrgid()
    getgrnam()
    gethostbyaddr() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    gethostbyname() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    gethostent()
    getlogin()
    getnetbyaddr()
    getnetbyname()
    getnetent()
    getopt()
    getprotobyname()
    getprotobynumber()
    getprotoent()
    getpwent()
    getpwnam()
    getpwuid()
    getservbyname()
    getservbyport()
    getservent()
    getutxent()
    getutxid()
    getutxline()
    gmtime()
    hcreate()
    hdestroy()
    hsearch()
    inet_ntoa()
    l64a()
    lgamma()
    lgammaf()
    lgammal()
    localeconv()
    localtime()
    lrand48()
    mrand48()
    nftw()
    nl_langinfo()
    ptsname()
    putc_unlocked()
    putchar_unlocked()
    putenv()
    pututxline()
    rand()
    readdir()
    setenv()
    setgrent()
    setkey()
    setpwent()
    setutxent()
    strerror()
    strsignal() [Added in POSIX.1-2008]
    strtok()
    system() [Added in POSIX.1-2008]
    tmpnam() if passed a non-NULL argument
    ttyname()
    unsetenv()
    wcrtomb() if its final argument is NULL
    wcsrtombs() if its final argument is NULL
    wcstombs()
    wctomb()
    ```

4. **异步取消安全函数 （Async-cancel-safe）**

    异步取消安全函数是指可以在启用异步取消功能的应用程序中安全调用的函数（参见 `pthread_setcancelstate(3)` ）。

    根据POSIX.1-2001和POSIX.1-2008的规定，只有以下函数需要是异步取消安全的：
    ```c
    pthread_cancel()
    pthread_setcancelstate()
    pthread_setcanceltype()
    ```

5. **取消点(Cancellation points)** 

    POSIX.1规定，某些函数必须是取消点，而其他一些函数可能是取消点。如果一个线程是可取消的，其取消类型是延迟的，并且线程有待取消的请求，那么当线程调用一个取消点函数时，线程将被取消。

    以下函数根据POSIX.1-2001和/或POSIX.1-2008的规定需要是取消点：
    ```c
    accept()
    aio_suspend()
    clock_nanosleep()
    close()
    connect()
    creat()
    fcntl() F_SETLKW
    fdatasync()
    fsync()
    getmsg()
    getpmsg()
    lockf() F_LOCK
    mq_receive()
    mq_send()
    mq_timedreceive()
    mq_timedsend()
    msgrcv()
    msgsnd()
    msync()
    nanosleep()
    open()
    openat() [Added in POSIX.1-2008]
    pause()
    poll()
    pread()
    pselect()
    pthread_cond_timedwait()
    pthread_cond_wait()
    pthread_join()
    pthread_testcancel()
    putmsg()
    putpmsg()
    pwrite()
    read()
    readv()
    recv()
    recvfrom()
    recvmsg()
    select()
    sem_timedwait()
    sem_wait()
    send()
    sendmsg()
    sendto()
    sigpause() [POSIX.1-2001 only (moves to "may" list in POSIX.1-2008)]
    sigsuspend()
    sigtimedwait()
    sigwait()
    sigwaitinfo()
    sleep()
    system()
    tcdrain()
    usleep() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
    wait()
    waitid()
    waitpid()
    write()
    writev()
    ```

    根据 POSIX.1-2001 和/或 POSIX.1-2008 标准，以下函数可以是取消点：
    ```c
    access()
    asctime()
    asctime_r()
    catclose()
    catgets()
    catopen()
    chmod() [Added in POSIX.1-2008]
    chown() [Added in POSIX.1-2008]
    closedir()
    closelog()
    ctermid()
    ctime()
    ctime_r()
    dbm_close()
    dbm_delete()
    dbm_fetch()
    dbm_nextkey()
    dbm_open()
    dbm_store()
    dlclose()
    dlopen()
    dprintf() [Added in POSIX.1-2008]
    endgrent()
    endhostent()
    endnetent()
    endprotoent()
    endpwent()
    endservent()
    endutxent()
    faccessat() [Added in POSIX.1-2008]
    fchmod() [Added in POSIX.1-2008]
    fchmodat() [Added in POSIX.1-2008]
    fchown() [Added in POSIX.1-2008]
    fchownat() [Added in POSIX.1-2008]
    fclose()
    fcntl() (for any value of cmd argument)
    fflush()
    fgetc()
    fgetpos()
    fgets()
    fgetwc()
    fgetws()
    fmtmsg()
    fopen()
    fpathconf()
    fprintf()
    fputc()
    fputs()
    fputwc()
    fputws()
    fread()
    freopen()
    fscanf()
    fseek()
    fseeko()
    fsetpos()
    fstat()
    fstatat() [Added in POSIX.1-2008]
    ftell()
    ftello()
    ftw()
    futimens() [Added in POSIX.1-2008]
    fwprintf()
    fwrite()
    fwscanf()
    getaddrinfo()
    getc()
    getc_unlocked()
    getchar()
    getchar_unlocked()
    getcwd()
    getdate()
    getdelim() [Added in POSIX.1-2008]
    getgrent()
    getgrgid()
    getgrgid_r()
    getgrnam()
    getgrnam_r()
    gethostbyaddr() [SUSv3 only (function removed in POSIX.1-2008)]
    gethostbyname() [SUSv3 only (function removed in POSIX.1-2008)]
    gethostent()
    gethostid()
    gethostname()
    getline() [Added in POSIX.1-2008]
    getlogin()
    getlogin_r()
    getnameinfo()
    getnetbyaddr()
    getnetbyname()
    getnetent()
    getopt() (if opterr is nonzero)
    getprotobyname()
    getprotobynumber()
    getprotoent()
    getpwent()
    getpwnam()
    getpwnam_r()
    getpwuid()
    getpwuid_r()
    gets()
    getservbyname()
    getservbyport()
    getservent()
    getutxent()
    getutxid()
    getutxline()
    getwc()
    getwchar()
    getwd() [SUSv3 only (function removed in POSIX.1-2008)]
    glob()
    iconv_close()
    iconv_open()
    ioctl()
    link()
    linkat() [Added in POSIX.1-2008]
    lio_listio() [Added in POSIX.1-2008]
    localtime()
    localtime_r()
    lockf() [Added in POSIX.1-2008]
    lseek()
    lstat()
    mkdir() [Added in POSIX.1-2008]
    mkdirat() [Added in POSIX.1-2008]
    mkdtemp() [Added in POSIX.1-2008]
    mkfifo() [Added in POSIX.1-2008]
    mkfifoat() [Added in POSIX.1-2008]
    mknod() [Added in POSIX.1-2008]
    mknodat() [Added in POSIX.1-2008]
    mkstemp()
    mktime()
    nftw()
    opendir()
    openlog()
    pathconf()
    pclose()
    perror()
    popen()
    posix_fadvise()
    posix_fallocate()
    posix_madvise()
    posix_openpt()
    posix_spawn()
    posix_spawnp()
    posix_trace_clear()
    posix_trace_close()
    posix_trace_create()
    posix_trace_create_withlog()
    posix_trace_eventtypelist_getnext_id()
    posix_trace_eventtypelist_rewind()
    posix_trace_flush()
    posix_trace_get_attr()
    posix_trace_get_filter()
    posix_trace_get_status()
    posix_trace_getnext_event()
    posix_trace_open()
    posix_trace_rewind()
    posix_trace_set_filter()
    posix_trace_shutdown()
    posix_trace_timedgetnext_event()
    posix_typed_mem_open()
    printf()
    psiginfo() [Added in POSIX.1-2008]
    psignal() [Added in POSIX.1-2008]
    pthread_rwlock_rdlock()
    pthread_rwlock_timedrdlock()
    pthread_rwlock_timedwrlock()
    pthread_rwlock_wrlock()
    putc()
    putc_unlocked()
    putchar()
    putchar_unlocked()
    puts()
    pututxline()
    putwc()
    putwchar()
    readdir()
    readdir_r()
    readlink() [Added in POSIX.1-2008]
    readlinkat() [Added in POSIX.1-2008]
    remove()
    rename()
    renameat() [Added in POSIX.1-2008]
    rewind()
    rewinddir()
    scandir() [Added in POSIX.1-2008]
    scanf()
    seekdir()
    semop()
    setgrent()
    sethostent()
    setnetent()
    setprotoent()
    setpwent()
    setservent()
    setutxent()
    sigpause() [Added in POSIX.1-2008]
    stat()
    strerror()
    strerror_r()
    strftime()
    symlink()
    symlinkat() [Added in POSIX.1-2008]
    sync()
    syslog()
    tmpfile()
    tmpnam()
    ttyname()
    ttyname_r()
    tzset()
    ungetc()
    ungetwc()
    unlink()
    unlinkat() [Added in POSIX.1-2008]
    utime() [Added in POSIX.1-2008]
    utimensat() [Added in POSIX.1-2008]
    utimes() [Added in POSIX.1-2008]
    vdprintf() [Added in POSIX.1-2008]
    vfprintf()
    vfwprintf()
    vprintf()
    vwprintf()
    wcsftime()
    wordexp()
    wprintf()
    wscanf()
    ```

    具体实现时还可以将标准中未指定的其他函数标记为取消点。特别是，实现时很可能将任何可能阻塞的非标准函数标记为取消点。（这包括大多数可能涉及文件的函数。）

