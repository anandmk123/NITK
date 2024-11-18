#include <stdio.h>

// Define a structure to hold the result of the subsequence with the maximum sum
typedef struct {
    int startIndex;   // Starting index of the subsequence
    int endIndex;     // Ending index of the subsequence
    int maxSum;       // Maximum sum of the subsequence
} Subsequence;

// Function to find the contiguous subsequence with maximum sum
Subsequence findMaxSumSubsequence(int array[], int size) {
    Subsequence maxSubseq;  // To store the result (maximum subsequence)
    
    // Variables to track the sum of the current subarray and the maximum sum so far
    int currentSubarraySum = 0;
    int maxSumSoFar = 0;
    
    // Index for the potential start of a new subarray when the sum goes negative
    int potentialStartIndex = 0;
    
    // Initialize the result structure with default values
    maxSubseq.startIndex = 0;
    maxSubseq.endIndex = -1; // Indicates an empty subsequence (no result yet)
    maxSubseq.maxSum = 0;

    // Iterate through the entire array to find the maximum sum subsequence
    for (int currentIndex = 0; currentIndex < size; currentIndex++) {
        
        // Add the current element to the sum of the current subarray
        currentSubarraySum += array[currentIndex];

        // If the sum becomes negative, reset it and consider starting a new subarray
        if (currentSubarraySum < 0) {
            currentSubarraySum = 0;
            potentialStartIndex = currentIndex + 1;  // Next element will be the start of the new subarray
        }
        // If we found a new maximum sum, update the result structure
        else if (maxSumSoFar < currentSubarraySum) {
            maxSumSoFar = currentSubarraySum;  // Update the maximum sum found so far
            maxSubseq.startIndex = potentialStartIndex;  // Update the start index of the subsequence
            maxSubseq.endIndex = currentIndex;  // Update the end index of the subsequence
            maxSubseq.maxSum = maxSumSoFar;  // Update the maximum sum
        }
    }

    return maxSubseq;  // Return the result containing the maximum sum subsequence
}

int main() {
    // Sample input data: an array of integers
    int sequence[] = {5, 15, -30, 10, -5, 40, 10};
    int size = sizeof(sequence) / sizeof(sequence[0]);  // Calculate the size of the array

    // Call the function to find the subsequence with the maximum sum
    Subsequence maxSubsequenceResult = findMaxSumSubsequence(sequence, size);

    // Output the input sequence
    printf("Input Sequence: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    // If no subsequence was found (empty subsequence), print a message
    if (maxSubsequenceResult.endIndex == -1) {
        printf("The maximum sum is 0 (empty subsequence).\n");
    }
    // Otherwise, print the maximum sum and the corresponding subsequence
    else {
        printf("Maximum Sum: %d\n", maxSubsequenceResult.maxSum);
        printf("Subsequence: ");
        for (int i = maxSubsequenceResult.startIndex; i <= maxSubsequenceResult.endIndex; ++i) {
            printf("%d ", sequence[i]);  // Print the subsequence
        }
        printf("\n");
    }

    return 0;  // End of program
}
