#include <stdio.h>
#include <stdlib.h>

int triomino_count = 0;

// This function uses a divide-and-conquer approach to recursively place triominos on the board.
void placeTriominos(int **board, int start_row, int start_col, int current_size,
                    int missing_row, int missing_col) {
    // Base case for a 2x2 board: fill it with an L-Triomino
    if (current_size == 2) {
        triomino_count++;
        for (int i = 0; i < current_size; i++) {
            for (int j = 0; j < current_size; j++) {
                // Fill squares, skipping the missing square
                if (start_row + i != missing_row && start_col + j != missing_col) {
                    board[start_row + i][start_col + j] = triomino_count;
                }
            }
        }
        return;
    }

    int triomino_number = triomino_count++;
    // Divide the board into four quadrants
    int half_size = current_size / 2;

    // Process the top-left quadrant
    if (missing_row < start_row + half_size && missing_col < start_col + half_size) {
        // If the missing square is in this quadrant, proceed recursively
        placeTriominos(board, start_row, start_col, half_size, missing_row, missing_col);
    } else {
        // Place an L-Triomino in the bottom right of this quadrant
        board[start_row + half_size - 1][start_col + half_size - 1] = triomino_number;
        placeTriominos(board, start_row, start_col, half_size, start_row + half_size - 1, start_col + half_size - 1);
    }

    // Process the top-right quadrant
    if (missing_row < start_row + half_size && missing_col >= start_col + half_size) {
        // If the missing square is in this quadrant, proceed recursively
        placeTriominos(board, start_row, start_col + half_size, half_size, missing_row, missing_col);
    } else {
        // Place an L-Triomino in the bottom left of this quadrant
        board[start_row + half_size - 1][start_col + half_size] = triomino_number;
        placeTriominos(board, start_row, start_col + half_size, half_size, start_row + half_size - 1, start_col + half_size);
    }

    // Process the bottom-left quadrant
    if (missing_row >= start_row + half_size && missing_col < start_col + half_size) {
        // If the missing square is in this quadrant, proceed recursively
        placeTriominos(board, start_row + half_size, start_col, half_size, missing_row, missing_col);
    } else {
        // Place an L-Triomino in the top right of this quadrant
        board[start_row + half_size][start_col + half_size - 1] = triomino_number;
        placeTriominos(board, start_row + half_size, start_col, half_size, start_row + half_size, start_col + half_size - 1);
    }

    // Process the bottom-right quadrant
    if (missing_row >= start_row + half_size && missing_col >= start_col + half_size) {
        // If the missing square is in this quadrant, proceed recursively
        placeTriominos(board, start_row + half_size, start_col + half_size, half_size, missing_row, missing_col);
    } else {
        // Place an L-Triomino in the top left of this quadrant
        board[start_row + half_size][start_col + half_size] = triomino_number;
        placeTriominos(board, start_row + half_size, start_col + half_size, half_size, start_row + half_size, start_col + half_size);
    }
}

int main() {
    int board_size, missing_row, missing_col;

    printf("Enter the size of the chess board: ");
    scanf("%d", &board_size);
    printf("Enter the index of missing square (row and column): ");
    scanf("%d %d", &missing_row, &missing_col);

    // Dynamically allocate the board
    int **board = (int **)malloc(board_size * sizeof(int *));
    for (int i = 0; i < board_size; i++) {
        board[i] = (int *)malloc(board_size * sizeof(int));
    }

    // Initialize the board with zeros
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j] = 0;
        }
    }

    // Mark the missing square with -1
    board[missing_row][missing_col] = -1;

    // Start placing triominos on the board
    placeTriominos(board, 0, 0, board_size, missing_row, missing_col);

    // Print the filled board
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < board_size; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}
