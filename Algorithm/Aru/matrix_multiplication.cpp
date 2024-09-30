#include <chrono>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define MAX 100
using namespace std;

// brute force approac

void brute_matrix_mul(int a[MAX][MAX], int b[MAX][MAX], int n,
                      int c[MAX][MAX]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      c[i][j] = 0;
      for (int k = 1; k <= n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// Strassen algorithm

// base case when the matrix is 4x4, use simplified calculations to find the
// result
void basecase(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX]) {
  int a1 = a[1][1], b1 = a[1][2], c1 = a[2][1], d1 = a[2][2];
  int e1 = b[1][1], f1 = b[1][2], g1 = b[2][1], h1 = b[2][2];

  int p1 = a1 * (f1 - h1);
  int p2 = (a1 + b1) * h1;
  int p3 = (c1 + d1) * e1;
  int p4 = d1 * (g1 - e1);
  int p5 = (a1 + d1) * (e1 + h1);
  int p6 = (b1 - d1) * (g1 + h1);
  int p7 = (a1 - c1) * (e1 + f1);

  c[1][1] = a1 * e1 + b1 * g1;
  c[1][2] = a1 * f1 + b1 * h1;
  c[2][1] = c1 * e1 + d1 * g1;
  c[2][2] = c1 * f1 + d1 * h1;
}

// utility function to add the matrix
void add(int a[MAX][MAX], int b[MAX][MAX], int n, int c[MAX][MAX]) {
  int i = 1, j = 1;
  while (i <= n) {
    for (j = 1; j <= n; j++) {
      c[i][j] = a[i][j] + b[i][j];
    }
    i++;
  }
  return;
}

// utility function to subtract the matrix
void subtract(int a[MAX][MAX], int b[MAX][MAX], int n, int c[MAX][MAX]) {
  int i = 1, j = 1;
  for (i = 1; i <= n; i++) {
    while (j <= n) {
      c[i][j] = a[i][j] - b[i][j];
      j++;
    }
    j = 1;
  }
  return;
}

// Strassen algorithm is based on divide and conquer approach
// works only for matrix of size 2^k
// T(n) = 7T(n/2) + O(n^2)
// Time complexity O(n^2.81)
void strassenalgo(int a[MAX][MAX], int b[MAX][MAX], int n, int c[MAX][MAX]) {
  int i, j;

  // if the
  if (n == 2) {
    basecase(a, b, c);
    return;
  }

  else {

    // split the current matrix into 4 matrixs (top left, top right, bottom
    // left, bottom right)
    int a11[MAX][MAX];
    int a12[MAX][MAX];
    int a21[MAX][MAX];
    int a22[MAX][MAX];
    int b11[MAX][MAX];
    int b12[MAX][MAX];
    int b21[MAX][MAX];
    int b22[MAX][MAX];

    i = 1;
    j = 1;
    while (i <= n / 2) {
      while (j <= n / 2) {

        a11[i][j] = a[i][j];
        b11[i][j] = b[i][j];

        a21[i][j] = a[i + (n / 2)][j];
        b21[i][j] = b[i + (n / 2)][j];

        a12[i][j] = a[i][j + (n / 2)];
        b12[i][j] = b[i][j + (n / 2)];

        a22[i][j] = a[i + (n / 2)][j + (n / 2)];
        b22[i][j] = b[i + (n / 2)][j + (n / 2)];

        j++;
      }
      i++;
      j = 1;
    }

    int m1[MAX][MAX];
    int m2[MAX][MAX];
    int m3[MAX][MAX];
    int m4[MAX][MAX];
    int m5[MAX][MAX];
    int m6[MAX][MAX];
    int m7[MAX][MAX];

    int temp1[MAX][MAX];
    int temp2[MAX][MAX];

    // recursively compute the simplified calculation

    // m1 = a11 * (b12 - b22)
    subtract(b12, b22, n / 2, temp1);
    strassenalgo(a11, temp1, n / 2, m1);

    // m2 = (a11 + a12) * b22
    add(a11, a12, n / 2, temp1);
    strassenalgo(temp1, b22, n / 2, m2);

    // m3 =(a21 + a22) * b11
    add(a21, a22, n / 2, temp1);
    strassenalgo(temp1, b11, n / 2, m3);

    // m4 = a22 * (b21 - b11)
    subtract(b21, b11, n / 2, temp1);
    strassenalgo(a22, temp1, n / 2, m4);

    // m5 = (a11 + a22) * (b11 + b22)
    add(a11, a22, n / 2, temp1);
    add(b11, b22, n / 2, temp2);
    strassenalgo(temp1, temp2, n / 2, m5);

    // m6 = (a12 - a22) * (b21 + b22)
    subtract(a12, a22, n / 2, temp1);
    add(b21, b22, n / 2, temp2);
    strassenalgo(temp1, temp2, n / 2, m6);
    
    // m7 = (a11 - a21) * (b11 + b12)
    subtract(a11, a21, n / 2, temp1);
    add(b11, b12, n / 2, temp2);
    strassenalgo(temp1, temp2, n / 2, m7);

    // c11 = m5 + m4 + m2 + m6
    // c21 = m3 + m4
    // c12 = m1 + m2
    // c22 = m1 + m5 + m3 + m7
    for (i = 1; i <= n / 2; i++) {
      for (j = 1; j <= n / 2; j++) {

        c[i][j] = m5[i][j] + m4[i][j] - m2[i][j] + m6[i][j];
        c[i + (n / 2)][j] = m3[i][j] + m4[i][j];
        c[i][j + (n / 2)] = m1[i][j] + m2[i][j];
        c[i + (n / 2)][j + (n / 2)] = m1[i][j] + m5[i][j] - m3[i][j] - m7[i][j];
      }
    }
  }
  return;
}

int main() {

  int t, n, i, j, mat1[MAX][MAX], mat2[MAX][MAX], result[MAX][MAX];

  cout << "Enter the size of the matrix : ";
  cin >> n;
  for (i = 1; i < MAX; i++) {
    for (j = 1; j < MAX; j++) {
      mat1[i][j] = 0;
      mat2[i][j] = 0;
      result[i][j] = 0;
    }
  }

  cout << "Enter the elements of the matrix A : \n";
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cin >> mat1[i][j];
    }
  }
  cout << "Enter the elements of the matrix B : \n";
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cin >> mat2[i][j];
    }
  }

  cout << "Brute force matrix multiplication : " << endl;
  auto start = chrono::high_resolution_clock::now();
  brute_matrix_mul(mat1, mat2, n, result);
  auto end = chrono::high_resolution_clock::now();
  auto dur = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Execution time (micro sec) : " << dur.count() << endl;
  cout << "Output" << endl;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cout << result[i][j] << " ";
    }
    cout << "\n";
  }

  cout << "Strassen's algorithm for matrix multiplication : " << endl;
  start = chrono::high_resolution_clock::now();
  strassenalgo(mat1, mat2, n, result);
  end = chrono::high_resolution_clock::now();
  auto durs = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Execution time (micro sec) : " << durs.count() << endl;
  cout << "Output" << endl;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cout << result[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}