#include <iostream>
#include <vector>
#include <string>
using namespace std;

pair<int, string> longestCommonSubstring(string x, string y) {
    int n = x.length(), m = y.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLength = 0;  // Maximum length of LCS
    int endIndex = -1;  // End index of the longest common substring in `x`
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;  // Update end index of the substring
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    // Extract the longest common substring from `x` using endIndex and maxLength
    string lcs = (endIndex != -1) ? x.substr(endIndex - maxLength + 1, maxLength) : "";
    
    return {maxLength, lcs};
}

int main() {
    string x = "abbcde";
    string y = "abbfde";
    auto result = longestCommonSubstring(x, y);
    
    cout << "Length of Longest Common Substring: " << result.first << endl;
    cout << "Longest Common Substring: \"" << result.second << "\"" << endl;
    
    return 0;
}
