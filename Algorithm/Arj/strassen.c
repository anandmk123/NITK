#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void addMatrices(int **A, int **B, int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtractMatrices(int **A, int **B, int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Function to allocate memory for a matrix
int** allocateMatrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        matrix[i] = (int *)malloc(size * sizeof(int));
    return matrix;
}

// Function to free the allocated memory for a matrix
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

// Function to implement Strassen's Algorithm for matrix multiplication
void strassen(int **A, int **B, int **C, int size) {
    // Base case: When matrix size is 1x1, multiply directly
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Divide matrices into submatrices
    int newSize = size / 2;
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **temp1 = allocateMatrix(newSize);
    int **temp2 = allocateMatrix(newSize);

    // Split A into A11, A12, A21, A22
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute M1 = (A11 + A22) * (B11 + B22)
    addMatrices(A11, A22, temp1, newSize);
    addMatrices(B11, B22, temp2, newSize);
    strassen(temp1, temp2, M1, newSize);

    // Compute M2 = (A21 + A22) * B11
    addMatrices(A21, A22, temp1, newSize);
    strassen(temp1, B11, M2, newSize);

    // Compute M3 = A11 * (B12 - B22)
    subtractMatrices(B12, B22, temp1, newSize);
    strassen(A11, temp1, M3, newSize);

    // Compute M4 = A22 * (B21 - B11)
    subtractMatrices(B21, B11, temp1, newSize);
    strassen(A22, temp1, M4, newSize);

    // Compute M5 = (A11 + A12) * B22
    addMatrices(A11, A12, temp1, newSize);
    strassen(temp1, B22, M5, newSize);

    // Compute M6 = (A21 - A11) * (B11 + B12)
    subtractMatrices(A21, A11, temp1, newSize);
    addMatrices(B11, B12, temp2, newSize);
    strassen(temp1, temp2, M6, newSize);

    // Compute M7 = (A12 - A22) * (B21 + B22)
    subtractMatrices(A12, A22, temp1, newSize);
    addMatrices(B21, B22, temp2, newSize);
    strassen(temp1, temp2, M7, newSize);

    // Compute C11, C12, C21, C22
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C12[i][j] = M3[i][j] + M5[i][j];
            C21[i][j] = M2[i][j] + M4[i][j];
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Combine C11, C12, C21, C22 into the result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free all allocated memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize); freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize); freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize); freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize); freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize); freeMatrix(M7, newSize);
    freeMatrix(temp1, newSize); freeMatrix(temp2, newSize);
}

// Function to display a matrix
void displayMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

// Main function
int main() {
    int n;
    printf("Enter the size of the matrix (must be a power of 2): ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Perform Strassen's algorithm
    strassen(A, B, C, n);

    // Display the result
    printf("Resultant matrix C after multiplication:\n");
    displayMatrix(C, n);

    // Free the allocated
}