#include <stdio.h>
#include <string.h>

// Function to compute the Longest Common Subsequence (LCS)
int lcs(char v1[], char v2[], int n) {
    int dp[n + 1][n + 1];

    // Build the dp table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (v1[i - 1] == v2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    // Return the length of the LCS
    return dp[n][n];
}

// Function to find the length of the longest palindromic subsequence
int longestPalindromicSubsequence(char v[], int n) {
    // Reverse the array to create v2 (v reversed)
    char reversed_v[n];
    for (int i = 0; i < n; i++) {
        reversed_v[i] = v[n - i - 1];
    }

    // Find the LCS between v and reversed_v
    return lcs(v, reversed_v, n);
}

int main() {
    // Test cases array
    char test_cases[][7] = {
        {'A', 'G', 'T', 'A', 'T', 'G', 'D'},    // Expected LPS length: 5
        {'A', 'B', 'C', 'B', 'A'},              // Expected LPS length: 5
        {'A', 'A', 'A', 'A'},                   // Expected LPS length: 4
        {'B', 'A', 'B', 'B', 'A'},              // Expected LPS length: 5
        {'C', 'A', 'C', 'A', 'C'},              // Expected LPS length: 5
        {'D', 'E', 'F', 'E', 'D'},              // Expected LPS length: 5
        {'M', 'A', 'D', 'A', 'M'},              // Expected LPS length: 5
        {'R', 'A', 'C', 'E', 'C', 'A', 'R'},    // Expected LPS length: 7
        {'N', 'O', 'O', 'N'},                   // Expected LPS length: 4
        {'S', 'E', 'R', 'I', 'A', 'L'},         // Expected LPS length: 1
    };

    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    // Loop through each test case
    for (int i = 0; i < num_test_cases; i++) {
        printf("Test Case %d: ", i + 1);
        
        // Print the test case sequence
        for (int j = 0; test_cases[i][j] != '\0'; j++) {
            printf("%c ", test_cases[i][j]);
        }
        
        printf("\nLongest Palindromic Subsequence Length: ");
        int length = longestPalindromicSubsequence(test_cases[i], strlen(test_cases[i]));
        printf("%d\n", length);
        printf("-----------------------------\n");
    }

    return 0;
}
