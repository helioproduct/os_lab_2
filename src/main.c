#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

char* read_string() 
{
    int len = 0;
    int capacity = 1; 
    char *string = (char*) malloc(sizeof(char));
    char c;
    read(STDIN_FILENO, &c, sizeof(char));    
    while (c != '\n') {
        string[len++] = c;
        if (len >= capacity) {
            capacity *= 2;
            string = (char*) realloc(string, capacity * sizeof(char));
        }
        read(STDIN_FILENO, &c, 1);
    }
    string[len] = '\0';
    return string;
}

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe open error\n");
        return 1;
    }

    char hello_message[] = "Enter path to file: ";
    write(STDIN_FILENO, hello_message, sizeof(hello_message) / sizeof(char));

    char *path_to_file = read_string();
    
    int id = fork();
    if (id == -1) {
        perror("fork error\n");
        return 2;
    }
    if (id == 0) {
        close(fd[0]);
        FILE *source = freopen(path_to_file, "r", stdin);
        if (source == NULL) {
            perror("file open error");
            return 3;
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Error changing stdout\n");
            return 4;
        }
        if (execv("child", NULL) == -1)  {
            perror("error executing child process\n");
            return 5;
        }
    }   
    else {
        close(fd[1]);
        double sum;
        read(fd[0], &sum, sizeof(sum));

        char result_message[20];
        sprintf(result_message, "Total sum = %lf\n", sum);

        write(STDOUT_FILENO, result_message, 20);
        close(fd[0]);
    }
    return 0;
}
