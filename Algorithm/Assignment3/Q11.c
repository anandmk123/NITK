#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to solve the triangulation problem for a given segment
int calculateMinScore(int* vertexValues, int start, int end, int** memo) {
    // Base case: If only two vertices, no triangle can be formed
    if (start + 1 == end) {
        return 0;
    }

    // If the result is already calculated, return it (memoization)
    if (memo[start][end] != -1) {
        return memo[start][end];
    }

    int minScore = INT_MAX;

    // Try splitting the polygon segment at all possible points
    for (int split = start + 1; split < end; split++) {
        // Calculate the score for this split and recursively calculate for subproblems
        int score = vertexValues[start] * vertexValues[end] * vertexValues[split]
                  + calculateMinScore(vertexValues, start, split, memo)
                  + calculateMinScore(vertexValues, split, end, memo);
        
        // Update the minimum score
        if (score < minScore) {
            minScore = score;
        }
    }

    // Store the result in the memo table and return
    memo[start][end] = minScore;
    return minScore;
}

// Wrapper function to initialize the DP table and call the recursive function
int findMinTriangulationScore(int* vertexValues, int vertexCount) {
    // Allocate memory for the memoization table
    int** memo = (int**)malloc(vertexCount * sizeof(int*));
    for (int i = 0; i < vertexCount; i++) {
        memo[i] = (int*)malloc(vertexCount * sizeof(int));
        for (int j = 0; j < vertexCount; j++) {
            memo[i][j] = -1; // Initialize all values to -1
        }
    }

    // Calculate the minimum triangulation score starting from the full polygon
    int result = calculateMinScore(vertexValues, 0, vertexCount - 1, memo);

    // Free memory allocated for the memoization table
    for (int i = 0; i < vertexCount; i++) {
        free(memo[i]);
    }
    free(memo);

    return result;
}

int main() {
    // Example input: vertex values of a convex polygon
    int vertexValues[] = {1, 3, 1, 4, 1, 5};
    int vertexCount = sizeof(vertexValues) / sizeof(vertexValues[0]);

    // Find and print the minimum triangulation score
    printf("Minimum score of triangulation: %d\n", findMinTriangulationScore(vertexValues, vertexCount));
    return 0;
}
