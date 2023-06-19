#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
 
int main(int argc, const char* argv[]) {
 
    int ret = -1;
    sigset_t new;
    sigset_t old;
    sigset_t set;
 
    sigemptyset(&new); // 清空信号集set
    sigemptyset(&old); // 清空信号集set
    sigemptyset(&set); // 清空信号集set
    /*将信号2、3放入信号集*/
    sigaddset(&new, SIGINT);
    sigaddset(&new, SIGQUIT);
 
    ret = sigprocmask(SIG_BLOCK, &new, &old); // 将信号2、3放入阻塞信号集
    if (-1 == ret) {
        perror("sigprocmask");
        return 1;
    }
 
    getchar();
 
    ret = sigpending(&set); // 获取阻塞信号集
    if (-1 == ret) {
        perror("sigpending");
        return 1;
    }
 
    for (int i = 1;i < 32;i++) { // 打印阻塞信号集
        if (sigismember(&set, i)) {
            printf("%d ", i);
        }
    }
    putchar('\n');
 
    return 0;
}