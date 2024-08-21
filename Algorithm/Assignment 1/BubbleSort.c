#include <stdio.h>
#include <time.h>

int BubbleSortFunction()
{
    int arr[1000000];
    int n, i, j, t, k = 0;
    int line, number, flag = 0;

    FILE *fp = fopen("Sortedinputfile.txt", "r");

    if (fp == NULL)
    {
        printf("Not able to open the input file");
        return 0;
    }
    while (1)
    {
        line = fscanf(fp, "%d", &number);
        if (line == EOF)
            break;
        else
        {
            if (flag == 0)
            {
                n = number;
                flag = 1;
            }
            else
            {
                arr[k] = number;
                k++;
            }
        }
    }

    fclose(fp);

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



    FILE *fp2 = fopen("Sortedoutputfile.txt", "w");
    if (fp2 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }

    for (i = 0; i < 10; i++)
        fprintf(fp2, "%d\n",arr[i]);

    fclose(fp);

    // for (i = 0; i < n; i++)
    // {
    //     printf("%d \t", arr[i]);
    // }
    return 0;
}

int main()
{
    clock_t starttime, endtime;
    starttime = clock();
    double executiontime;

    BubbleSortFunction();

    endtime = clock();
    executiontime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;

    printf("Time = %f seconds", executiontime);

    return 0;
}