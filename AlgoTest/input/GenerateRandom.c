#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int GenerateRandom(int low, int high)
{
    int random_number = rand() % (high - low + 1) + low;
    return random_number;
}

int main()
{
    int i,num;
    srand(time(0));
    FILE *fp = fopen("Random100000check.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    fprintf(fp, "%d\n",100000);
    for (i = 100000; i < 200000; i++)
    {
        num=GenerateRandom(100000,200000);
        fprintf(fp, "%d\n", num);
    }

    fclose(fp);

    return 0;
}