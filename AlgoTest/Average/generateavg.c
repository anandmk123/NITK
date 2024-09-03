#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to shuffle an array partially
void partial_shuffle(int arr[], int start, int end) {
    for (int i = start; i < end; i++) {
        int j = i + rand() / (RAND_MAX / (end - i) + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    int n = 30000;
    int arr[n];

    int i;

    FILE *fp = fopen("Shuffle30000.txt", "w");
    if (fp == NULL)
    {
        printf("Not able to open the file");
        return 0;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate an increasing sorted array
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Partially shuffle sections of the array
    partial_shuffle(arr, 0, n / 3);           // Shuffle first third
    partial_shuffle(arr, 2 * n / 3, n);       // Shuffle last third

    fprintf(fp, "%d\n",n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);

    return 0;
}
