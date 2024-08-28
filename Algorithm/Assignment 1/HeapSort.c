#include <stdio.h>
#include <time.h>

void heapify(int arr[],int n,int index){
    int t;
    int left=2*index+1;
    int right=2*index+2;

    if(left<n){
        int large=left;
        if(right<n && arr[right]>arr[left])
            large=right;
        if(arr[large]>arr[index]){
            int t=arr[index];
            arr[index]=arr[large];
            arr[large]=t;
            heapify(arr,n,large);
        }
    }


}

void HeapSortFunction(int arr[],int n)
{
    int i,j,t;
    // Build max heap
    for(i=n/2 -1;i>=0;i--)
        heapify(arr,n,i);
    
    for(j=n-1;j>=0;j--){
        t=arr[j];
        arr[j]=arr[0];
        arr[0]=t;
        heapify(arr,j,0);
    }
}

int main()
{
    clock_t starttime, endtime;
    double executiontime;

    int arr[200000];
    int c, n, k = 0;
    int line, number, flag = 0;
    char *inputfile;

    printf("Heap Sort \nSelect File Name \n 1:Sorted Input File \n 2:Sorted Descending Input File \n 3:Random Input File \n");
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
    HeapSortFunction(arr,n);
    endtime = clock();

    FILE *fp2 = fopen("HeapSortoutputfile.txt", "w");
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