#include <iostream>
#include <vector>
#include <climits>  // For INT_MIN

using namespace std;

int maxSubArray(vector<int>& nums) {
    int maxsum = INT_MIN;
    int currsum = 0;

    // Variables to track the indices of the maximum subarray
    int start = 0, end = 0, tempStart = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (currsum + nums[i] > nums[i]) {
            currsum += nums[i];  // Continue adding to current subarray
        } else {
            currsum = nums[i];   // Start a new subarray
            tempStart = i;       // Update temporary start index
        }

        if (currsum > maxsum) {
            maxsum = currsum;
            start = tempStart;   // Update start to tempStart
            end = i;             // Update end to current index
        }
    }

     cout << "Maximum Subarray Sum: " << maxsum << endl;

    // Print the subarray that gives the maximum sum
    cout << "Maximum Subarray: [";
    for (int i = start; i <= end; i++) {
        cout << nums[i];
        if (i < end) cout << ", ";
    }
    cout << "]" << endl;

    return maxsum;
}

int main() {
    // Demo array
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    // Call the function and print the result
     maxSubArray(nums);
   

    return 0;
}
