#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("raise before!");
    /* 这条语句不会打印，因为printf只有在加了'\n' 时才会写入到内核*/
    raise(SIGKILL); //杀进程，直接调用_exit()，而不是库函数exit()
    // raise(SIGHUP); //挂起进程
    // raise(SIGBUS); //挂起进程
    printf("raise after!\n");

    return 0;
}