#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for reverse()

using namespace std;

// Helper function to solve using tabulation with space optimization
pair<int, vector<pair<int, int>>> solveTab(const string& a, const string& b) {
    int m = a.length();
    int n = b.length();

    vector<int> curr(n + 1, 0);
    vector<int> next(n + 1, 0);

    vector<vector<pair<int, int>>> paths(m + 1, vector<pair<int, int>>(n + 1));

    // Fill the DP table from bottom-right to top-left
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (a[i] == b[j]) {
                curr[j] = 1 + next[j + 1];
                paths[i][j] = make_pair(i, j);  // Save pair of indices
            } else {
                if (next[j] > curr[j + 1]) {
                    curr[j] = next[j];
                    paths[i][j] = paths[i + 1][j];  // Carry forward the best path
                } else {
                    curr[j] = curr[j + 1];
                    paths[i][j] = paths[i][j + 1];  // Carry forward the best path
                }
            }
        }
        next = curr; // Update the next row
    }

    // Reconstruct pairs
    vector<pair<int, int>> resultPairs;
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (a[i] == b[j]) {
            resultPairs.push_back(make_pair(i, j));
            i++;
            j++;
        } else {
            pair<int, int> nextIndices = paths[i][j];
            if (nextIndices.first != i || nextIndices.second != j) {  // move as per DP path
                i = nextIndices.first;
                j = nextIndices.second;
            } else {
                break;
            }
        }
    }

    return make_pair(next[0], resultPairs);  // Result along with pairs
}

// Function to find the length of the longest palindromic subsequence
pair<int, vector<pair<int, int>>> longestPalindromeSubseq(const string& s) {
    string revStr = s; // Create a reversed string
    reverse(revStr.begin(), revStr.end());
    return solveTab(s, revStr);
}

int main() {
    string testStr = "bbbab";
    string revStr = testStr;
    reverse(revStr.begin(), revStr.end());

    pair<int, vector<pair<int, int>>> result = longestPalindromeSubseq(testStr);
    int length = result.first;
    vector<pair<int, int>> pairs = result.second;

    cout << "The longest palindromic subsequence length of \"" 
         << testStr << "\" is: " 
         << length << endl;

    // Separate indices for both strings
    vector<int> originalIndices;
    vector<int> reversedIndices;
    for (int i = 0; i < pairs.size(); i++) {
        originalIndices.push_back(pairs[i].first);
        reversedIndices.push_back(pairs[i].second);
    }

    // Display indices with string context
    cout << "Indices in \"" << testStr << "\" contributing to LPS: ";
    for (int i = 0; i < originalIndices.size(); i++) {
        cout << originalIndices[i];
        if (i < originalIndices.size() - 1) cout << ", ";
    }
    cout << endl;

    cout << "Indices in \"" << revStr << "\" contributing to LPS: ";
    for (int i = 0; i < reversedIndices.size(); i++) {
        cout << reversedIndices[i];
        if (i < reversedIndices.size() - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}
