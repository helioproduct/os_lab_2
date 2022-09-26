#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int id = fork();
    if (id == -1) {
        perror("Fork error\n");
        return -1;
    }
    if (id == 0) {
        printf("Hello from child process\n");
    }
    else {
        printf("hello from main process\n");
    }
    return 0;
}