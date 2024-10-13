#include <stdio.h>
#include <stdlib.h>

// Function to merge two halves of the array while counting the number of
// elements smaller than the current element on its right.
// Time complexity: O(n)
void countAndMerge(int array[], int output[], int index[], int low, int mid, int high) {
    int n = high - low + 1;      // Total number of elements in the current segment
    int buffer[n];               // Temporary array to hold sorted elements
    int bufferCount = 0;         // Counter for the buffer
    int left = low;              // Left pointer for the left subarray
    int right = mid + 1;         // Right pointer for the right subarray

    // Merging process
    while (left <= mid && right <= high) {
        if (array[left] > array[right]) {
            // If the left element is greater, it means all elements
            // from right pointer to high are smaller than the left element.
            output[index[array[left]]] += ((high - right) + 1);
            buffer[bufferCount++] = array[left++]; // Add left element to buffer
        } else {
            buffer[bufferCount++] = array[right++]; // Add right element to buffer
        }
    }

    // Copy any remaining elements from the left subarray to the buffer
    while (left <= mid) {
        buffer[bufferCount++] = array[left++];
    }

    // Copy any remaining elements from the right subarray to the buffer
    while (right <= high) {
        buffer[bufferCount++] = array[right++];
    }

    // Copy the sorted buffer back to the original array
    for (int i = 0; i < n; i++) {
        array[low + i] = buffer[i];
    }
}

// Function to implement the modified merge sort algorithm.
// It recursively divides the array into two halves and merges them,
// counting the number of smaller elements on the right side.
// Time complexity: O(n log n)
void countSmallestElementsInRight(int array[], int output[], int index[], int low, int high) {
    if (high > low) {
        int mid = (low + high) / 2; // Calculate the midpoint
        // Recursively sort and count for the left half
        countSmallestElementsInRight(array, output, index, low, mid);
        // Recursively sort and count for the right half
        countSmallestElementsInRight(array, output, index, mid + 1, high);
        // Merge the two halves and count smaller elements
        countAndMerge(array, output, index, low, mid, high);
    }
}

int main() {
    int size; // Variable to hold the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Dynamically allocate memory for the array and output result
    int *array = (int *)malloc(size * sizeof(int));
    int *output = (int *)malloc(size * sizeof(int));
    int index[100]; // Array to store the original index of each element, assuming elements are <= 100

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);      // Read each element into the array
        output[i] = 0;               // Initialize output counts to zero
        index[array[i]] = i;         // Store the original index of the elements
    }

    // Call the function to count smallest elements on the right
    countSmallestElementsInRight(array, output, index, 0, size - 1);

    // Print the output counts
    printf("Smallest elements in right are: ");
    for (int i = 0; i < size; i++) {
        printf("%d, ", output[i]);   // Display the counts for each element
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d, ", array[i]);   // Display the counts for each element
    }
    printf("\n");

    // Free dynamically allocated memory
    free(array);
    free(output);
    return 0;
}
