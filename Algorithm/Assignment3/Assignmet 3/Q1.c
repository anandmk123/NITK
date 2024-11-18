#include <stdio.h>
#include <stdlib.h>

// Function prototypes for merge sort and pair matching
void merge_sort(int* arr, int left, int right);
void merge(int* arr, int left, int mid, int right);
int calculate_max_pairs(int* men, int num_men, int* women, int num_women, int** matched_pairs);

// Merge two sorted halves of an array
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Allocate memory for temporary arrays
    int* left_arr = (int*)malloc(n1 * sizeof(int));
    int* right_arr = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left; // i, j for left/right arrays; k for original array
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of left_arr
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy any remaining elements of right_arr
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(left_arr);
    free(right_arr);
}

// Recursive function to sort an array using merge sort
void merge_sort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calculate the midpoint

        // Recursively sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to calculate the maximum number of dancing couples and track matched pairs
int calculate_max_pairs(int* men, int num_men, int* women, int num_women, int** matched_pairs) {
    // Sort men's and women's heights using merge sort
    merge_sort(men, 0, num_men - 1);
    merge_sort(women, 0, num_women - 1);

    int i = 0; // Index for men
    int j = 0; // Index for women
    int matches = 0; // Count of valid pairs

    // Allocate memory to store matched pairs
    *matched_pairs = (int*)malloc(2 * (num_men + num_women) * sizeof(int)); // Each pair has 2 elements (man, woman)

    // Iterate through both lists to find matching pairs
    while (i < num_men && j < num_women) {
        if (men[i] < women[j]) {
            // Man is shorter than the woman; move to the next man
            ++i;
        } else if (men[i] > women[j] + 3) {
            // Man is more than 3 inches taller than the woman; move to the next woman
            ++j;
        } else {
            // Valid couple found
            (*matched_pairs)[2 * matches] = men[i];
            (*matched_pairs)[2 * matches + 1] = women[j];
            ++matches; // Increment match count
            ++i; // Move to the next man
            ++j; // Move to the next woman
        }
    }

    return matches; // Return the total number of matches
}

// Function to run a test case and print the results
void run_test_case(const char* test_name, int* men, int num_men, int* women, int num_women) {
    int* matched_pairs; // Pointer to store matched pairs
    printf("%s:\n", test_name);

    // Calculate the maximum number of pairs and retrieve matched pairs
    int max_pairs = calculate_max_pairs(men, num_men, women, num_women, &matched_pairs);

    // Print matched pairs
    for (int i = 0; i < max_pairs; ++i) {
        printf("Man: %d, Woman: %d\n", matched_pairs[2 * i], matched_pairs[2 * i + 1]);
    }
    printf("Maximum number of dancing couples: %d\n\n", max_pairs);

    // Free allocated memory for matched pairs
    free(matched_pairs);
}

int main() {
    // Example Test Case 1
    int men1[] = {60, 72, 75, 69, 66}; // Array of men's heights
    int women1[] = {65, 68, 70, 71, 73}; // Array of women's heights
    run_test_case("Test Case 1", men1, 5, women1, 5);

    // Example Test Case 2
    int men2[] = {67, 62, 64, 70};
    int women2[] = {60, 65, 63, 69};
    run_test_case("Test Case 2", men2, 4, women2, 4);

    // Example Test Case 3
    int men3[] = {72, 68, 74};
    int women3[] = {60, 63, 66};
    run_test_case("Test Case 3", men3, 3, women3, 3);

    return 0; // End of program
}
