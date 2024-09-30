#include <iostream>

using namespace std;

// merge the sub arrays while counting the inversions
// Time complexity : O(n)
int countAndMerge(int arr[], int left, int mid, int right) {
  int n = right - left + 1;
  int b[n];
  int bcount = 0, lcount = left, rcount = mid + 1;
  int lsize = mid - left + 1;
  int inversions = 0;

  // merge the array in sorted order
  while (lcount <= mid && rcount <= right) {
    if (arr[lcount] <= arr[rcount]) {
      b[bcount++] = arr[lcount++];
    } else {
      b[bcount++] = arr[rcount++];
      inversions +=
          (lsize -
           (lcount -
            left)); // inversion =  size of left array -
                    // current index of left array
                    // (i.e) all elements in right of lcount in left subarray
    }
  }
  // add the remaining elements
  while (lcount <= mid) {
    b[bcount++] = arr[lcount++];
  }

  while (rcount <= right) {
    b[bcount++] = arr[rcount++];
  }

  // copy back to the array
  for (int i = 0; i < n; i++) {
    arr[left + i] = b[i];
  }

  return inversions;
}

/**
This method uses divide and conquer approach, in this recursion the array is
divided into two sub arrays of equal size. When the subarrays are merged the
inversions are counted and returned
 */
 // T(n) = 2T(n/2) + O(n)
 // Time complexity : O(n log n)
int countInversion(int arr[], int left, int right) {
  int inversions = 0;
  if (left < right) {
    int mid = (left + right) / 2;
    inversions += countInversion(arr, left, mid);
    inversions += countInversion(arr, mid + 1, right);
    inversions += countAndMerge(arr, left, mid, right);
  }
  return inversions;
}

int main() {
  int n;
  cout << "Enter the size of the array : ";
  cin >> n;

  int arr[n];

  cout << "Enter the elements of the array : ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  cout << "No. of inversions : " << countInversion(arr, 0, n - 1) << endl;

  return 0;
}