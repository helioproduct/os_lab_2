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

        FILE *source = fopen(path_to_file, "r");
        stdin = source;

        int read;
        float first, second, third;
        double sum = 0;
        
        while ((read = scanf("%f %f %f", &first, &second, &third)) > 0) {
            sum += first;
            sum += second;
            sum += third;
        }

        write(fd[1], &sum, sizeof(sum));
        fclose(stdin);
        close(fd[1]);
    }   
    else {
        close(fd[1]);
        double sum;
        read(fd[0], &sum, sizeof(sum));
        printf("[%d] Total sum = %lf\n", getpid(), sum);
        wait(NULL);
    }

    return 0;
}
