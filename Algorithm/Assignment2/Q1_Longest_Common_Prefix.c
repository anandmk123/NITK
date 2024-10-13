#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * This function compares two strings and returns their longest common prefix.
 */
char* commonPrefix(char* left, char* right) {
    int i = 0;
    int limit = (strlen(left) < strlen(right)) ? strlen(left) : strlen(right);

    // Compare the two strings and find the common prefix
    while (i < limit && left[i] == right[i])
        i++;

    // Allocate memory for the result and store the common prefix
    char* result = (char*)malloc((i + 1) * sizeof(char)); // +1 for null terminator
    strncpy(result, left, i);
    result[i] = '\0';

    return result;
}

/**
 * The function implements a divide-and-conquer approach to find the longest common prefix
 * in an array of strings.
 * Time complexity is O(m log n), where 'm' is the length of the longest string
 * and 'n' is the number of strings in the array.
 */
char* findLongestCommonPrefix(char* strings[], int start, int end) {
    // Base case: if only one string, return it as the prefix
    if (start == end) {
        return strings[start];
    }

    // Divide the array into two halves
    int mid = (start + end) / 2;

    // Recursively find the longest common prefix in both halves
    char* prefixLeft = findLongestCommonPrefix(strings, start, mid);
    char* prefixRight = findLongestCommonPrefix(strings, mid + 1, end);

    // Find the common prefix between the two halves
    char* common = commonPrefix(prefixLeft, prefixRight);

    return common;
}

int main() {
    int numStrings, i;

    // Ask the user to input the number of strings
    printf("Enter the number of strings: ");
    scanf("%d", &numStrings);

    // Dynamically allocate memory for the array of strings
    char* strings[numStrings];
    char inputString[100];

    // Input strings from the user
    printf("Enter the strings:\n");
    for (i = 0; i < numStrings; i++) {
        scanf("%s", inputString);

        // Allocate memory for each string and copy the input to the allocated space
        strings[i] = (char*)malloc((strlen(inputString) + 1) * sizeof(char));
        strcpy(strings[i], inputString);
    }

    // Find and print the longest common prefix
    char* result = findLongestCommonPrefix(strings, 0, numStrings - 1);

    // Handle the case of no common prefix
    if (strlen(result) == 0) {
        printf("No common prefix exists.\n");
    } else {
        printf("Longest Common Prefix: %s\n", result);
    }

    // Free allocated memory for each string and the result
    free(result);
    for (i = 0; i < numStrings; i++) {
        free(strings[i]);
    }

    return 0;
}
