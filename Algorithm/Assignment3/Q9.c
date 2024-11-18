#include <stdio.h>
#include <stdbool.h>

// Function to determine if it is possible to form the target sum
bool isTargetSumPossible(const int* denominations, int numDenominations, int targetAmount) {
    // Create a DP array to track if a particular amount can be formed
    bool isPossible[targetAmount + 1];

    // Initialize all amounts as not possible initially
    for (int i = 0; i <= targetAmount; i++) {
        isPossible[i] = false;
    }

    // Base case: It is always possible to form the amount 0 (no coins needed)
    isPossible[0] = true;

    // Iterate through each coin denomination
    for (int i = 0; i < numDenominations; i++) {
        // Update the DP table for amounts that can be formed with the current coin
        for (int amount = denominations[i]; amount <= targetAmount; amount++) {
            if (isPossible[amount - denominations[i]]) {
                isPossible[amount] = true;
            }
        }
    }

    // Return whether the target amount can be formed
    return isPossible[targetAmount];
}

int main() {
    // Define test cases
    struct TestCase {
        int denominations[10];  // Array of coin denominations
        int numDenominations;   // Number of denominations in the array
        int targetAmount;       // Target amount to be formed
    };

    struct TestCase testCases[] = {
        {{5, 10}, 2, 15},        // Expected: Possible
        {{5, 10}, 2, 12},        // Expected: Not possible
        {{1, 2, 5}, 3, 11},      // Expected: Possible
        {{2}, 1, 3},             // Expected: Not possible
        {{2, 3, 7}, 3, 14},      // Expected: Possible
        {{3, 6, 9}, 3, 13},      // Expected: Not possible
        {{1, 5, 10, 25}, 4, 30}, // Expected: Possible
        {{4, 5}, 2, 7},          // Expected: Not possible
        {{1}, 1, 0},             // Expected: Possible (amount 0)
        {{}, 0, 5},              // Expected: Not possible (no coins)
    };

    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    // Process each test case
    for (int testCaseIndex = 0; testCaseIndex < numTestCases; testCaseIndex++) {
        struct TestCase currentTestCase = testCases[testCaseIndex];

        // Determine if the target amount can be formed
        bool canFormTarget = isTargetSumPossible(
            currentTestCase.denominations,
            currentTestCase.numDenominations,
            currentTestCase.targetAmount
        );

        // Print test case details
        printf("Test Case %d:\n", testCaseIndex + 1);
        printf("Coin Denominations: ");
        for (int i = 0; i < currentTestCase.numDenominations; i++) {
            printf("%d ", currentTestCase.denominations[i]);
        }
        printf("\nTarget Amount: %d\n", currentTestCase.targetAmount);
        printf("Can form target amount? %s\n", canFormTarget ? "Yes" : "No");
        printf("-----------------------------\n");
    }

    return 0;
}
