#include <cmath>
#include <cstdlib>
#include <iostream>
#define MAX 128

using namespace std;

// count elements lesser than or equal to middle value
// complexity : O(max(m,n))
int count(int mat[MAX][MAX], int mid, int m, int n) {
  int count = 0;
  // bottom-left corner of the matrix
  int i = m - 1;
  int j = 0;

  while (i >= 0 && j < n) {
    // If the current element is lesser than or equal to mid, go to the next
    // column
    if (mat[i][j] <= mid) {
      count += (i + 1);
      ++j;
    } else {
      --i; //  If the current element is greater than mid, go to the top row
    }
  }

  return count;
}

// Binary search approach is used to find the kth element.
// Time complexity : O(n logn)
int kthsmallest_matrix(int mat[MAX][MAX], int k, int m, int n) {

  int low = mat[0][0];
  int high = mat[m - 1][n - 1];

  while (low < high) {
    // mid is the median of smallest and largest element in the matrix
    int mid = (low + high) / 2;

    // count the elements lesser than or equal to mid
    // If the no. elements are lesser than k, then the required element is
    // left subpart of the sorted element, or otherwise in the right subpart. 
    if (count(mat, mid, m, n) <= k) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }

  return low;
}

int main() {
  int m, n, k;
  cout << "Enter the size of the row and column: ";
  cin >> m;
  cin >> n;

  int mat[MAX][MAX];

  cout << "Enter the elements of the matrix (sorted order) : \n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> mat[i][j];
    }
  }

  cout << "Enter k : ";
  cin >> k;

  cout << "kth smallest element in the array is "
       << kthsmallest_matrix(mat, k - 1, m, n) << endl;
  return 0;
}
