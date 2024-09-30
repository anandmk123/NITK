#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * This function uses divide and conquer approach to find the longest common prefix in the given array of strings
 * worst case time complexity of this algorithm is O(m log n), where m is length of longest string in the array and n is the size of the array.
 */
string longestCommonPrefix(string words[], int l, int h)
{
    // Base condition to check whether the leaf (word) of the recursion tree is reached
    if (h > l)
    {
        /**
         * Split the current array at the middle into two sub arrays
         */
        int mid = (h + l) / 2;
        string str1 = longestCommonPrefix(words, 0, mid);
        string str2 = longestCommonPrefix(words, mid + 1, h);

        /**
         * Compare the common prefixes from the left (str1) and right (str2) sub array and return the common prefix of
         * str1 and str2
         */
        int i = 0, limit = min(str1.size(), str2.size());
        while (i < limit && str1[i] == str2[i])
            i++;
        return str1.substr(0, i);
    }

    // leaf of the recursion tree
    return words[l];
}

int main()
{
    // get input from the file
    ifstream input("lcp_in.txt");
    int n, i = 0;
    input >> n;
    string words[n];
    string inputWord;
    while (input >> inputWord)
    {
        words[i++] = inputWord;
    }
    cout << longestCommonPrefix(words, 0, n - 1) << endl;
}