#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MAX 100

// Brute force approach for matrix multiplication
void brute_force_matrix_multiply(int matA[MAX][MAX], int matB[MAX][MAX], int size, int result[MAX][MAX]) {
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
void strassen_base_case(int matA[MAX][MAX], int matB[MAX][MAX], int result[MAX][MAX]) {
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
void add_matrices(int matA[MAX][MAX], int matB[MAX][MAX], int size, int result[MAX][MAX]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matA[i][j] + matB[i][j];
        }
    }
}

// Utility function to subtract two matrices
void subtract_matrices(int matA[MAX][MAX], int matB[MAX][MAX], int size, int result[MAX][MAX]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matA[i][j] - matB[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassen_matrix_multiply(int matA[MAX][MAX], int matB[MAX][MAX], int size, int result[MAX][MAX]) {
    if (size == 2) {
        strassen_base_case(matA, matB, result);
        return;
    }

    // Split the current matrix into 4 sub-matrices
    int newSize = size / 2;
    int a11[MAX][MAX], a12[MAX][MAX], a21[MAX][MAX], a22[MAX][MAX];
    int b11[MAX][MAX], b12[MAX][MAX], b21[MAX][MAX], b22[MAX][MAX];
    
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

    int m1[MAX][MAX], m2[MAX][MAX], m3[MAX][MAX], m4[MAX][MAX];
    int m5[MAX][MAX], m6[MAX][MAX], m7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Compute the Strassen's products
    subtract_matrices(b12, b22, newSize, temp1);
    strassen_matrix_multiply(a11, temp1, newSize, m1);

    add_matrices(a11, a12, newSize, temp1);
    strassen_matrix_multiply(temp1, b22, newSize, m2);

    add_matrices(a21, a22, newSize, temp1);
    strassen_matrix_multiply(temp1, b11, newSize, m3);

    subtract_matrices(b21, b11, newSize, temp1);
    strassen_matrix_multiply(a22, temp1, newSize, m4);

    add_matrices(a11, a22, newSize, temp1);
    add_matrices(b11, b22, newSize, temp2);
    strassen_matrix_multiply(temp1, temp2, newSize, m5);

    subtract_matrices(a12, a22, newSize, temp1);
    add_matrices(b21, b22, newSize, temp2);
    strassen_matrix_multiply(temp1, temp2, newSize, m6);

    subtract_matrices(a11, a21, newSize, temp1);
    add_matrices(b11, b12, newSize, temp2);
    strassen_matrix_multiply(temp1, temp2, newSize, m7);

    // Combine the results into the final result matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            result[i][j] = m5[i][j] + m4[i][j] - m2[i][j] + m6[i][j];
            result[i + newSize][j] = m3[i][j] + m4[i][j];
            result[i][j + newSize] = m1[i][j] + m2[i][j];
            result[i + newSize][j + newSize] = m1[i][j] + m5[i][j] - m3[i][j] - m7[i][j];
        }
    }
}

int main() {
    int size, mat1[MAX][MAX], mat2[MAX][MAX], result[MAX][MAX];

    printf("Enter the size of the matrix: ");
    scanf("%d", &size);

    // Initialize matrices to zero
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mat1[i][j] = 0;
            mat2[i][j] = 0;
            result[i][j] = 0;
        }
    }

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

    struct timeval tv1, tv2,tv3,tv4;

    printf("Brute force matrix multiplication:\n");
    gettimeofday(&tv1, NULL);
    brute_force_matrix_multiply(mat1, mat2, size, result);
    gettimeofday(&tv2, NULL);
    double executiontime = (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
                        (double)(tv2.tv_sec - tv1.tv_sec);
    executiontime=executiontime*1000;
    printf("Execution time (millisec): %lf\n", executiontime);
    printf("Output:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("Strassen's algorithm for matrix multiplication:\n");
    gettimeofday(&tv3, NULL);
    strassen_matrix_multiply(mat1, mat2, size, result);
    gettimeofday(&tv4, NULL);
    double executiontime2 = (double)(tv4.tv_usec - tv3.tv_usec) / 1000000 +
                        (double)(tv4.tv_sec - tv3.tv_sec);
    executiontime=executiontime*1000;
    printf("Execution time (millisec): %lf\n", executiontime2);

    printf("Output:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
