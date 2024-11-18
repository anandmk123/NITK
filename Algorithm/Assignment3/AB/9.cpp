#include <iostream>
#include <vector>

using namespace std;

// Function to print a single subset
void printSubset(const vector<int>& subset) {
    cout << "{ ";
   for (int i = 0; i < subset.size(); i++) {
    cout << subset[i] << " ";
}
    cout << "}" << endl;
}

// Recursive function to find all subsets that sum to the target
void findSubsets(const vector<int>& coins, int target, vector<int>& currentSubset, int index) {
    // Base case: if target becomes 0, print the current subset
    if (target == 0) {
        printSubset(currentSubset);
        return;
    }

    // If target becomes negative or no coins are left, return
    if (target < 0 || index >= coins.size()) {
        return;
    }

    // Include the current coin in the subset and explore
    currentSubset.push_back(coins[index]);
    findSubsets(coins, target - coins[index], currentSubset, index);

    // Backtrack: remove the last coin and explore the next possibility
    currentSubset.pop_back();
    findSubsets(coins, target, currentSubset, index + 1);
}

// Dynamic Programming function to find the number of ways to make the target sum
int countWays(const vector<int>& coins, int v) {
    int n = coins.size();

    // DP table
    vector<vector<int>> dp(n + 1, vector<int>(v + 1, 0));

    // Base case: only one way to make sum 0
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= v; j++) {
            if (j >= coins[i - 1]) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]]; // Include or exclude the coin
            } else {
                dp[i][j] = dp[i - 1][j]; // Exclude the coin
            }
        }
    }

    return dp[n][v];
}

int main() {
    vector<int> coins = {5, 10}; // Example coin denominations
    int target = 12;                // Example target value

    // Compute the number of ways
    int ways = countWays(coins, target);
    if (ways>0){
        cout<<"Yes it is possible to make change for : "<< target<<endl;
    }else{
        cout<<"No it is not possible to make change for : "<< target<<endl;
    }
    cout << "Number of ways to make change for " << target << " : " << ways << endl;

    // Print all subsets
    vector<int> currentSubset;
    cout << "Subsets that sum to " << target << ":" << endl;
    findSubsets(coins, target, currentSubset, 0);

    return 0;
}
