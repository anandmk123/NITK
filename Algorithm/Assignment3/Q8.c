#include <stdio.h>
#include <string.h>

// Function to find the length of the longest common substring
int longestCommonSubstring(const char* X, const char* Y) {
    int n = strlen(X); // Length of string X
    int m = strlen(Y); // Length of string Y
    int max_length = 0; // Variable to store the maximum length of common substring
    
    // Create a 2D array initialized with zeros
    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp)); // Initialize all values to 0

    // Build the dp table using a bottom-up approach
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // If characters match, update the dp value
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                // Update max_length if the current substring is longer
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                }
            } else {
                dp[i][j] = 0; // Reset the value if characters don't match
            }
        }
    }

    return max_length; // Return the length of the longest common substring
}

int main() {
    // Array of test cases: pairs of strings
    const char* test_cases[][2] = {
        {"ABAB", "BABA"},               // Expected: 3 ("ABA" or "BAB")
        {"abcdxyz", "xyzabcd"},         // Expected: 4 ("abcd")
        {"zxabcdezy", "yzabcdezx"},     // Expected: 6 ("abcdez")
        {"abc", "def"},                 // Expected: 0 (No common substring)
        {"abcdef", "abfdef"},           // Expected: 3 ("def")
        {"", "abcdef"},                 // Expected: 0 (Empty string)
        {"abcdef", ""},                 // Expected: 0 (Empty string)
        {"aaa", "aa"},                  // Expected: 2 ("aa")
        {"The quick brown fox", "quick brown"} // Expected: 11 ("quick brown")
    };

    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]); // Number of test cases

    // Iterate through each test case
    for (int i = 0; i < num_test_cases; i++) {
        const char* X = test_cases[i][0]; // First string
        const char* Y = test_cases[i][1]; // Second string
        
        // Find the length of the longest common substring
        int length = longestCommonSubstring(X, Y);
        
        // Print results
        printf("Test Case %d:\n", i + 1);
        printf("String X: \"%s\"\n", X);
        printf("String Y: \"%s\"\n", Y);
        printf("Length of Longest Common Substring: %d\n", length);
        printf("-----------------------------\n");
    }

    return 0; // Exit the program
}
