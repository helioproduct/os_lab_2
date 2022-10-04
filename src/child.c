#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    // TODO: one float number
    float first, second, third;
    double sum = 0;

    // TODO: low lewel function intstead scanf
    while ((scanf("%f %f %f", &first, &second, &third)) > 0) 
    {
        sum += (first + second + third);
    }
    write(STDOUT_FILENO, &sum, sizeof(double));
    close(STDOUT_FILENO);
    return 0;
}
