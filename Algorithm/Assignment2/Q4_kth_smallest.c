#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototypes
int quickSelect(int array[], int k, int low, int high);
int findMedianIndex(int array[], int a, int b);
void swap(int *a, int *b);
int partition(int array[], int pivot, int low, int high);
int partitionByMedian(int array[], int low, int high);
void quickSort(int *array, int low, int high);
int medianOfMedians(int array[], int low, int high);

// Find the median of three indices for better pivot selection
int findMedianIndex(int array[], int a, int b) {
    int mid = (a + b) / 2;
    // Check the conditions to find the median of array[a], array[mid], array[b]
    if ((array[a] < array[mid] && array[mid] < array[b]) || (array[b] < array[mid] && array[mid] < array[a])) {
        return mid; // Median is at mid index
    }
    if ((array[mid] < array[a] && array[a] < array[b]) || (array[b] < array[a] && array[a] < array[mid])) {
        return a; // Median is at a index
    }
    if ((array[mid] < array[b] && array[b] < array[a]) || (array[a] < array[b] && array[b] < array[mid])) {
        return b; // Median is at b index
    }
    return mid; // Default to mid index
}

// Swap function to exchange two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array based on the pivot value
// Elements smaller than the pivot go to the left, and elements greater go to the right
int partition(int array[], int pivot, int low, int high) {
    int i = low, j = low, k = high;
    while (j <= k) {
        if (array[j] < pivot) {
            swap(&array[i], &array[j]); // Move smaller elements to the left
            i++;
            j++;
        } else if (array[j] > pivot) {
            swap(&array[k], &array[j]); // Move larger elements to the right
            k--;
        } else {
            j++; // Move past elements equal to the pivot
        }
    }
    return i; // Return index where partition occurred
}

// Partition the array by finding the median and using it as the pivot
int partitionByMedian(int array[], int low, int high) {
    int idx = findMedianIndex(array, low, high); // Find median of the array for better pivot selection
    swap(&array[low], &array[idx]); // Move the median element to the start
    return partition(array, array[idx], low, high); // Partition the array around this median pivot
}

// Standard quicksort algorithm using partition by median of three elements
void quickSort(int *array, int low, int high) {
    if (low < high) {
        int p = partitionByMedian(array, low, high); // Partition the array and find the pivot index
        quickSort(array, low, p - 1); // Recursively sort the left part
        quickSort(array, p + 1, high); // Recursively sort the right part
    }
}

// Find the median of medians from groups of five elements for better pivot selection in quickselect
int medianOfMedians(int array[], int low, int high) {
    int n = high - low + 1; // Total number of elements
    int groupCount = ceil((float)n / 5); // Calculate the number of groups (each group has up to 5 elements)
    int medianArray[groupCount]; // Array to store medians of each group

    // Divide the array into groups of 5 and find the median of each group
    for (int i = 0; i < n / 5; i++) {
        int start = low + (i * 5);
        int end = start + 4;
        int mid = (start + end) / 2;
        quickSort(array, start, end); // Sort each group of 5 elements
        medianArray[i] = array[mid]; // Store the median of the group
    }

    // Handle remaining elements (less than 5 elements)
    int remaining = n % 5;
    if (remaining != 0) {
        int start = low + (n - remaining);
        int end = high;
        int mid = (start + end) / 2;
        quickSort(array, start, end); // Sort the remaining elements
        medianArray[groupCount - 1] = array[mid]; // Store the median of the last small group
    }

    // If the number of groups is small, sort and return the median directly
    if (groupCount <= 5) {
        quickSort(medianArray, 0, groupCount - 1);
        return medianArray[groupCount / 2]; // Return the median of the medians
    } else {
        // Recursively find the median of the medians array
        return quickSelect(medianArray, groupCount / 2, 0, groupCount - 1);
    }
}

// Quickselect algorithm to find the kth smallest element in the array
// Uses divide and conquer, based on the median of medians strategy for optimal pivot selection
int quickSelect(int array[], int k, int low, int high) {
    int n = high - low + 1; // Number of elements in the current range

    // Find the median of medians to use as the pivot
    int pivot = medianOfMedians(array, low, high);

    // Partition the array using the median of medians as the pivot
    int mid = partition(array, pivot, low, high);

    // Size of the left subarray
    int leftSize = mid - low;

    // Recursively find the kth element
    if (k < leftSize + 1) {
        return quickSelect(array, k, low, mid - 1); // Search in the left partition
    } else if (k > leftSize + 1) {
        return quickSelect(array, k - (leftSize + 1), mid + 1, high); // Search in the right partition
    } else {
        return pivot; // If the pivot is the kth smallest element
    }
}

int main() {
    int n, k;
    printf("Enter the size of the array: ");
    scanf("%d", &n); // Read the size of the array

    // Dynamically allocate memory for the array
    int *array = (int *)malloc(n * sizeof(int));

    // Read the elements of the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    // Read the value of k (the position of the desired element)
    printf("Enter k: ");
    scanf("%d", &k);

    // Call quickSelect to find the kth smallest element
    printf("The %dth smallest element in the array is %d\n", k, quickSelect(array, k, 0, n - 1));

    // Free the allocated memory for the array
    free(array);
    return 0;
}
