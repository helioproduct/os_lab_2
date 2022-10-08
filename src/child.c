#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>

#include "string_utils.h"

int main(void)
{
    float number = 0;
    double sum = 0;
    int fd = STDIN_FILENO;
    char *string;
    while ( (string = read_string(fd)) != NULL )
    {
        printf("%s", string);
        char *token;
        while ( (token = strsep(&string, " ")) != NULL )
        {
            number = atof(token);
            sum += number;
        }
    }
    write(STDOUT_FILENO, &sum, sizeof(double));
    close(STDOUT_FILENO);
    return 0;
}
