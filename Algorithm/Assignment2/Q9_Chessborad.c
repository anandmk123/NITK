#include <stdio.h>

#define MAX_SIZE 128 // Maximum chessboard size assumed to be 128x128

int chessboard[MAX_SIZE][MAX_SIZE];
int triomino_id = 0; // Global variable to track the current triomino ID

// Function to recursively place the L-shaped triomino on the chessboard
void tilePlacement(int startRow, int startCol, int missingRow, int missingCol, int currentSize) {
    // Base case: when the current quadrant is 2x2, place the L-shaped triomino
    if (currentSize == 2) {
        triomino_id++; // Increment the triomino ID for this placement
        for (int i = 0; i < currentSize; i++) {
            for (int j = 0; j < currentSize; j++) {
                // Place the triomino in all cells except the designated missing square
                if (!(startRow + i == missingRow && startCol + j == missingCol)) {
                    chessboard[startRow + i][startCol + j] = triomino_id;
                }
            }
        }
        return;
    }

    // Divide the board into four quadrants and recursively tile them
    int currentTriomino = triomino_id++; // Current triomino ID for this step
    int halfSize = currentSize / 2;      // Half of the current board size to divide it into quadrants

    // Process top-left quadrant
    if (missingRow < startRow + halfSize && missingCol < startCol + halfSize) {
        // If the missing tile is in this quadrant, recurse on this part
        tilePlacement(startRow, startCol, missingRow, missingCol, halfSize);
    } else {
        // Otherwise, place part of the L-shaped triomino in the center
        chessboard[startRow + halfSize - 1][startCol + halfSize - 1] = currentTriomino;
        tilePlacement(startRow, startCol, startRow + halfSize - 1, startCol + halfSize - 1, halfSize);
    }

    // Process top-right quadrant
    if (missingRow < startRow + halfSize && missingCol >= startCol + halfSize) {
        // If the missing tile is in this quadrant, recurse on this part
        tilePlacement(startRow, startCol + halfSize, missingRow, missingCol, halfSize);
    } else {
        // Otherwise, place part of the L-shaped triomino in the center
        chessboard[startRow + halfSize - 1][startCol + halfSize] = currentTriomino;
        tilePlacement(startRow, startCol + halfSize, startRow + halfSize - 1, startCol + halfSize, halfSize);
    }

    // Process bottom-left quadrant
    if (missingRow >= startRow + halfSize && missingCol < startCol + halfSize) {
        // If the missing tile is in this quadrant, recurse on this part
        tilePlacement(startRow + halfSize, startCol, missingRow, missingCol, halfSize);
    } else {
        // Otherwise, place part of the L-shaped triomino in the center
        chessboard[startRow + halfSize][startCol + halfSize - 1] = currentTriomino;
        tilePlacement(startRow + halfSize, startCol, startRow + halfSize, startCol + halfSize - 1, halfSize);
    }

    // Process bottom-right quadrant
    if (missingRow >= startRow + halfSize && missingCol >= startCol + halfSize) {
        // If the missing tile is in this quadrant, recurse on this part
        tilePlacement(startRow + halfSize, startCol + halfSize, missingRow, missingCol, halfSize);
    } else {
        // Otherwise, place part of the L-shaped triomino in the center
        chessboard[startRow + halfSize][startCol + halfSize] = currentTriomino;
        tilePlacement(startRow + halfSize, startCol + halfSize, startRow + halfSize, startCol + halfSize, halfSize);
    }
}

// Main function
int main() {
    int boardSize, holeRow, holeCol;
    
    // Input: get the board size (must be a power of 2) and the missing square's position
    printf("Enter the size of the board (must be a power of 2): ");
    scanf("%d", &boardSize);
    
    printf("Enter the row and column of the missing square: ");
    scanf("%d %d", &holeRow, &holeCol);
    
    // Initialize the chessboard with 0's and mark the missing square with -1
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            chessboard[i][j] = 0; // Initialize all squares with 0
        }
    }
    chessboard[holeRow][holeCol] = -1; // Mark the missing square with -1
    
    // Call the recursive function to start placing triominos
    tilePlacement(0, 0, holeRow, holeCol, boardSize);
    
    // Print the final board configuration
    printf("The board with L-shaped triominoes:\n");
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            printf("%2d ", chessboard[i][j]); // Print each cell with proper formatting
        }
        printf("\n"); // Move to the next row
    }
    
    return 0;
}
