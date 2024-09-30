#include <stdio.h>

// Function to merge two subarrays while counting inversions
int mergeAndCountInversions(int array[], int leftIndex, int midIndex, int rightIndex) {
    int size = rightIndex - leftIndex + 1; // Size of the merged array
    int temp[size]; // Temporary array for merging
    int tempIndex = 0; // Index for temporary array
    int leftPointer = leftIndex; // Pointer for the left subarray
    int rightPointer = midIndex + 1; // Pointer for the right subarray
    int leftSize = midIndex - leftIndex + 1; // Size of the left subarray
    int inversionCount = 0; // Count of inversions

    // Merge the arrays in sorted order while counting inversions
    while (leftPointer <= midIndex && rightPointer <= rightIndex) {
        if (array[leftPointer] <= array[rightPointer]) {
            temp[tempIndex++] = array[leftPointer++]; // No inversion, add element from left
        } else {
            temp[tempIndex++] = array[rightPointer++]; // Inversion found, add element from right
            inversionCount += (leftSize - (leftPointer - leftIndex)); // Count inversions
        }
    }
    
    // Add remaining elements from the left subarray
    while (leftPointer <= midIndex) {
        temp[tempIndex++] = array[leftPointer++];
    }

    // Add remaining elements from the right subarray
    while (rightPointer <= rightIndex) {
        temp[tempIndex++] = array[rightPointer++];
    }

    // Copy the merged array back to the original array
    for (int i = 0; i < size; i++) {
        array[leftIndex + i] = temp[i];
    }

    return inversionCount; // Return the total count of inversions
}

/**
This function uses a divide and conquer strategy. The array is recursively divided 
into two subarrays. The total inversions are counted during the merging process.
*/
int countInversions(int array[], int leftIndex, int rightIndex) {
    int inversionCount = 0; // Initialize inversion count
    if (leftIndex < rightIndex) {
        int midIndex = (leftIndex + rightIndex) / 2; // Find the midpoint
        inversionCount += countInversions(array, leftIndex, midIndex); // Count inversions in left subarray
        inversionCount += countInversions(array, midIndex + 1, rightIndex); // Count inversions in right subarray
        inversionCount += mergeAndCountInversions(array, leftIndex, midIndex, rightIndex); // Count inversions during merge
    }
    return inversionCount; // Return total inversions counted
}

int main() {
    int size; // Variable to hold the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size); // Input size of the array

    int array[size]; // Declare the array

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]); // Input elements of the array
    }

    // Output the number of inversions found in the array
    printf("Number of inversions: %d\n", countInversions(array, 0, size - 1));

    return 0; 
}
