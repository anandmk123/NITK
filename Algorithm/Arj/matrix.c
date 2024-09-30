#include <stdio.h>
#include <limits.h>

int countLessEqual(int matrix[][100], int m, int n, int mid) {
    int count = 0;
    int row = m - 1, col = 0;

    while (row >= 0 && col < n) {
        if (matrix[row][col] <= mid) {
            count += (row + 1); // All elements in this column up to this row are <= mid
            col++;  // Move right
        } else {
            row--;  // Move up
        }
    }

    return count;
}

int kthSmallest(int matrix[][100], int m, int n, int k) {
    int left = matrix[0][0], right = matrix[m - 1][n - 1];

    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = countLessEqual(matrix, m, n, mid);

        if (count < k) {
            left = mid + 1; // Look for a larger number
        } else {
            right = mid; // mid could be the k-th smallest
        }
    }

    return left; // or right, both are the same here
}

int main() {
    int matrix[100][100] = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int m = 3, n = 3, k = 3;

    int result = kthSmallest(matrix, m, n, k);
    printf("The %d-th smallest element is: %d\n", k, result);

    return 0;
}
