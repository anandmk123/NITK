#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void merge(int arr[], int l, int m, int r, long long *comparisonCount);
void mergeSort(int arr[], int l, int r, long long *comparisonCount);

void merge(int arr[], int l, int m, int r, long long *comparisonCount)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Check memory allocation
    if (L == NULL || R == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        (*comparisonCount)++; // Increment comparison counter
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        arr[k++] = R[j++];
    }

    // Free the allocated memory
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r, long long *comparisonCount)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, comparisonCount);
        mergeSort(arr, m + 1, r, comparisonCount);

        // Merge the sorted halves
        merge(arr, l, m, r, comparisonCount);
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

        mergeSort(arr, 0, n - 1, &comparisonCount);

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

    FILE *fp3 = fopen("./comparison/SortedMergecomparison", "w");
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
        mergeSort(arr, 0, n - 1, &comparisonCount);

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

    FILE *fp4 = fopen("./comparison/DescendMergecomparison", "w");
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
        mergeSort(arr, 0, n - 1, &comparisonCount);

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

    FILE *fp5 = fopen("./comparison/RandomMergecomparison", "w");
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