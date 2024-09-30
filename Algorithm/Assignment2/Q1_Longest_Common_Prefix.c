#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * This function implements a divide-and-conquer approach to find the longest common prefix
 * in an array of strings.
 * Time complexity is O(m log n), where 'm' is the length of the longest string
 * and 'n' is the number of strings in the array.
 */
char* findLongestCommonPrefix(char* strings[], int start, int end) {
    // If more than one string is present, recursively divide the array
    if (end > start) {
        /**
         * Divide the array into two halves by calculating the midpoint.
         */
        int mid = (start + end) / 2;

        // Find the longest common prefix in the left and right halves
        char* prefixLeft = findLongestCommonPrefix(strings, start, mid);
        char* prefixRight = findLongestCommonPrefix(strings, mid + 1, end);

        /**
         * Compare the two prefixes and return the common part between them.
         */
        int i = 0, limit = (strlen(prefixLeft) < strlen(prefixRight)) ? strlen(prefixLeft) : strlen(prefixRight);
        while (i < limit && prefixLeft[i] == prefixRight[i])
            i++;

        // Store the result (common prefix) in a static buffer
        static char result[100];
        strncpy(result, prefixLeft, i);
        result[i] = '\0';
        return result;
    }

    // Base case: return the string when only one string is left
    return strings[start];
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
    printf("Longest Common Prefix: %s\n", findLongestCommonPrefix(strings, 0, numStrings - 1));

    // Free allocated memory for each string
    for (i = 0; i < numStrings; i++) {
        free(strings[i]);
    }

    return 0;
}
