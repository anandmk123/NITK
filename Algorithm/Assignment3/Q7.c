#include <stdio.h>
#include <string.h>

// Function to compute the Longest Common Subsequence (LCS)
int lcs(char v1[], char v2[], int n) {
    int dp[n + 1][n + 1]; // DP table to store lengths of LCS for substrings

    // Build the dp table using a bottom-up dynamic programming approach
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // Base case: LCS of empty string is 0
            } else if (v1[i - 1] == v2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Characters match
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1]; // Take max of excluding one character
            }
        }
    }

    // Return the length of the LCS for the full strings
    return dp[n][n];
}

// Function to find the length of the longest palindromic subsequence
int longestPalindromicSubsequence(char v[], int n) {
    // Reverse the array to create a comparison string (v2)
    char reversed_v[n];
    for (int i = 0; i < n; i++) {
        reversed_v[i] = v[n - i - 1]; // Reverse the original string
    }

    // Find the LCS between the original string and its reverse
    return lcs(v, reversed_v, n);
}

int main() {
    // Array of test cases: strings to find the longest palindromic subsequence
    char *test_cases[] = {
        "AGTATGD",   // Expected LPS length: 5
        "ABCBA",     // Expected LPS length: 5
        "AAAA",      // Expected LPS length: 4
        "BABBA",     // Expected LPS length: 5
        "CACAC",     // Expected LPS length: 5
        "DEFED",     // Expected LPS length: 5
        "MADAM",     // Expected LPS length: 5
        "RACECAR",   // Expected LPS length: 7
        "NOON",      // Expected LPS length: 4
        "SERIAL"     // Expected LPS length: 1
    };

    // Calculate the number of test cases
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    // Loop through each test case
    for (int i = 0; i < num_test_cases; i++) {
        printf("Test Case %d: %s\n", i + 1, test_cases[i]); // Print the test case string

        // Calculate the length of the longest palindromic subsequence
        printf("Longest Palindromic Subsequence Length: ");
        int length = longestPalindromicSubsequence(test_cases[i], strlen(test_cases[i]));
        printf("%d\n", length); // Print the result

        printf("-----------------------------\n"); // Separator for better readability
    }

    return 0;
}
