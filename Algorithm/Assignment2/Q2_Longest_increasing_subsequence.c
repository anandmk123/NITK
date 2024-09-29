#include <stdio.h>

// Function to print the LIS
void printSub(int arr[], int n, int dp[], int maxLengthIndex) {
    int lis[maxLengthIndex + 1];
    int length = dp[maxLengthIndex];
    
    // Reconstruct the LIS by backtracking through dp[]
    for (int i = maxLengthIndex; i >= 0; i--) {
        if (dp[i] == length) {
            lis[length - 1] = arr[i];
            length--;
        }
    }
    
    // Print the LIS
    printf("Longest Increasing Subsequence: ");
    for (int i = 0; i < dp[maxLengthIndex]; i++) {
        printf("%d ", lis[i]);
    }
    printf("\n");
}

// Function to find the length of LIS and the subsequence
void longestSub(int arr[], int n) {
    int dp[n];        // Array to store the length of LIS ending at each index
    int maxLength = 1; // Length of the longest subsequence found
    int maxLengthIndex = 0; // Index of the last element of the longest subsequence
    
    // Initialize all dp[] values to 1 because every element is an increasing subsequence of length 1
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    // Build the dp[] array
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
        
        // Track the maximum length and the index of the last element of the LIS
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxLengthIndex = i;
        }
    }
    
    // Print the length of the LIS
    printf("Length of LIS: %d\n", maxLength);
    
    // Reconstruct and print the actual LIS
    printSub(arr, n, dp, maxLengthIndex);
}

int main() {
    int arr[] = {50, 3, 10, 7, 40, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    longestSub(arr, n);
    
    return 0;
}
