#include <stdio.h>
#include <time.h>

int BubbleSortFunction(int arr[], int n)
{
    int i,j,t;
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
    return 0;
}

int main()
{
    clock_t starttime, endtime;
    double executiontime;

    int arr[100000];
    int n,i,c,k = 0;
    int line, number, flag = 0;
    char *inputfile;

    printf("Bubble Sort \n Select File Name \n 1:Sorted Input File \n 2:Sorted Descending Input File \n 3:Random Input File \n");
    scanf("%d", &c);

    switch (c)
    {
    case 1:
        inputfile = "Sortedinputfile.txt";
        break;
    case 2:
        inputfile = "SortedDescendinputfile.txt";
        break;
    case 3:
        inputfile = "Randominputfile.txt";
        break;
    default:
        printf("Invalid input file");
    }

    FILE *fp = fopen(inputfile, "r");

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
    starttime = clock();
    BubbleSortFunction(arr, n);
    endtime = clock();

    FILE *fp2 = fopen("BubbleSortoutputfile.txt", "w");
    if (fp2 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }

    for (i = 0; i < n; i++)
        fprintf(fp2, "%d\n", arr[i]);

    fclose(fp2);

    executiontime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;

    printf("Time = %f seconds", executiontime);

    return 0;
}