#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count=0;

int *merge(int *input1,int *input2,int low,int mid,int high)
{
    int size = high - low + 1;
    int *output = (int*)malloc(size * sizeof(int));
     int i=0,j=0,k=0;
     while(i<(mid-low+1) && j<(high-mid))
     {
        if(input2[j]<input1[i])
        {
        output[k]=input2[j];
        count=count+(mid-low-i+1);
        j++;
        k++;
        }
        else{
            output[k]=input1[i];
            i++;
            k++;
        }
     }
     while(i<(mid-low+1))
     {
        output[k]=input1[i];
        k++;
        i++;
     }
     while(j<(high-mid))
     {
        output[k]=input2[j];
        k++;
        j++;
     }
     return output;
}

int *count_inversions(int *arr,int low,int high)
{
    if((high-low+1)==1)
    {
        int *arr1 = (int*)malloc(sizeof(int));
        arr1[0]=arr[low];
        return arr1;
    }
    else if((high-low+1)==2)
    {
        int *arr1 = (int*)malloc(2 * sizeof(int));
        if(arr[low]>arr[high])
        {
            arr1[0]=arr[high];
            arr1[1]=arr[low];
            count+=1;
        }
        else{
            arr1[0]=arr[low];
            arr1[1]=arr[high];
        }
        return arr1;
    }
    else{
        int mid=(high+low)/2;
        printf("%d",mid);
        int *arr1=count_inversions(arr,low,mid);
        int *arr2=count_inversions(arr,mid+1,high);
        int *arr3=merge(arr1,arr2,low,mid,high);
        return arr3;
    }
}
void main()
{
    int n;
    printf("ENTER LENGTH OF THE ARRAY\n");
    scanf("%d",&n);
    int arr[n];
    printf("ENTER THE ELEMENTS\n");
    for(int i=0;i<n;i++)
    {
       scanf("%d",&arr[i]);
    }
    count_inversions(arr,0,n-1);
    printf("NUMBER OF INVERSIONS : %d",count);
}