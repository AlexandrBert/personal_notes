#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    printf("pause before!\n");
    pause();
    printf("pause after!\n");

    return 0;
}