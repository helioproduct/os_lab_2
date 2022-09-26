#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int arr[] = {1, 2, 3, 4, 1, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int start, end;

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe open error\n");
        return -1;
    }

    int id = fork();
    if (id == -1) {
        perror("fork error");
        return -2;
    }
    if (id == 0) {
        start = 0;
        end = start + size / 2;
    }
    else {
        start = size / 2;
        end = size;
    }

    int sum = 0;
    int i;
    for (i = start; i < end; i++) {
        sum += arr[i];
    }

    printf("Calculated partical sum: %d\n", sum);
    if (id == 0) {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(int)) == -1) {
            perror("write error\n");
            return -3;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int sum_from_child;
        if (read(fd[0], &sum_from_child, sizeof(int)) == -1) {
            perror("read error\n");
            return -4;
        }
        close(fd[0]);
        printf("Total sum = %d\n", sum + sum_from_child);
        wait(NULL);
    }    

    return 0;
}