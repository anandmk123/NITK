#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
struct Activity {
    int id;      // Unique identifier for the activity
    int start;   // Start time of the activity
    int finish;  // Finish time of the activity
};

// Comparator function for qsort to sort activities by their finish time
// Takes two void pointers as arguments and casts them to Activity structs
int activityCompare(const void* a, const void* b) {
    struct Activity* activityA = (struct Activity*)a;
    struct Activity* activityB = (struct Activity*)b;
    return activityA->finish - activityB->finish; // Compare finish times
}

int main() {
    // Input: List of activities with their start and finish times
    // struct Activity activities[] = {
    //     {1, 1, 4},  // Activity 1: Start at 1, finish at 4
    //     {2, 3, 5},  // Activity 2: Start at 3, finish at 5
    //     {3, 0, 6},  // Activity 3: Start at 0, finish at 6
    //     {4, 5, 7},  // Activity 4: Start at 5, finish at 7
    //     {5, 8, 9},  // Activity 5: Start at 8, finish at 9
    //     {6, 5, 9}   // Activity 6: Start at 5, finish at 9
    // };

    struct Activity activities[] = {
        {1, 2, 3},
        {2, 1, 4},
        {3, 3, 5},
        {4, 0, 6},
        {5, 5, 7},
        {6, 8, 9},
        {7, 5, 9}
    };


    // Calculate the number of activities
    int n = sizeof(activities) / sizeof(activities[0]);

    // Step 1: Sort the activities based on their finish times
    // This ensures that we always consider the earliest finishing activity first
    qsort(activities, n, sizeof(struct Activity), activityCompare);

    // Step 2: Select activities
    printf("Selected Activities:\n");

    // The first activity is always selected because it finishes the earliest
    int lastSelectedIndex = 0; // Index of the last selected activity
    printf("Activity %d (Time: %d to %d)\n", 
           activities[lastSelectedIndex].id, 
           activities[lastSelectedIndex].start, 
           activities[lastSelectedIndex].finish);

    // Step 3: Iterate through the remaining activities
    for (int i = 1; i < n; i++) {
        // If the start time of the current activity is greater than or equal to
        // the finish time of the last selected activity, select it
        if (activities[i].start >= activities[lastSelectedIndex].finish) {
            printf("Activity %d (Time: %d to %d)\n", 
                   activities[i].id, 
                   activities[i].start, 
                   activities[i].finish);

            // Update the last selected activity index
            lastSelectedIndex = i;
        }
    }

    return 0;
}
