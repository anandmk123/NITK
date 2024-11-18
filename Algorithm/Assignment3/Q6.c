#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to calculate the minimum penalty and find the optimal sequence of hotels
void findOptimalStops(int hotelCount, int* hotelDistances) {
    // Include the starting point at mile post 0
    int* allStops = (int*)malloc((hotelCount + 1) * sizeof(int));
    allStops[0] = 0;
    for (int i = 0; i < hotelCount; i++) {
        allStops[i + 1] = hotelDistances[i];
    }
    hotelCount += 1; // Include starting point in the total count

    // Initialize the dp array to store the minimum penalty for each stop
    int* minPenalty = (int*)malloc(hotelCount * sizeof(int));
    int* previousStop = (int*)malloc(hotelCount * sizeof(int)); // To reconstruct the path
    for (int i = 0; i < hotelCount; i++) {
        minPenalty[i] = INT_MAX;
        previousStop[i] = -1;
    }
    minPenalty[0] = 0; // No penalty at the starting point

    // Compute the minimum penalty using dynamic programming
    for (int currentStop = 1; currentStop < hotelCount; currentStop++) {
        for (int earlierStop = 0; earlierStop < currentStop; earlierStop++) {
            int distanceTravelled = allStops[currentStop] - allStops[earlierStop];
            int penaltyForDay = (200 - distanceTravelled) * (200 - distanceTravelled);
            int totalPenalty = minPenalty[earlierStop] + penaltyForDay;
            if (totalPenalty < minPenalty[currentStop]) {
                minPenalty[currentStop] = totalPenalty;
                previousStop[currentStop] = earlierStop; // Store the previous hotel index
            }
        }
    }

    // Output the minimum total penalty
    printf("Minimum Total Penalty: %d\n", minPenalty[hotelCount - 1]);

    // Reconstruct the optimal sequence of stops
    int* optimalStops = (int*)malloc(hotelCount * sizeof(int));
    int stopCount = 0;
    int currentIndex = hotelCount - 1;
    while (currentIndex != -1) {
        optimalStops[stopCount++] = currentIndex;
        currentIndex = previousStop[currentIndex];
    }

    // Reverse the path to get the correct order of stops
    for (int i = 0; i < stopCount / 2; i++) {
        int temp = optimalStops[i];
        optimalStops[i] = optimalStops[stopCount - i - 1];
        optimalStops[stopCount - i - 1] = temp;
    }

    // Output the optimal sequence of stops
    printf("Optimal Sequence of Hotels (mile posts):\n");
    for (int i = 1; i < stopCount; i++) { // Skip the starting point at index 0
        printf("%d ", allStops[optimalStops[i]]);
    }
    printf("\n");

    // Free allocated memory
    free(allStops);
    free(minPenalty);
    free(previousStop);
    free(optimalStops);
}

int main() {
    int hotelCount = 4;
    int hotelDistances[] = {50, 300, 600, 1000}; // Hotel mile posts

    findOptimalStops(hotelCount, hotelDistances);

    return 0;
}
