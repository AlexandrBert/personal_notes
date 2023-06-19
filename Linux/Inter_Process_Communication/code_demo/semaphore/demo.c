#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

/* 定义全局变量key和semid，方便在函数中进行访问 */
key_t key;
int   semid;

/* 定义P和V操作函数 */
void P(int n)
{
    struct sembuf buf;
    buf.sem_num = 0;    // 操作的信号量标识符为0
    buf.sem_op  = -n;   // 执行的操作为减少n个信号量
    buf.sem_flg = SEM_UNDO;
    semop(semid, &buf, 1);
}

void V(int n)
{
    struct sembuf buf;
    buf.sem_num = 0;    // 操作的信号量标识符为0
    buf.sem_op  = n;    // 执行的操作为增加n个信号量
    buf.sem_flg = SEM_UNDO;
    semop(semid, &buf, 1);
}

/* 子进程函数 */
void child()
{
    printf("Child process: Attempting to lock semaphore\n");
    P(1);               // 请求一个信号量
    printf("Child process: Semaphore locked\n");

    /* 释放信号量 */
    printf("Child process: Releasing semaphore\n");
    V(1);

    exit(0);
}

/* 父进程函数 */
void parent()
{
    printf("Parent process: Attempting to lock semaphore\n");
    P(1);              // 请求一个信号量
    printf("Parent process: Semaphore locked\n");

    /* 等待子进程结束 */
    wait(NULL);

    /* 释放信号量 */
    printf("Parent process: Releasing semaphore\n");
    V(1);

    exit(0);
}

int main()
{
    /* 创建一个SystemV信号量集，标识符为1234 */
    key = ftok(".", 's');   // 使用当前目录和's'作为key
    semid = semget(key, 1, IPC_CREAT | 0666);

    /* 对新创建的信号量集进行初始化 */
    semctl(semid, 0, SETVAL, 1);  // 初始值为1

    /* 创建子进程 */
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)      // 子进程
    {
        child();
    }
    else                   // 父进程
    {
        parent();
    }

    /* 删除信号量集 */
    semctl(semid, 0, IPC_RMID, 0);

    return 0;
}
