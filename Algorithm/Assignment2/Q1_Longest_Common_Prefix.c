#include <stdio.h>
#include <string.h>

// Function to find the longest common prefix using a greedy approach
void commonPrefix(char strs[][100], int n, char *prefix) {
    if (n == 0) {
        strcpy(prefix, "");
        return;
    }

    // Assume the first string is the common prefix
    strcpy(prefix, strs[0]);

    // Traverse all strings
    for (int i = 1; i < n; i++) {
        int j = 0;
        // Compare current string with the assumed prefix character by character
        while (prefix[j] && strs[i][j] && prefix[j] == strs[i][j]) {
            j++;
        }
        // Terminate the prefix at the first mismatch
        prefix[j] = '\0';

        // If prefix becomes empty, no common prefix exists
        if (strlen(prefix) == 0) {
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    char strings[n][100];
    printf("Enter the strings:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    // Allocate memory for the prefix
    char prefix[100];

    // Find the longest common prefix
    commonPrefix(strings, n, prefix);

    // Print the result
    if (strlen(prefix) > 0) {
        printf("Longest Common Prefix: %s\n", prefix);
    } else {
        printf("No common prefix found\n");
    }

    return 0;
}
