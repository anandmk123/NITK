#include <stdio.h>
#include <time.h>

void Merge(int arr[], int low, int mid, int high, int size)
{
    int temp[size], i, j, k, t;
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        temp[k] = arr[j];
        k++;
        j++;
    }
    for (t = low; t <= high; t++)
        arr[t] = temp[t];
}

void MergeSortFunction(int arr[], int low, int high, int size)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        MergeSortFunction(arr, low, mid, size);
        MergeSortFunction(arr, mid + 1, high, size);
        Merge(arr, low, mid, high, size);
    }
}

int main()
{
    clock_t starttime, endtime;
    double executiontime;

    int arr[20000];
    int c, n, k = 0;
    int line, number, flag = 0;
    char *inputfile;

    printf("Merge Sort \nSelect File Name \n 1:Sorted Input File \n 2:Sorted Descending Input File \n 3:Random Input File \n");
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
    MergeSortFunction(arr, 0, n - 1, n);
    endtime = clock();

    FILE *fp2 = fopen("MergeSortoutputfile.txt", "w");
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