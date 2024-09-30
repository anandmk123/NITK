#include <stdio.h>
#include <stdlib.h>

// Function to count elements in the matrix that are less than or equal to the given value 'middle'
// This is done starting from the bottom-left corner of the matrix.
// Time Complexity: O(max(rows, cols))
int count_less_or_equal(int **matrix, int middle, int rows, int cols) {
    int count = 0;
    int i = rows - 1;  // Start from the last row (bottom-left corner)
    int j = 0;         // Start from the first column

    // Traverse through the matrix
    while (i >= 0 && j < cols) {
        // If the current element is less than or equal to 'middle', it means
        // all the elements above it in the same column are also less than or equal to 'middle'
        if (matrix[i][j] <= middle) {
            count += (i + 1); // Add the number of elements from the first row to the current row
            j++; // Move to the next column
        } else {
            // If the current element is greater than 'middle', move up in the matrix
            i--;
        }
    }

    return count; // Return the total count of elements less than or equal to 'middle'
}

// Function to find the kth smallest element in a sorted matrix using binary search
// Time Complexity: O(rows * log(cols))
int find_kth_smallest(int **matrix, int k, int rows, int cols) {
    int low = matrix[0][0]; // Minimum element in the matrix (top-left corner)
    int high = matrix[rows - 1][cols - 1]; // Maximum element in the matrix (bottom-right corner)

    // Perform binary search between the smallest and largest element
    while (low < high) {
        int middle = (low + high) / 2; // Calculate the middle value

        // Count how many elements in the matrix are less than or equal to 'middle'
        if (count_less_or_equal(matrix, middle, rows, cols) <= k) {
            // If the count is less than or equal to k, the kth smallest element
            // must be on the right side of the matrix or might be 'middle'
            low = middle + 1;
        } else {
            // If more than k elements are less than or equal to 'middle', 
            // the kth smallest element is on the left side of the matrix
            high = middle;
        }
    }

    return low; // 'low' will be the kth smallest element
}

int main() {
    int rows, cols, k;
    
    // Get matrix dimensions from the user
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    // Dynamically allocate memory for the matrix based on user input
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Input the matrix elements, which are assumed to be sorted
    printf("Enter the elements of the matrix (in sorted order): \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Get the value of k from the user
    printf("Enter k: ");
    scanf("%d", &k);

    // Find and print the kth smallest element in the matrix
    printf("The %dth smallest element in the matrix is %d\n", k, find_kth_smallest(matrix, k - 1, rows, cols));

    // Free the dynamically allocated memory to avoid memory leaks
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
