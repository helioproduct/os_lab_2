#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    float first, second, third;
    double sum = 0;
    while ((scanf("%f %f %f", &first, &second, &third)) > 0) 
    {
        sum += (first + second + third);
    }
    write(STDOUT_FILENO, &sum, sizeof(double));
    return 0;
}
