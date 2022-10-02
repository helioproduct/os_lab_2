#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char* read_string() 
{
    int len = 0;
    int capacity = 1; 
    char *string = (char*) malloc(sizeof(char));
    char c = getchar();
    if (c == '\n') c = getchar();
    while (c != '\n') {
        string[len++] = c;
        if (len >= capacity) {
            capacity *= 2;
            string = (char*) realloc(string, capacity * sizeof(char));
        }
        c = getchar();
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

    printf("Enter path to the file: ");
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
        if (execv("child.out", NULL) == -1)  {
            perror("error executing child process\n");
            return 5;
        }
    }   
    else {
        close(fd[1]);
        double sum;
        read(fd[0], &sum, sizeof(sum));
        printf("[%d] Total sum = %lf\n", getpid(), sum);
        close(fd[0]);
    }
    return 0;
}
