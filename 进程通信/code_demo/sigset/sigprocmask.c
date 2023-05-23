#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
 
void func0(int signum) {
    printf("捕捉到信号：%d\n", signum);
}
 
void func1(int signum) {
    printf("捕捉到信号：%d\n", signum);
}
 
int main(int argc, const char* argv[]) {
 
    int ret = -1;
 
    // 信号集
    sigset_t set;
    sigset_t old;
 
    /*注册信号处理函数。*/
    // SIGINT: Ctrl + c  2号信号
    signal(SIGINT, func0);
 
    /*SIGQUIT: Ctrl + \*/
    signal(SIGQUIT, func1);
 
    /*将SIGINT加入阻塞信号集*/
    printf("按回车键阻塞信号2 SIGINT.\n");
 
    // 只能输入回车，输入一个字符再回车，就相当于输入两个字符；第二个回车被下面的getchar接收。
    getchar();
 
    sigemptyset(&set); // 清空信号集
    sigaddset(&set, SIGINT); // 将2号信号加入信号集
    sigemptyset(&old); // 清空信号集
    ret = sigprocmask(SIG_BLOCK, &set, &old); // 设置阻塞信号集
    if (-1 == ret) {
        perror("sigprocmask");
        return 1;
    }
    printf("2号信号SIGINT屏蔽成功.\n");
    printf("按下回车键解除2号信号的屏蔽.\n");
 
    getchar();
 
    /*将阻塞信号集设置为原先的集合*/
    ret = sigprocmask(SIG_SETMASK, &old, NULL);
    if (-1 == ret) {
        perror("sigprocmask");
        return 1;
    }
 
    getchar();
 
    return 0;
}