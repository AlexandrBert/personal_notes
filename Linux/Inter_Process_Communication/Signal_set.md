# 信号集

每个进程的PCB中有两个信号集合：阻塞信号集 & 未决信号集。

两个集合都是用位图表示信号的状态，1表示阻塞或未决。

仅可设置阻塞信号集；未决信号集由内核自动设置。

（1）阻塞信号集：
    将某信号加入该阻塞信号集，该信号将被阻塞；
    若被阻塞期间收到该信号，则不会被处理；
    但在解除阻塞后，阻塞期间收到的那次信号仍然会被处理，相当于滞后处理该信号。

（2）未决信号集：
    某信号产生，未决信号集中描述该信号的状态位被置为1，表示该信号为未决状态；当信号被处理，该信号对应的状态位被置为0。
    信号产生后由于某些原因（主要为被阻塞）不能抵达，这些信号状态为未决状态。
    信号被阻塞期间，一直处于未决状态。


## 信号集函数

### 信号集操作函数
```c
#include<signal.h>
 
int sigemptyset(sigset_t* set);           // 将set信号集置空
int sigfillset(sigset_t* set);            // 将所有信号加入set信号集
int sigaddset(sigset_t* set, int signo);  // 将signo信号加入set信号集
int sigdelset(sigset_t* set, int signo);  // 将signo信号从set信号集移除
int sigismember(const sigset_t* set, int signo); // 判断set信号集中是否存在signo信号
 
/*sigset_t为二进制位图*/
```

### sigprocmask() 函数
```c
#include<signal.h>
 
int sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
/*
功能：
    根据how指定的方法对进程的阻塞信号集进行操作。
    新的阻塞信号集由set指定，原先的阻塞信号集由oldset保存。
参数：
    how：对阻塞信号集的操作方式：
        SIG_BLOCK：向阻塞信号集中添加set信号集，新的信号集是set与oldset的并集。
                   相当于mask = mask | set;
        SIG_UNBLOCK：从阻塞信号集中删除set集合。
                     相当于mask = mask & ~set;
        SIG_SETMASK：将阻塞信号集设置为set。
                     相当于mask = set;
    set：要操作的信号集地址。
         若为NULL，则不改变阻塞信号集。仅将当前的阻塞信号集保存到oldset中。
    
    oldset：保存原先阻塞信号集的地址。
返回值：
    成功：0
    失败：-1，失败时错误码只可能是EINVAL，表示参数how不合法。  
*/
```

### sigpending() 函数
```c
#include<signal.h>
 
int sigpending(sigset_t* set);
/*
功能：
    获取未决信号集存入set集合
参数：
    set：存储未决信号集
返回值：
    成功：0
    失败：-1
*/
```
