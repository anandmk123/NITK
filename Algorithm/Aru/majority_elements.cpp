#include <cmath>
#include <iostream>
#include <limits>

using namespace std;
int Inf = -std::numeric_limits<int>().infinity();
// counts frequency of element k in the array in linear time
int frequency(int arr[], int low, int high, int k) {
  int count = 0;
  for (int i = low; i <= high; i++) {
    if (arr[i] == k) {
      count++;
    }
  }
  return count;
}

// divide the array into subarrays of equal size and find majority element
// recursively.
// T(n) = 2T(n) + O(n)
// Time complexity : O(n log n)
int majority_element(int arr[], int low, int high) {

  // base case
  if (high > low) {
    int n = (high - low) + 1;
    int mid = (low + high) / 2;

    // recursively find the majority element in left and right sub arrays
    int leftMajority = majority_element(arr, low, mid);
    int rightMajority = majority_element(arr, mid + 1, high);

    if (leftMajority == rightMajority) {
      return leftMajority;
    }

    int lcount = 0, rcount = 0;

    if (leftMajority != Inf) {
      // find the count of left majority
      lcount = frequency(arr, low, high, leftMajority);
    }

    if (rightMajority != Inf) {
      // find the count of right majority
      rcount = frequency(arr, low, high, rightMajority);
    }

    // return majority element
    if (lcount > n / 2)
      return leftMajority;
    else if (rcount > n / 2)
      return rightMajority;
    else
      return Inf;
  }

  // base case
  return arr[low];
}


// This use divide and conquer to find the majority element.
// Lemma : If x is majority element of atmost n/2 pairs of same element in array A, then it is also
// the majority element of A 
// T(n) = T(n/2) + O(n)
// Time complexity : O(n)
int majority_element_linear(int arr[], int low, int high) {
  int n = (high - low) + 1;

  // if the pair are same return the element, else it is not majority
  if (n == 2) {
    if (arr[low] == arr[high]) {
      return arr[low];
    } else {
      return Inf;
    }
  }

  // if n is odd
  if (n == 1) {
    return arr[low];
  }

  // create a temp array to hold the pairs of same elements
  // O(n)
  int temp[n / 2];
  int n1 = 0;
  for (int i = low, j = 0; i < high; i++, j++) {
    if (arr[i] == arr[i + 1]) {
      temp[j] = arr[i];
      n1++;
    }
  }

  // find the majority in the atmost n/2 elements
  return majority_element_linear(temp, 0, n1 - 1);
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

  // use divide and conquer
  cout << "Majority element in O(n logn) : " << endl;
  int majorityElement = majority_element(arr, 0, n - 1);

  if (majorityElement == Inf) {
    cout << "No majority element\n";
  } else {
    cout << "Majority element : " << majorityElement << endl;
  }

  // optimized divide and conquer
  cout << "Majority element in O(n) : " << endl;
  int majorityElementLin = majority_element_linear(arr, 0, n - 1);
  if (majorityElementLin == Inf) {
    cout << "No majority element\n";
  } else {
    int majorityCount = frequency(arr, 0, n - 1, majorityElementLin);
    if (majorityCount > n / 2) {
      cout << "Majority element : " << majorityElementLin << endl;
    } else {
      cout << "No majority element\n";
    }
  }

  return 0;
}