#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Element;

void mergeAndCount(Element arr[], int start, int mid, int end, int result[]) {
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    // Temporary arrays for left and right subarrays
    Element* leftArray = (Element*)malloc(leftSize * sizeof(Element));
    Element* rightArray = (Element*)malloc(rightSize * sizeof(Element));

    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[start + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;
    int rightCounter = 0;

    // Merge and count smaller elements
    while (i < leftSize && j < rightSize) {
        if (leftArray[i].value <= rightArray[j].value) {
            result[leftArray[i].index] += rightCounter;
            arr[k++] = leftArray[i++];
        } else {
            rightCounter++;
            arr[k++] = rightArray[j++];
        }
    }

    // Copy remaining elements of leftArray
    while (i < leftSize) {
        result[leftArray[i].index] += rightCounter;
        arr[k++] = leftArray[i++];
    }

    // Copy remaining elements of rightArray
    while (j < rightSize) {
        arr[k++] = rightArray[j++];
    }

    free(leftArray);
    free(rightArray);
}

void divideAndCount(Element arr[], int start, int end, int result[]) {
    if (start >= end) return;

    int mid = start + (end - start) / 2;

    // Recursively divide the array
    divideAndCount(arr, start, mid, result);
    divideAndCount(arr, mid + 1, end, result);

    // Merge and count smaller elements
    mergeAndCount(arr, start, mid, end, result);
}

void countSmallerElements(int arr[], int n, int result[]) {
    Element* elements = (Element*)malloc(n * sizeof(Element));

    for (int i = 0; i < n; i++) {
        elements[i].value = arr[i];
        elements[i].index = i;
    }

    divideAndCount(elements, 0, n - 1, result);

    free(elements);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    int* result = (int*)malloc(n * sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        result[i] = 0;
    }

    countSmallerElements(arr, n, result);

    printf("Result: \n");
    for (int i = 0; i < n; i++) {
        printf("Number of elements smaller than %d to the right: %d\n", arr[i], result[i]);
    }

    free(arr);
    free(result);

    return 0;
}