#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

// int test(void)
// {
//     char *string = read_string();
//     void *source = fopen(string, "r");

//     if (source == NULL) {
//         perror("File open error\n");
//         return 1;
//     }

//     stdin = source;
//     char c = getchar();
//     while (c != EOF) {
//         printf("%c", c);
//         c = getchar();
//     }    

//     return 0;
// }

int main(void)
{
    int number = 1;


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
        close(fd[1]); // close write
        
        int value_from_parent;
        read(fd[0], &value_from_parent, sizeof(int));
        
        printf("got %d from parent\n", value_from_parent);
        
        close(fd[0]);
    }
    // parent process
    else {
        close(fd[0]); // close read
        // char *path_to_file = read_string();
        write(fd[1], &number, sizeof(int));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}