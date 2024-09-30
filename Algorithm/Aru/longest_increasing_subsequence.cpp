#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * This function uses dynamic programming to tabulate the results of overlapping sub problems
 * Time complexity : O(n^2)
 **/
vector<int> longestIncreasingSubsequence(int arr[], int size)
{
    // dp stores the longest increasing subsequence till that index i (i.e) dp[i] is longest subsequence till i
    // ancestor tracks the index of previous element of the longest sequence at index i
    vector<int> dp(size, 1), ancestor(size, -1);

    // O(n^2)
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // If element at j is lesser than element at i, 
            // then longest sequence till i is longest sequence till j + 1 (including the element at i)
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                ancestor[i] = j; // track index of previous element j of current element i .
            }
        }
    }

    // find the maximum value in dp, (i.e) the longest sequence
    //O(n)
    int max = -1, lastPos = -1;

    for (int i = 0; i < dp.size(); i++)
    {
        if (max < dp[i])
        {
            max = dp[i];
            lastPos = i;
        }
    }

    cout << max << "  \n";

    // track the previous elements and reverse it to get the list of longest sequences
    // O(n)
    vector<int> subsequence(max);
    while (lastPos != -1)
    {
        subsequence.push_back(arr[lastPos]);
        lastPos = ancestor[lastPos];
    }

    reverse(subsequence.begin(), subsequence.end());

    return subsequence;
}

int main()
{
    int n;
    cout << "Enter size of the array : ";
    cin >> n;
    cout << "Enter the elements : ";
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    auto result = longestIncreasingSubsequence(arr, n);
    cout << "Size : " << result.size() << endl;
    for (auto i : result)
    {
        cout << i << ", ";
    }
    cout << endl;
}