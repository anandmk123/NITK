#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int min = 5, max = 28;
    int random_number = rand() % (max - min + 1) + min;

    printf("%d ", random_number);
    return 0;
}