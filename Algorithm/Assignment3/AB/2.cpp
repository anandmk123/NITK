#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximizeGrade(vector<vector<int>>& B, int H) {
    vector<int> allBenefits;  // Store all benefits in a flat array

    // Flatten the 2D benefit matrix into a 1D array
   for (int i = 0; i < B.size(); ++i) {
    for (int j = 0; j < B[i].size(); ++j) {
        allBenefits.push_back(B[i][j]);
    }
}

    // Sort the benefits in descending order
    sort(allBenefits.rbegin(), allBenefits.rend());

    // Sum the top H benefits
    int totalGrade = 0;
    for (int i = 0; i < H; ++i) {
        totalGrade += allBenefits[i];
    }

    return totalGrade;
}

int main() {
    vector<vector<int>> B = {
        {9, 8, 7},  // Assignment 1 diminishing returns
        {7, 6, 5},  // Assignment 2 diminishing returns
        {5, 4, 3},  // Assignment 3 diminishing returns
        {3, 2, 1}   // Assignment 4 diminishing returns
    };
    int H = 4;  // Available hours

    cout << "Maximum grade: " << maximizeGrade(B, H) << endl;

    return 0;
}