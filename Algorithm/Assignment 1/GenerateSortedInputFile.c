#include <stdio.h>
int main()
{
    int i;

    FILE *fp = fopen("Sortedinputfile.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    fprintf(fp, "%d\n",1000000);
    for (i = 0; i < 1000000; i++)
        fprintf(fp, "%d\n", i + 1);

    fclose(fp);

    return 0;
}