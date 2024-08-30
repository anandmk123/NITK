#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int findmedian(int arr[], int low, int high)
{

    int middle = (low + high) / 2;
    if ((arr[low] <= arr[middle]) && (arr[middle] <= arr[high]))
        return middle;
    if ((arr[low] <= arr[high]) && (arr[high] <= arr[middle]))
        return high;
    if ((arr[middle] <= arr[low]) && (arr[low] <= arr[high]))
        return low;
    if ((arr[middle] <= arr[high]) && (arr[high] <= arr[low]))
        return high;
    if ((arr[high] <= arr[low]) && (arr[low] <= arr[middle]))
        return low;
    return middle;
}

int GenerateRandom(int low, int high)
{
    srand(time(0));
    int random_number = rand() % (high - low + 1) + low;
    return random_number;
}

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

void QuickSortFunction(int arr[], int low, int high, int p)
{
    if (low < high)
    {
        if (p == 2)
        {
            int random_number = GenerateRandom(low, high);
            swap(&arr[low], &arr[random_number]);
        }
        else if (p == 3)
        {
            int median = findmedian(arr, low, high);
            swap(&arr[low], &arr[median]);
        }
        int index = partition(arr, low, high);
        QuickSortFunction(arr, low, index - 1, p);
        QuickSortFunction(arr, index + 1, high, p);
    }
}

int main()
{
    clock_t starttime, endtime;
    double executiontime;

    int arr[100000];
    int c, n, p, k = 0;
    int line, number, flag = 0;
    char *inputfile;

    printf("Quick Sort \nSelect File Name \n 1:Sorted Input File \n 2:Sorted Descending Input File \n 3:Random Input File \n");
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

    printf("Select Pivot element \n 1:First element \n 2:Random element \n 3:The median of the first, middle, and last elements \n");
    scanf("%d", &p);
    starttime = clock();
    QuickSortFunction(arr, 0, n - 1, p);
    endtime = clock();

    FILE *fp2 = fopen("QuickSortoutputfile.txt", "w");
    if (fp2 == NULL)
    {
        printf("Not able to open the output file");
        return 0;
    }

    for (int i = 0; i < n; i++)
        fprintf(fp2, "%d\n", arr[i]);

    fclose(fp2);

    executiontime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;
    printf("Time = %f seconds \n", executiontime);

    return 0;
}