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

    printf("Hello world! from %d\n", id);

    return 0;
}