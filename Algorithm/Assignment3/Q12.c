#include <stdio.h>
#include <stdlib.h>

// Comparator function for sorting doubles in ascending order
int compare(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

// Function to find the minimum number of guards and their positions
void findMinimumGuards(double* paintingPositions, int paintingCount, double** guardPositions, int* guardCount) {
    // Create a copy of the painting positions for sorting
    double* sortedPositions = (double*)malloc(paintingCount * sizeof(double));
    for (int i = 0; i < paintingCount; i++) {
        sortedPositions[i] = paintingPositions[i];
    }
    // Sort the painting positions
    qsort(sortedPositions, paintingCount, sizeof(double), compare);

    // Allocate memory to store the guard positions
    double* guards = (double*)malloc(paintingCount * sizeof(double));
    int guardIndex = 0; // Index to track the number of guards placed

    int i = 0; // Index to traverse through the sorted painting positions
    while (i < paintingCount) {
        // The leftmost uncovered painting
        double leftmostPainting = sortedPositions[i];

        // Place a guard at position one unit to the right of the leftmost painting
        double currentGuardPosition = leftmostPainting + 1;
        guards[guardIndex++] = currentGuardPosition;

        // Advance the index to skip all paintings covered by this guard
        i++;
        while (i < paintingCount && sortedPositions[i] <= currentGuardPosition + 1) {
            i++;
        }
    }

    // Update output variables with the guard positions and count
    *guardPositions = guards;
    *guardCount = guardIndex;

    // Free the temporary sorted positions array
    free(sortedPositions);
}

int main() {
    // Example positions of paintings on the wall
    double paintingPositions[] = {0.5, 1.2, 2.8, 3.0, 4.1, 5.5, 6.0, 7.2, 8.5, 9.1};
    int paintingCount = sizeof(paintingPositions) / sizeof(paintingPositions[0]);

    double* guardPositions = NULL; // Pointer to store guard positions
    int guardCount = 0;           // Variable to store the number of guards

    // Find the guard positions to cover all paintings
    findMinimumGuards(paintingPositions, paintingCount, &guardPositions, &guardCount);

    // Output the results
    printf("Minimum number of guards required: %d\n", guardCount);
    printf("Guard positions:\n");
    for (int i = 0; i < guardCount; i++) {
        printf("%.1f ", guardPositions[i]);
    }
    printf("\n");

    // Free allocated memory for guard positions
    free(guardPositions);

    return 0;
}
