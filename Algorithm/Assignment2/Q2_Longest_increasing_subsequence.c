#include <stdio.h>
#include <stdlib.h>

/**
 * This function finds the Longest Increasing Subsequence (LIS) using dynamic programming.
 * It calculates the length of LIS for each element by considering all previous elements and 
 * determining if the current element can extend the sequence. The sequence is then reconstructed.
 * Time complexity: O(n^2)
 * 
 **/
int* longestIncreasingSubsequence(int arr[], int size, int* resultSize)
{
    // dp[i] stores the length of the longest increasing subsequence ending at index i.
    // predecessor[i] stores the index of the previous element in the sequence for reconstruction.
    int* dp = (int*)malloc(size * sizeof(int));
    int* predecessor = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        dp[i] = 1;            // Initialize LIS length for each element as 1 (itself)
        predecessor[i] = -1;   // Initialize no predecessor for each element
    }

    // Compute LIS for each element by comparing it with previous elements.
    // If arr[i] > arr[j], update dp[i] and track the predecessor.
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                predecessor[i] = j; // Update the predecessor of element at i
            }
        }
    }

    // Find the maximum value in dp[] which represents the length of the LIS.
    int maxLength = -1, lastPos = -1;
    for (int i = 0; i < size; i++)
    {
        if (maxLength < dp[i])
        {
            maxLength = dp[i];
            lastPos = i;  // Track the index of the last element in the LIS
        }
    }

    printf("Length of LIS: %d\n", maxLength);

    // Reconstruct the LIS by following the predecessor array.
    int* subsequence = (int*)malloc(maxLength * sizeof(int));
    int index = maxLength - 1;
    while (lastPos != -1)
    {
        subsequence[index--] = arr[lastPos];
        lastPos = predecessor[lastPos];
    }

    *resultSize = maxLength;  // Update the size of the resulting LIS
    
    // Free dynamically allocated memory
    free(dp);
    free(predecessor);

    return subsequence;
}

int main()
{
    int n;
    printf("Enter size of the array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int resultSize;
    int* result = longestIncreasingSubsequence(arr, n, &resultSize);

    printf("Longest Increasing Subsequence: ");
    for (int i = 0; i < resultSize; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(arr);
    free(result);

    return 0;
}
