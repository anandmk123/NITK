#include <stdio.h>
int main()
{
    int i;

    FILE *fp = fopen("SortedDescendinputfile.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    fprintf(fp, "%d\n",10);
    for (i = 10; i > 0; i--)
        fprintf(fp, "%d\n", i);

    fclose(fp);

    return 0;
}