#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* read_string() 
{
    int len = 0;
    int capacity = 1; // 1, так как точно будет '\0'
    char *string = (char*) malloc(sizeof(char));

    char c = getchar();
    if (c == '\n') c = getchar();
    while (c != '\n') {
        string[len++] = c; // заносим в строку новый символ
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
    int id = fork();
    if (id == -1) {
        perror("Fork error\n");
        return 1;
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe error\n");
        return 2;
    }
    // child process
    if (id == 0) {
        
    
    }
    // parent process
    else {
        char *string = read_string();
        int pointer_value = (long) fopen(string, "r");

    }

    return 0;
}