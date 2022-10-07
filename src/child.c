#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>

#include "string_utils.h"

int main(void)
{
    float first, second, third;
    // float number = 0;
    double sum = 0;

    // int source_fd = open("../test/test.txt", O_RDONLY);
    // char *string = read_string(source_fd);
    // char *pointer;

    // while (string != NULL) {

    //     pointer = strtok(string, " "); //skip only spaces

    //     while(pointer != NULL)
    //      {
    //         printf("%s\n", pointer);
    //               pointer = strtok(NULL, " ");
    //     }
    //     string = read_string(source_fd);
    // }

    while ((scanf("%f %f %f", &first, &second, &third)) > 0) 
    {
        sum += (first + second + third);
    }
    write(STDOUT_FILENO, &sum, sizeof(double));
    close(STDOUT_FILENO);
    return 0;
}
