#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
 
void showSet(sigset_t* set) { // 显示信号集
    for (int i = 1; i < 32; i++) {
        if (sigismember(set, i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    putchar('\n');
}
 
int main(int argc, const char* argv[]) {
 
    int i = 0;
 
    // 定义信号集
    sigset_t set;
 
    // 清空信号集
    sigemptyset(&set);
    puts("sigemptyset后的信号集：");
    showSet(&set);
 
    // 将所有的信号加入信号集
    sigfillset(&set);
    puts("sigfillset后的信号集：");
    showSet(&set);
 
    // 将信号1,3从信号集中移除
    sigdelset(&set, SIGHUP);
    sigdelset(&set, SIGQUIT);
    puts("sigdelset后的信号集：");
    showSet(&set);
 
    // 将信号1,3加入信号集
    sigaddset(&set, SIGHUP);
    sigaddset(&set, SIGQUIT);
    puts("sigaddset后的信号集：");
    showSet(&set);
 
    return 0;
}