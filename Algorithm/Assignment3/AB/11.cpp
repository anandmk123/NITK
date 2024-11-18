#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <algorithm> // For min function

using namespace std;

int solve(vector<int>& v, int i, int j, vector<vector<int>>& dp) {
    if (i + 1 == j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int ans = INT_MAX;
    for (int k = i + 1; k < j; k++) {
        ans = min(ans, v[i] * v[j] * v[k] + solve(v, i, k, dp) + solve(v, k, j, dp));
    }
    dp[i][j] = ans;
    return dp[i][j];
}

int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(values, 0, n - 1, dp);
}

int main() {
    vector<int> values = {1, 3, 1, 4, 1, 5}; // Example input
    cout << "Minimum score of triangulation: " << minScoreTriangulation(values) << endl;
    return 0;
}
