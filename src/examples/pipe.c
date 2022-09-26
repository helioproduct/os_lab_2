#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe open error\n");
        return -1;
    }
    int id = fork();
    if (id == -1) {
        perror("fork error\n");
        return -2;
    }
    if (id == 0) {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x); 
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    else {z 
        wait(NULL);
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        printf("%d\n", y);
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}