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

    fprintf(fp, "%d\n",20000);
    for (i = 200000; i > 180000; i--)
        fprintf(fp, "%d\n", i);

    fclose(fp);
    

    return 0;
}