#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
 
// 信号处理函数
void func(int signum) {
    printf("捕捉到信号%d.\n", signum);
}
 
int main(int argc, const char* argv[]) {
 
    int ret = -1;
    struct sigaction act;
 
    act.sa_handler = func;  // 自定义旧的信号处理函数
    act.sa_flags = 0;  // 使用旧的信号处理函数
 
    ret = sigaction(SIGINT, &act, NULL);
    if (-1 == ret) {
        perror("sigaction");
        return 1;
    }
 
    printf("按下任意键继续...\n");
    getchar();
    return 0;
}