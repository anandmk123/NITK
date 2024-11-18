#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compare activities based on their finish times
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

// Function to find and display the maximum number of non-overlapping activities
int maxActivities(int start[], int finish[], int n) {
    vector<pair<int, int>> activities;

    // Create pairs of start and finish times
    for (int i = 0; i < n; i++) {
        activities.push_back(make_pair(start[i], finish[i]));
    }

    // Sort the activities based on finish times
    sort(activities.begin(), activities.end(), cmp);

    cout << "Following activities are selected:\n";

    // Select the first activity
    int count = 1;  // First activity selected
    int lastFinishTime = activities[0].second;
    cout << "Activity: (" << activities[0].first << ", " << activities[0].second << ")\n";

    // Iterate through the rest of the activities
    for (int i = 1; i < n; i++) {
        if (activities[i].first >= lastFinishTime) {
            count++;
            lastFinishTime = activities[i].second;
            cout << "Activity: (" << activities[i].first << ", " << activities[i].second << ")\n";
        }
    }

    return count;
}

// Driver program
int main() {
    // Example input: Start and finish times of activities
    int start[] = {1, 3, 0, 5, 8, 5};
    int finish[] = {2, 4, 6, 7, 9, 9};
    int n = sizeof(start) / sizeof(start[0]);

    int maxActivitiesCount = maxActivities(start, finish, n);
    cout << "Maximum number of non-overlapping activities: " << maxActivitiesCount << endl;

    return 0;
}
