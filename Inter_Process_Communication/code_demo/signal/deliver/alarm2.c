#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int i=0;

    printf("raise before!\n");
    alarm(8); //使用alarm时会开始闹钟计时
    printf("raise after!\n");

    /* 如果进程直接结束，就不会执行后面的语句了，这里增加比alarm大的延时 */
    while(i<20)
    {
        i++;
        sleep(1);
        printf("during a while \n");

        if(i == 4){
            printf("before clear alarm \n");
            alarm(0);/* 再次使用alarm信号可以清除（撤回）之前定义的所有alarm */
            printf("after clear alarm \n");
        }
    }

    return 0;
}