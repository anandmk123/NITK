#include <stdio.h>
int main()
{
    int i;

    FILE *fp = fopen("Sorted100000.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    fprintf(fp, "%d\n",100000);
    for (i = 100000; i < 200000; i++)
        fprintf(fp, "%d\n", i);

    fclose(fp);

    return 0;
}