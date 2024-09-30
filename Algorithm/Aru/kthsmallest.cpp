#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

int quickselect(int arr[], int k, int low, int high);

// quick sorting
int median_idx(int *arr, int a, int b) {
  int mid = (a + b) / 2;
  if ((arr[a] < arr[mid] && arr[mid] < arr[b]) ||
      (arr[b] < arr[mid] && arr[mid] < arr[a])) {
    return mid;
  }

  if ((arr[mid] < arr[a] && arr[a] < arr[b]) ||
      (arr[b] < arr[a] && arr[a] < arr[mid])) {
    return a;
  }

  if ((arr[mid] < arr[b] && arr[b] < arr[a]) ||
      (arr[a] < arr[b] && arr[b] < arr[mid])) {
    return b;
  }

  return mid;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// partition algorithm in linear time O(n)
int partition(int arr[], int pivot, int low, int high) {
  int i = low, j = low, k = high;
  while (j <= k) {
    if (arr[j] < pivot) {
      swap(&arr[i], &arr[j]);
      i++;
      j++;
    } else if (arr[j] > pivot) {
      swap(&arr[k], &arr[j]);
      k--;
    } else {
      j++;
    }
  }
  return i;
}

int partition_median(int arr[], int low, int high) {
  int idx = median_idx(arr, low, high);
  int temp = arr[low];
  arr[low] = arr[idx];
  arr[idx] = temp;

  return partition(arr, arr[idx], low, high);
}

void quick_sort(int *arr, int low, int high) {
  if (low < high) {
    int p = partition_median(arr, low, high);
    quick_sort(arr, low, p - 1);
    quick_sort(arr, p + 1, high);
  }
}

// find the medians of groups of five elements in linear time O(n)
int median_of_medians(int arr[], int low, int high) {
  int n = high - low + 1;
  int groupcount = ceil((float)n / 5); // no. of groups
  int medians_arr[groupcount];
  // divide the array into groups of 5
  // sort the group and store the middle element (median)
  for (int i = 0; i < n / 5; i++) {
    int start = low + (i * 5);
    int end = start + 4;
    int mid = (start + end) / 2;
    quick_sort(arr, start, end);
    medians_arr[i] = arr[mid];
  }

  // if there are groups with lesser than 5 elements
  // sort and add the middle element
  int remaining = n % 5;
  if (remaining != 0) {
    int start = low + (n - remaining);
    int end = high;
    int mid = (start + end) / 2;
    quick_sort(arr, start, end);
    medians_arr[groupcount - 1] = arr[mid];
  }
  // if size of medians is less than 5, just sort and return the result
  if (groupcount <= 5) {
    quick_sort(medians_arr, 0, groupcount - 1);
    return medians_arr[groupcount / 2];
  } else { // else find the n/2 th element (median) in linear time using quick
           // select
    return quickselect(medians_arr, groupcount / 2, 0, groupcount - 1);
  }
}

// Use divide and conquer approach
// T(n) = T(n/5) + T(7n/10) + O(n)
// Time complexity : O(n)
int quickselect(int arr[], int k, int low, int high) {
  int n = high - low + 1;

  // find median of medians
  int pivot = median_of_medians(arr, low, high);

  // partition the array on median of medians
  int mid = partition(arr, pivot, low, high);

  // size of left sub array
  int lsize = mid - low;

  if (k < lsize + 1) { // kth smallest element is in left partition
    // find kth position element in left subarray
    return quickselect(arr, k, low, mid - 1);
  } else if (k > lsize + 1) { // kth smallest element is in right partition
    // find position at k minus size of left sub array  and 1 for pivot element
    // in right subarray
    return quickselect(arr, k - (lsize + 1), mid + 1, high);
  } else {
    return pivot;
  }
}

int main() {
  int n, k;
  cout << "Enter the size of the array : ";
  cin >> n;

  int arr[n];

  cout << "Enter the elements of the array : ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  cout << "Enter k : ";
  cin >> k;

  cout << "kth smallest element in the array is "
       << quickselect(arr, k, 0, n - 1) << endl;
  return 0;
}
