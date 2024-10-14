#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Brute force approach for matrix multiplication
void brute_force_matrix_multiply(int** matA, int** matB, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

// Base case for Strassen's algorithm (2x2 matrix multiplication)
void strassen_base_case(int** matA, int** matB, int** result) {
    int a11 = matA[0][0], a12 = matA[0][1], a21 = matA[1][0], a22 = matA[1][1];
    int b11 = matB[0][0], b12 = matB[0][1], b21 = matB[1][0], b22 = matB[1][1];

    int p1 = a11 * (b12 - b22);
    int p2 = (a11 + a12) * b22;
    int p3 = (a21 + a22) * b11;
    int p4 = a22 * (b21 - b11);
    int p5 = (a11 + a22) * (b11 + b22);
    int p6 = (a12 - a22) * (b21 + b22);
    int p7 = (a11 - a21) * (b11 + b12);

    result[0][0] = a11 * b11 + a12 * b21;
    result[0][1] = a11 * b12 + a12 * b22;
    result[1][0] = a21 * b11 + a22 * b21;
    result[1][1] = a21 * b12 + a22 * b22;
}

// Utility function to add two matrices
void add_matrices(int** matA, int** matB, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matA[i][j] + matB[i][j];
        }
    }
}

// Utility function to subtract two matrices
void subtract_matrices(int** matA, int** matB, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matA[i][j] - matB[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassen_matrix_multiply(int** matA, int** matB, int size, int** result) {
    if (size == 2) {
        strassen_base_case(matA, matB, result);
        return;
    }

    // Split the current matrix into 4 sub-matrices
    int newSize = size / 2;

    // Dynamically allocate sub-matrices
    int** a11 = (int**)malloc(newSize * sizeof(int*));
    int** a12 = (int**)malloc(newSize * sizeof(int*));
    int** a21 = (int**)malloc(newSize * sizeof(int*));
    int** a22 = (int**)malloc(newSize * sizeof(int*));

    int** b11 = (int**)malloc(newSize * sizeof(int*));
    int** b12 = (int**)malloc(newSize * sizeof(int*));
    int** b21 = (int**)malloc(newSize * sizeof(int*));
    int** b22 = (int**)malloc(newSize * sizeof(int*));

    for (int i = 0; i < newSize; i++) {
        a11[i] = (int*)malloc(newSize * sizeof(int));
        a12[i] = (int*)malloc(newSize * sizeof(int));
        a21[i] = (int*)malloc(newSize * sizeof(int));
        a22[i] = (int*)malloc(newSize * sizeof(int));

        b11[i] = (int*)malloc(newSize * sizeof(int));
        b12[i] = (int*)malloc(newSize * sizeof(int));
        b21[i] = (int*)malloc(newSize * sizeof(int));
        b22[i] = (int*)malloc(newSize * sizeof(int));
    }

    // Divide the matrices into sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = matA[i][j];
            a12[i][j] = matA[i][j + newSize];
            a21[i][j] = matA[i + newSize][j];
            a22[i][j] = matA[i + newSize][j + newSize];

            b11[i][j] = matB[i][j];
            b12[i][j] = matB[i][j + newSize];
            b21[i][j] = matB[i + newSize][j];
            b22[i][j] = matB[i + newSize][j + newSize];
        }
    }

    // Compute the intermediate matrices
    int** m1 = (int**)malloc(newSize * sizeof(int*));
    int** m2 = (int**)malloc(newSize * sizeof(int*));
    int** m3 = (int**)malloc(newSize * sizeof(int*));
    int** m4 = (int**)malloc(newSize * sizeof(int*));
    int** m5 = (int**)malloc(newSize * sizeof(int*));
    int** m6 = (int**)malloc(newSize * sizeof(int*));
    int** m7 = (int**)malloc(newSize * sizeof(int*));

    for (int i = 0; i < newSize; i++) {
        m1[i] = (int*)malloc(newSize * sizeof(int));
        m2[i] = (int*)malloc(newSize * sizeof(int));
        m3[i] = (int*)malloc(newSize * sizeof(int));
        m4[i] = (int*)malloc(newSize * sizeof(int));
        m5[i] = (int*)malloc(newSize * sizeof(int));
        m6[i] = (int*)malloc(newSize * sizeof(int));
        m7[i] = (int*)malloc(newSize * sizeof(int));
    }

    // Calculate the Strassen products (similar to previous code)
    // ...

    // Free memory for intermediate matrices and sub-matrices
    for (int i = 0; i < newSize; i++) {
        free(a11[i]); free(a12[i]); free(a21[i]); free(a22[i]);
        free(b11[i]); free(b12[i]); free(b21[i]); free(b22[i]);
        free(m1[i]); free(m2[i]); free(m3[i]); free(m4[i]);
        free(m5[i]); free(m6[i]); free(m7[i]);
    }
    free(a11); free(a12); free(a21); free(a22);
    free(b11); free(b12); free(b21); free(b22);
    free(m1); free(m2); free(m3); free(m4);
    free(m5); free(m6); free(m7);
}

int main() {
    int size;

    printf("Enter the size of the matrix: ");
    scanf("%d", &size);

    // Dynamically allocate matrices
    int** mat1 = (int**)malloc(size * sizeof(int*));
    int** mat2 = (int**)malloc(size * sizeof(int*));
    int** result = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        mat1[i] = (int*)malloc(size * sizeof(int));
        mat2[i] = (int*)malloc(size * sizeof(int));
        result[i] = (int*)malloc(size * sizeof(int));
    }

    // Input the matrix elements
    printf("Enter the elements of matrix A:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter the elements of matrix B:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    // Perform brute force matrix multiplication
    brute_force_matrix_multiply(mat1, mat2, size, result);

    printf("Result of matrix multiplication:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free memory for matrices
    for (int i = 0; i < size; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }
    free(mat1);
    free(mat2);
    free(result);

    return 0;
}
