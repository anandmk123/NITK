#include <stdio.h>
#include <stdlib.h>

void printLIS(int arr[], int prev[], int i) {
    if (i < 0)
        return;
    printLIS(arr, prev, prev[i]);
    printf("%d ", arr[i]);
}

void longestIncreasingSubsequence(int arr[], int n) {
    int *dp = (int *)malloc(n * sizeof(int));  // dp[i] stores the length of LIS ending at arr[i]
    int *prev = (int *)malloc(n * sizeof(int)); // prev[i] stores the previous index in the LIS
    int max_len = 0, last_index = -1;

    // Initialize the dp array and prev array
    for (int i = 0; i < n; i++) {
        dp[i] = 1;        // The minimum length of LIS ending at arr[i] is 1 (the element itself)
        prev[i] = -1;     // No previous element in the subsequence
    }

    // Build the dp and prev arrays
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }

    // Find the index of the maximum length of LIS
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
            last_index = i;
        }
    }

    // Print the length of the LIS
    printf("Length of LIS: %d\n", max_len);
    
    // Print the Longest Increasing Subsequence
    printf("Longest Increasing Subsequence: ");
    printLIS(arr, prev, last_index);
    printf("\n");

    // Free allocated memory
    free(dp);
    free(prev);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    longestIncreasingSubsequence(arr, n);

    return 0;
}