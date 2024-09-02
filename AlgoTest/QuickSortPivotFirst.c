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

    char *Sortedinputfile[] = {"./input/Sorted10000.txt", "./input/Sorted20000.txt", "./input/Sorted30000.txt", "./input/Sorted40000.txt",
                               "./input/Sorted50000.txt", "./input/Sorted60000.txt", "./input/Sorted70000.txt", "./input/Sorted80000.txt", "./input/Sorted90000.txt", "./input/Sorted100000.txt"};
    char *Sortedoutputfile[] = {"./output/Sorted10000.txt", "./output/Sorted20000.txt", "./output/Sorted30000.txt", "./output/Sorted40000.txt",
                                "./output/Sorted50000.txt", "./output/Sorted60000.txt", "./output/Sorted70000.txt", "./output/Sorted80000.txt", "./output/Sorted90000.txt", "./output/Sorted100000.txt"};
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

    FILE *fp3 = fopen("./time/SortedQuickPivotFirstTime", "w");
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

    // Sorted Input in Decending order

    char *Descendinputfile[] = {"./input/Descend10000.txt", "./input/Descend20000.txt", "./input/Descend30000.txt", "./input/Descend40000.txt",
                                "./input/Descend50000.txt", "./input/Descend60000.txt", "./input/Descend70000.txt", "./input/Descend80000.txt", "./input/Descend90000.txt", "./input/Descend100000.txt"};
    char *Descendoutputfile[] = {"./output/Descend10000.txt", "./output/Descend20000.txt", "./output/Descend30000.txt", "./output/Descend40000.txt",
                                 "./output/Descend50000.txt", "./output/Descend60000.txt", "./output/Descend70000.txt", "./output/Descend80000.txt", "./output/Descend90000.txt", "./output/Descend100000.txt"};
    for (int j = 0; j < 10; j++)
    {
        k = 0;
        int flag = 0;
        FILE *fp = fopen(Descendinputfile[j], "r");
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
        FILE *fp2 = fopen(Descendoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        exectime[j] = executiontime;

        printf("Time of %s = %f milli seconds \n", Descendoutputfile[j], executiontime);
    }

    FILE *fp4 = fopen("./time/DescendQuickPivotFirstTime", "w");
    if (fp4 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp4, "%d\t%f\n", n, exectime[j]);
        n += 10000;
    }
    fclose(fp4);

    // Random Input

    char *Randominputfile[] = {"./input/Random10000.txt", "./input/Random20000.txt", "./input/Random30000.txt", "./input/Random40000.txt",
                               "./input/Random50000.txt", "./input/Random60000.txt", "./input/Random70000.txt", "./input/Random80000.txt", "./input/Random90000.txt", "./input/Random100000.txt"};
    char *Randomoutputfile[] = {"./output/Random10000.txt", "./output/Random20000.txt", "./output/Random30000.txt", "./output/Random40000.txt",
                                "./output/Random50000.txt", "./output/Random60000.txt", "./output/Random70000.txt", "./output/Random80000.txt", "./output/Random90000.txt", "./output/Random100000.txt"};
    for (int j = 0; j < 10; j++)
    {
        k = 0;
        int flag = 0;
        FILE *fp = fopen(Randominputfile[j], "r");
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
        FILE *fp2 = fopen(Randomoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        exectime[j] = executiontime;

        printf("Time of %s = %f milli seconds \n", Randomoutputfile[j], executiontime);
    }

    FILE *fp5 = fopen("./time/RandomQuickPivotFirstTime", "w");
    if (fp5 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp5, "%d\t%f\n", n, exectime[j]);
        n += 10000;
    }
    fclose(fp5);

    return 0;
}