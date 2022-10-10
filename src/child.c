#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>

#include "string_utils.h"

int main(void)
{
    float number = 0;
    float sum = 0;
    int fd = STDIN_FILENO;
    char *string;
    while ( (string = read_string(fd)) != NULL )
    {
        char *token;
        while ( (token = strsep(&string, " ")) != NULL )
        {
            number = atof(token);
            sum += number;
        }
    }
    write(STDOUT_FILENO, &sum, sizeof(float));
    close(STDOUT_FILENO);
    return 0;
}
