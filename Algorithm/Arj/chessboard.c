#include <stdio.h>

#define MAX 128 // Assuming the maximum size of the chessboard to be 128 x 128

int board[MAX][MAX];
int tile = 0; // Global variable to track the current tile number

// Function to place the L-shaped triomino
void placeTile(int tr, int tc, int dr, int dc, int size) {
    if (size == 2) {
        tile++; // Increment the tile number
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!(tr + i == dr && tc + j == dc)) {
                    board[tr + i][tc + j] = tile;
                }
            }
        }
        return;
    }

    int t = tile++; // Current tile to place the L-triomino
    int newSize = size / 2;

    // Place the L-shaped triomino in the center
    // Check each quadrant and place the L-shaped tile in the center accordingly
    
    // Top-left quadrant
    if (dr < tr + newSize && dc < tc + newSize) {
        // The missing tile is in this quadrant
        placeTile(tr, tc, dr, dc, newSize);
    } else {
        // No missing tile, place L-shaped triomino
        board[tr + newSize - 1][tc + newSize - 1] = t;
        placeTile(tr, tc, tr + newSize - 1, tc + newSize - 1, newSize);
    }

    // Top-right quadrant
    if (dr < tr + newSize && dc >= tc + newSize) {
        // The missing tile is in this quadrant
        placeTile(tr, tc + newSize, dr, dc, newSize);
    } else {
        // No missing tile, place L-shaped triomino
        board[tr + newSize - 1][tc + newSize] = t;
        placeTile(tr, tc + newSize, tr + newSize - 1, tc + newSize, newSize);
    }

    // Bottom-left quadrant
    if (dr >= tr + newSize && dc < tc + newSize) {
        // The missing tile is in this quadrant
        placeTile(tr + newSize, tc, dr, dc, newSize);
    } else {
        // No missing tile, place L-shaped triomino
        board[tr + newSize][tc + newSize - 1] = t;
        placeTile(tr + newSize, tc, tr + newSize, tc + newSize - 1, newSize);
    }

    // Bottom-right quadrant
    if (dr >= tr + newSize && dc >= tc + newSize) {
        // The missing tile is in this quadrant
        placeTile(tr + newSize, tc + newSize, dr, dc, newSize);
    } else {
        // No missing tile, place L-shaped triomino
        board[tr + newSize][tc + newSize] = t;
        placeTile(tr + newSize, tc + newSize, tr + newSize, tc + newSize, newSize);
    }
}

// Function to print the board
void printBoard(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int n, missingRow, missingCol;
    
    printf("Enter the size of the board (must be a power of 2): ");
    scanf("%d", &n);
    
    printf("Enter the row and column of the missing square: ");
    scanf("%d %d", &missingRow, &missingCol);
    
    // Initialize the board with 0's (empty spaces)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    
    // Place the missing tile and start the tiling process
    placeTile(0, 0, missingRow, missingCol, n);
    
    // Print the resulting board
    printf("The board with L-shaped triominoes:\n");
    printBoard(n);
    
    return 0;
}