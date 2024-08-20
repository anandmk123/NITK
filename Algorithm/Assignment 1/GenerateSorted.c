#include <stdio.h>
int main()
{
    int i;

    FILE *fp = fopen("Sortedfile.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    fprintf(fp, "%d\n",10);
    for (i = 0; i < 10; i++)
        fprintf(fp, "%d\n", i + 1);

    fclose(fp);

    return 0;
}