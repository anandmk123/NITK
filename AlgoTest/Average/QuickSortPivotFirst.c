#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivotvalue = arr[low];
    int i = high;
    for (int j = high; j > low; j--)
    {
        if (arr[j] > pivotvalue)
        {
            swap(&arr[i], &arr[j]);
            i = i - 1;
        }
    }
    swap(&arr[low], &arr[i]);
    return i;
}

void QuickSortFunction(int arr[], int low, int high)
{
    if (low < high)
    {
        int index = partition(arr, low, high);
        QuickSortFunction(arr, low, index - 1);
        QuickSortFunction(arr, index + 1, high);
    }
}

int main()
{
    double executiontime;
    double exectime[10];

    int arr[100000];
    int n, i, c, k;
    int line, number;

    // Sorted Input

    char *Sortedinputfile[] = {"./input/Shuffle10000.txt", "./input/Shuffle20000.txt", "./input/Shuffle30000.txt", "./input/Shuffle40000.txt",
                               "./input/Shuffle50000.txt", "./input/Shuffle60000.txt", "./input/Shuffle70000.txt", "./input/Shuffle80000.txt", "./input/Shuffle90000.txt", "./input/Shuffle100000.txt"};
    char *Sortedoutputfile[] = {"./output/Shuffle10000.txt", "./output/Shuffle20000.txt", "./output/Shuffle30000.txt", "./output/Shuffle40000.txt",
                                "./output/Shuffle50000.txt", "./output/Shuffle60000.txt", "./output/Shuffle70000.txt", "./output/Shuffle80000.txt", "./output/Shuffle90000.txt", "./output/Shuffle100000.txt"};
    for (int j = 0; j < 10; j++)
    {
        k = 0;
        int flag = 0;
        FILE *fp = fopen(Sortedinputfile[j], "r");
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
        struct timeval tv1, tv2;
        gettimeofday(&tv1, NULL);
        QuickSortFunction(arr, 0, n - 1);
        gettimeofday(&tv2, NULL);

        executiontime = (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
                        (double)(tv2.tv_sec - tv1.tv_sec);
        executiontime = executiontime * 1000;
        FILE *fp2 = fopen(Sortedoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        exectime[j] = executiontime;

        printf("Time of %s = %f milli seconds \n", Sortedoutputfile[j], executiontime);
    }

    FILE *fp3 = fopen("./time/ShuffleQuickPivotFirstTime", "w");
    if (fp3 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp3, "%d\t%f\n", n, exectime[j]);
        n += 10000;
    }
    fclose(fp3);

    return 0;

}
 