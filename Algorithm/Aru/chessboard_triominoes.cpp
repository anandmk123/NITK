#include <iostream>
#define MAX 256

using namespace std;

int tile = 0;

// this method use divide and conquer approach to recursively place tile in four
// quadrants with half the board size. complexity : T(n) = 4T(n/2) + O(1)
void placeTriominoes(int board[MAX][MAX], int r, int c, int currentsize,
                     int missingrow, int missingcolumn) {
  // base case 2x2 board
  if (currentsize == 2) {
    tile++;
    for (int i = 0; i < currentsize; i++) {
      for (int j = 0; j < currentsize; j++) {
        // If the current square is not missing sqaure or occupied square by
        // other tile place the L-Triomino. 3 sqaures will be filled avoiding
        // the missing or occupied square.
        if (r + i != missingrow && c + j != missingcolumn) {
          board[r + i][c + j] = tile;
        }
      }
    }
    return;
  }

  int t = tile++;
  // divide the board into 4 quadrants
  int n = currentsize / 2;

  // check each quadrant and place the L-triomino

  // Top-left quadrant
  if (missingrow < r + n && missingcolumn < c + n) {
    // The missing square is in this quadrant
    placeTriominoes(board, r, c, n, missingrow, missingcolumn);
  } else {
    // No missing square is not in this quadrant.
    // so place L-shaped triomino in bottom right of this quadrant.
    // Consider this square as missing sqaure, so that it won't be filled by
    // other tile in this quadrant
    board[r + n - 1][c + n - 1] = t;
    placeTriominoes(board, r, c, n, r + n - 1, c + n - 1);
  }

  // Top-right quadrant
  if (missingrow < r + n && missingcolumn >= c + n) {
    // The missing square is in this quadrant
    placeTriominoes(board, r, c + n, n, missingrow, missingcolumn);
  } else {
    // Missing square is not in this quadrant.
    // so place L-shaped triomino in bottom left of this quadrant.
    // Consider this square as missing sqaure, so that it won't be filled by
    // other tile in this quadrant
    board[r + n - 1][c + n] = t;
    placeTriominoes(board, r, c + n, n, r + n - 1, c + n);
  }

  // Bottom-left quadrant
  if (missingrow >= r + n && missingcolumn < c + n) {
    // The missing square is in this quadrant
    placeTriominoes(board, r + n, c, n, missingrow, missingcolumn);

  } else {
    // Missing square is not in this quadrant.
    // so place L-shaped triomino in top right of this quadrant.
    // Consider this square as missing sqaure, so that it won't be filled by
    // other tile in this quadrant
    board[r + n][c + n - 1] = t;
    placeTriominoes(board, r + n, c, n, r + n, c + n - 1);
  }

  // Bottom-right quadrant
  if (missingrow >= r + n && missingcolumn >= c + n) {
    // The missing square is in this quadrant
    placeTriominoes(board, r + n, c + n, n, missingrow, missingcolumn);
  } else {
    // Missing square is not in this quadrant.
    // so place L-shaped triomino in top left of this quadrant.
    // Consider this square as missing sqaure, so that it won't be filled by
    // other tile in this quadrant
    board[r + n][c + n] = t;
    placeTriominoes(board, r + n, c + n, n, r + n, c + n);
  }
}

int main() {
  int n, r, c;
  int board[MAX][MAX];

  cout << "Enter the size of the chess board (2^i) : ";
  cin >> n;
  cout << "Enter the index of missing square (row and column) : ";
  cin >> r >> c;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }

  // putting -1 in place missing square
  board[r][c] = -1;

  placeTriominoes(board, 0, 0, n, r, c);

  // print the board
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << "\t";
    }
    cout << "\n";
  }

  return 0;
}