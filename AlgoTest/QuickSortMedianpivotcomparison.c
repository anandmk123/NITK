#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high, long long *comparisonCount);
void quickSort(int arr[], int low, int high, long long *comparisonCount);
int medianOfThree(int arr[], int low, int high);

int partition(int arr[], int low, int high, long long *comparisonCount) {
    int pivotIndex = medianOfThree(arr, low, high); // Choose pivot as median of first, middle, last
    int pivot = arr[pivotIndex];
    int temp;

    // Swap pivot with the last element
    temp = arr[pivotIndex];
    arr[pivotIndex] = arr[high];
    arr[high] = temp;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparisonCount)++; // Increment comparison counter
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i + 1] and arr[high]
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high, long long *comparisonCount) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisonCount);
        quickSort(arr, low, pi - 1, comparisonCount);
        quickSort(arr, pi + 1, high, comparisonCount);
    }
}

int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) {
        if (arr[mid] > arr[high])
            return mid;
        else if (arr[low] > arr[high])
            return high;
        else
            return low;
    } else {
        if (arr[low] > arr[high])
            return low;
        else if (arr[mid] > arr[high])
            return high;
        else
            return mid;
    }
}

int main()
{
    long long comparison[10];
    //%lld
    long long comparisonCount = 0;

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
        comparisonCount = 0;
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

    quickSort(arr, 0, n - 1, &comparisonCount);

        FILE *fp2 = fopen(Sortedoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        comparison[j] = comparisonCount;

        printf("Comparison %s = %lld  \n", Sortedoutputfile[j], comparisonCount);
    }

    FILE *fp3 = fopen("./comparison/SortedQuickMedianPivotcomparison", "w");
    if (fp3 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp3, "%d\t%lld\n", n, comparison[j]);
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
        comparisonCount = 0;
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
    quickSort(arr, 0, n - 1, &comparisonCount);

        FILE *fp2 = fopen(Descendoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        comparison[j] = comparisonCount;

        printf("comparison of %s = %lld \n", Descendoutputfile[j], comparisonCount);
    }

    FILE *fp4 = fopen("./comparison/DescendQuickMedianPivotcomparison", "w");
    if (fp4 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp4, "%d\t%lld\n", n, comparison[j]);
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
        comparisonCount = 0;
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
    quickSort(arr, 0, n - 1, &comparisonCount);

        FILE *fp2 = fopen(Randomoutputfile[j], "w");
        if (fp2 == NULL)
        {
            printf("Not able to open the output file");
            return 0;
        }

        for (i = 0; i < n; i++)
            fprintf(fp2, "%d\n", arr[i]);

        fclose(fp2);
        comparison[j] = comparisonCount;
        printf("comparison of %s = %lld \n", Randomoutputfile[j], comparisonCount);
    }

    FILE *fp5 = fopen("./comparison/RandomQuickMedianPivotcomparison", "w");
    if (fp5 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }
    n = 10000;
    for (int j = 0; j < 10; j++)
    {
        fprintf(fp5, "%d\t%lld\n", n, comparison[j]);
        n += 10000;
    }
    fclose(fp5);

    return 0;
}