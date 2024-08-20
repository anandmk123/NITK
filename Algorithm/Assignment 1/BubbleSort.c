#include <stdio.h>
int main()
{
    int arr[100];
    int n, i, j, t, k = 0;
    int line, number,flag=0;

    FILE *fp = fopen("Sortedfile.txt", "r");

    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }
    while (1)
    {
        line = fscanf(fp, "%d", &number);
        if (line == EOF)
            break;
        else
        {
            if(flag==0){
                n=number;
                flag=1;
            }
            else{
                arr[k]=number;
                k++;
            }
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        printf("%d \t", arr[i]);
    }

    return 0;
}