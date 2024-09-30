#include <iostream>
#include <unordered_map>

using namespace std;

// sort the array in decreasing order while counting the smallest numbers in the
// right
// Time complexity : O(n)
void countAndMerge(int arr[], int result[], unordered_map<int, int> idx,
                   int low, int mid, int high) {
  int n = high - low + 1;
  int b[n];
  int bcount = 0, l = low, r = mid + 1;

  while (l <= mid && r <= high) {
    if (arr[l] > arr[r]) {
      // since the subarrays are sorted in decreasing order, the elements
      // after r are also smallest elements to the element at index l
      result[idx[arr[l]]] += ((high - r) + 1);
      b[bcount++] = arr[l++];
    } else {
      b[bcount++] = arr[r++];
    }
  }

  // add remaining elements to the 
  while (l <= mid) {
    b[bcount++] = arr[l++];
  }

  while (r <= high) {
    b[bcount++] = arr[r++];
  }

  for (int i = 0; i < n; i++) {
    arr[low + i] = b[i];
  }
}

// merge sort - divide the current array into two equal halves recursively and
// merge while counting the smallest elements. unordered map is used to store
// the original idx of the elements of the array.
// T(n) = 2T(n/2) + O(n)
// Time complexity :  O(n logn)
void smallestElementsInRight(int arr[], int result[],
                             unordered_map<int, int> idx, int low, int high) {
  if (high > low) {
    int mid = (low + high) / 2;
    smallestElementsInRight(arr, result, idx, low, mid);
    smallestElementsInRight(arr, result, idx, mid + 1, high);
    countAndMerge(arr, result, idx, low, mid, high);
  }
}

int main() {

  int n;
  cout << "Enter the size of the array : ";
  cin >> n;

  int arr[n], result[n];

  unordered_map<int, int> idx;

  cout << "Enter the elements of the array : ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    result[i] = 0;
    idx[arr[i]] = i;
  }

  smallestElementsInRight(arr, result, idx, 0, n - 1);

  cout << "Smallest elements in right are : ";
  for (int i = 0; i < n; i++) {
    cout << result[i] << ", ";
  }

  return 0;
}