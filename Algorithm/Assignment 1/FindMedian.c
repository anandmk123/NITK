#include<stdio.h>

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

int main(){

    int arr[]={25,12,4,133,2,7,28,3,3,9,0,31,23};
    printf("%d",findmedian(arr,0,12));
    return 0;
}