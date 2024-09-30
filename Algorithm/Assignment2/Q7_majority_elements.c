#include <stdio.h>

// Function to count occurrences of a candidate in the array
int countOccurrences(int arr[], int size, int candidate) {
    int count = 0; // Initialize count to zero
    for (int i = 0; i < size; i++) {
        // Increment count if the candidate matches the current element
        if (arr[i] == candidate) {
            count++;
        }
    }
    return count; // Return the total count of occurrences
}

// Function to find the majority element using divide-and-conquer (O(n log n))
int majorityElement(int arr[], int left, int right) {
    // Base case: if the subarray has one element, return that element
    if (left == right) {
        return arr[left];
    }

    // Find the mid-point of the current subarray
    int mid = (left + right) / 2;

    // Recursively find the majority elements in the left and right halves
    int m1 = majorityElement(arr, left, mid);
    int m2 = majorityElement(arr, mid + 1, right);

    // If both halves return the same majority element, return it
    if (m1 == m2) {
        return m1;
    }

    // Count occurrences of m1 and m2 in the whole array
    int count1 = countOccurrences(arr, right + 1, m1);
    int count2 = countOccurrences(arr, right + 1, m2);

    // Check if m1 is the majority element
    if (count1 > (right - left + 1) / 2) {
        return m1;
    }

    // Check if m2 is the majority element
    if (count2 > (right - left + 1) / 2) {
        return m2;
    }

    return -1; // No majority element found
}

// Function to find the majority element using the pairing method (linear time)
int majorityElementLinear(int arr[], int size) {
    int candidate = -1; // Variable to store potential majority candidate
    int count = 0;      // Count to keep track of the current candidate's occurrences

    // Pair up elements and eliminate non-majority candidates
    for (int i = 0; i < size; i++) {
        // If count is zero, update candidate to current element
        if (count == 0) {
            candidate = arr[i];
            count = 1; // Start counting occurrences of this candidate
        } 
        // If current element is the same as candidate, increment count
        else if (arr[i] == candidate) {
            count++;
        } 
        // If current element is different, decrement count
        else {
            count--;
        }
    }

    // Verify the candidate's majority status by counting its occurrences
    count = 0; // Reset count for verification
    for (int i = 0; i < size; i++) {
        // Increment count if the current element matches the candidate
        if (arr[i] == candidate) {
            count++;
        }
    }

    // Check if the candidate appears more than half the time
    if (count > size / 2) {
        return candidate; // Return the candidate if it is the majority element
    }

    return -1; // No majority element found
}

int main() {
    int size;

    // Prompt the user for the number of elements in the array
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    int arr[size]; // Declare the array with the specified size

    // Prompt the user to enter the elements of the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]); // Read each element into the array
    }

    // Find the majority element using both algorithms
    int majority1 = majorityElement(arr, 0, size - 1); // O(n log n) method
    int majority2 = majorityElementLinear(arr, size);  // Linear-time method

    // Output the results from both algorithms
    if (majority1 != -1) {
        printf("The majority element (O(n log n)) is: %d\n", majority1);
    } else {
        printf("No majority element found using O(n log n) method.\n");
    }

    if (majority2 != -1) {
        printf("The majority element (Linear-time) is: %d\n", majority2);
    } else {
        printf("No majority element found using Linear-time method.\n");
    }

    return 0;
}
