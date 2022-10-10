#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "string_utils.h"

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe open error\n");
        return 1;
    }

    char hello_message[] = "Enter path to file: ";
    write(STDIN_FILENO, hello_message, sizeof(hello_message));
    char *path_to_file = read_string(STDIN_FILENO);

    int id = fork();
    if (id == -1) {
        perror("fork error\n");
        return 2;
    }
    if (id == 0) {
        close(fd[0]);
        int source_fd = open(path_to_file, O_RDONLY);
        if (source_fd == -1) {
            perror("File open error\n");
            return 3;
        }  
        if (dup2(source_fd, STDIN_FILENO) == -1) {
            perror("Error changing stdin\n");
            return 4;
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Error changing stdout\n");
            return 5;
        }
        if (execv("child", NULL) == -1)  {
            perror("error executing child process\n");
            return 6;
        }
        close(fd[1]);
    }   
    else {
        close(fd[1]);
        float sum;
        read(fd[0], &sum, sizeof(sum));

        char result_message[] = "Total sum = ";
        write(STDOUT_FILENO, result_message, sizeof(result_message));

        gcvt(sum, 10, result_message);
        write(STDOUT_FILENO, result_message, sizeof(result_message));

        close(fd[0]);
    }
    return 0;
}
