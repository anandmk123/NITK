#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int minPenalty(vector<int>& hotels) {
    int n = hotels.size();
    vector<int> dp(n, INT_MAX); // Initialize DP table with large values
    dp[0] = 0; // Starting point has no penalty
    
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < j; ++i) {
            int distance = hotels[j] - hotels[i];
            int penalty = (200 - distance) * (200 - distance);
            dp[j] = min(dp[j], dp[i] + penalty);
        }
    }
    
    return dp[n - 1]; // Minimum penalty to reach the last hotel
}

int main() {
    vector<int> hotels = {0,50, 300, 600, 1000}; // Example hotel mileposts
    cout << "Minimum total penalty: " << minPenalty(hotels) << endl;
    return 0;
}
