#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>

#include "string_utils.h"

int main(void)
{
    double number = 0;
    double sum = 0;
    char *string = read_string(STDIN_FILENO);

    while (string != NULL) {
        char *token;
        while ( (token = strsep(&string, " ")) != NULL) {
            number = atof(token);
            sum += number;
        }
        string = read_string(STDIN_FILENO);
    }

    write(STDOUT_FILENO, &sum, sizeof(double));
    close(STDOUT_FILENO);
    return 0;
}
