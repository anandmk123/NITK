#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to determine if it is possible to make change for amount targetAmount
bool canMakeChangeOnce(int* coinDenominations, int numCoins, int targetAmount) {
    // Create a DP table where dp[i][j] indicates whether it's possible to make change for amount j using the first i coins
    bool dp[numCoins + 1][targetAmount + 1];

    // Initialize the DP table to false
    for (int i = 0; i <= numCoins; i++) {
        for (int j = 0; j <= targetAmount; j++) {
            dp[i][j] = false;
        }
    }

    // Base case: sum of 0 is always possible with 0 coins
    dp[0][0] = true;

    // Iterate over all coins and amounts
    for (int i = 1; i <= numCoins; i++) {
        int currentCoin = coinDenominations[i - 1]; // Coin denomination at position i-1
        
        for (int j = 0; j <= targetAmount; j++) {
            // Exclude the current coin and carry over the previous result
            dp[i][j] = dp[i - 1][j];

            // Include the current coin if the remaining amount (j - currentCoin) is possible
            if (j >= currentCoin && dp[i - 1][j - currentCoin]) {
                dp[i][j] = true;
            }
        }
    }

    // Return whether it's possible to make the exact targetAmount with the available coins
    return dp[numCoins][targetAmount];
}

int main() {
    // Define test cases in the format {{coin denominations}, targetAmount}
    int testCases[][2][6] = {
        {{1, 5, 10, 20}, {16}}, // Expected: Yes (1 + 15)
        {{1, 5, 10, 20}, {31}}, // Expected: Yes (1 + 10 + 20)
        {{1, 5, 10, 20}, {40}}, // Expected: No
        {{2, 4, 6, 8}, {14}},   // Expected: Yes (6 + 8)
        {{2, 4, 6, 8}, {15}},   // Expected: No
        {{5, 10, 15}, {25}},    // Expected: Yes (10 + 15)
        {{5, 10, 15}, {30}},    // Expected: Yes (5 + 10 + 15)
        {{1, 2, 3, 4, 5}, {10}},// Expected: Yes (1 + 2 + 3 + 4)
        {{}, {0}},              // Expected: Yes (sum 0)
        {{}, {5}}               // Expected: No (no coins)
    };

    int numTestCases = sizeof(testCases) / sizeof(testCases[0]); // Calculate number of test cases

    // Loop through each test case and evaluate
    for (int i = 0; i < numTestCases; ++i) {
        int* coinDenominations = testCases[i][0]; // Pointer to current coin denominations array
        int targetAmount = testCases[i][1][0];    // The target amount for which we need to make change
        int numCoins = sizeof(testCases[i][0]) / sizeof(testCases[i][0][0]); // Number of coins in current test case
        
        // Check if it's possible to make the targetAmount using the current coins
        bool result = canMakeChangeOnce(coinDenominations, numCoins, targetAmount);
        
        // Output the result for the current test case
        printf("Test Case %d: \n", i + 1);
        printf("Coins: ");
        for (int j = 0; j < numCoins; j++) {
            printf("%d ", coinDenominations[j]); // Print each coin denomination
        }
        printf("\nAmount: %d\n", targetAmount);
        printf("Can make change using each coin at most once? %s\n", result ? "Yes" : "No");
        printf("-----------------------------\n");
    }

    return 0;
}
