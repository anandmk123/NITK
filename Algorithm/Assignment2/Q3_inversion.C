#include<stdio.h>

/*
Use divide and conquer 
Steps:
    Divide: Split the array into two halves.
    Conquer: Recursively count the inversions in each half.
    Combine: Count the inversions that cross the two halves. This can be done while merging the two sorted halves
*/

// Merge two sorted array and find number of inversion while merging
int MergeandCount(int arr[],int low,int mid,int high,int n){ 

    int temp[n];
    int i=low;
    int j=mid+1;
    int k=low;
    int invcount=0;

    while(i<=mid && j<=high){
        if(arr[i]<arr[j]){
            temp[k]=arr[i];
            i++;
            k++;
        }
        else{ //All the remaining element in left sub array is greater than arr[j].==> These are inversions
            temp[k]=arr[j];
            j++;
            k++;
            invcount+=(mid-i+1); // There are mid-i+1 inversions.(Remaining element in left sub array)
        }
    }
    //copy the remaning element of left subarray
    while (i <= mid)
    {
        temp[k] = arr[i];
        k++;
        i++;
    }
    //copy the remaning element of right subarray
    while (j <= high)
    {
        temp[k] = arr[j];
        k++;
        j++;
    }
 // Copy the sorted subarray into the original array
    for (int t = low; t <= high; t++)
        arr[t] = temp[t];

    return invcount;
}

int MergeSortandCountInversion(int arr[],int low,int high,int n){
    int invcount=0;
    if(low<high){
        int mid=(low+high)/2;
        int leftinvcount= MergeSortandCountInversion(arr,low,mid,n); // Find the number of inversions on left sub array
        int rightinvcount= MergeSortandCountInversion(arr,mid+1,high,n); // Find the number of inversions on right sub array
        int mergeinvcount=MergeandCount(arr,low,mid,high,n); // Find the number of inversions while merging left and right suba array
        invcount=leftinvcount + rightinvcount + mergeinvcount; // Sum of all inversions
    }
    return invcount;
}


int main(){

    int n=5,i;
    // printf("Enter the Number of elements in array");
    // scanf("%d",&n);
    // int arr[n];
    int arr[]= {5, 3, 2, 4, 1};
    // printf("Enter the elements \n");
    // for(i=0;i<n;i++)
    //     scanf("%d",&arr[i]);

    int inversioncount= MergeSortandCountInversion(arr,0,n-1,n);

    printf("\n Number of inversion = %d",inversioncount);

    return 0;
}