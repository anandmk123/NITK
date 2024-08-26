#include <stdio.h>
#include <time.h>

void CountSort(int arr[], int n, int pos)
{

    int count[10] = {0};
    int output[n], i;

    for (i = 0; i < n; i++)
        count[(arr[i] / pos) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] = count[i] + count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / pos) % 10] - 1] = arr[i];
        count[(arr[i] / pos) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void RadixSortFunction(int arr[], int n)
{

    int i, j;

    int maximum = arr[0];
    for (i = 1; i < n; i++)
    {
        if (arr[i] > maximum)
            maximum = arr[i];
    }

    for (int pos = 1; maximum / pos > 0; pos *= 10)
        CountSort(arr, n, pos);
}

int main()
{
    clock_t starttime, endtime;
    starttime = clock();
    double executiontime;

    int arr[200000];
    int c, n, k = 0;
    int line, number, flag = 0;
    char *inputfile;

    printf("Radix Sort \nSelect File Name \n 1:Sorted Input File \n 2:Sorted Descending Input File \n 3:Random Input File \n");
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

    RadixSortFunction(arr, n);

    FILE *fp2 = fopen("RadixSortoutputfile.txt", "w");
    if (fp2 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }

    for (int i = 0; i < n; i++)
        fprintf(fp2, "%d\n", arr[i]);

    fclose(fp2);

    endtime = clock();
    executiontime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;
    printf("Time = %f seconds \n", executiontime);

    return 0;
}