#include <iostream>
#include <vector>
using namespace std;

bool canMakeChange(vector<int>& coins, int v, vector<int>& result) {
    int n = coins.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(v + 1, false));

    // Base case: You can always make value 0.
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= v; ++j) {
            // Not using the current coin
            dp[i][j] = dp[i - 1][j];

            // Using the current coin if it doesn't exceed the current value
            if (j >= coins[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - coins[i - 1]];
            }
        }
    }

    // If it's not possible to make the change, return false
    if (!dp[n][v]) {
        return false;
    }

    // Backtrack to find the coins used
    int i = n, j = v;
    while (j > 0 && i > 0) {
        if (dp[i - 1][j]) {
            // Coin not used, move to previous row
            i--;
        } else {
            // Coin used, add it to result
            result.push_back(coins[i - 1]);
            j -= coins[i - 1];
            i--;
        }
    }

    return true;
}

int main() {
    vector<int> coins = {1, 5, 10, 20};
    int v = 31;
    vector<int> result;

    if (canMakeChange(coins, v, result)) {
        cout << "Yes, it's possible to make change for " << v << endl;
        cout << "Coins used: ";
        for (size_t i = 0; i < result.size(); ++i) {
        int coin = result[i];
        cout << coin << " ";
        }

        cout << endl;
    } else {
        cout << "No, it's not possible to make change for " << v << endl;
    }

    return 0;
}
