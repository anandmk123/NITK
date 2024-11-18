#include <stdio.h>
#include <stdlib.h>

// Structure to store grades with assignment index
typedef struct {
    int grade;         // Grade value
    int assignmentIdx; // Assignment index
} Grade;

// Binary heap implementation (Priority Queue)
typedef struct {
    Grade *heap;  // Array to store heap elements
    int size;     // Current number of elements in the heap
    int capacity; // Maximum capacity of the heap
} PriorityQueue;

// Function to initialize the priority queue
void initPriorityQueue(PriorityQueue *pq, int maxSize) {
    pq->heap = (Grade *)malloc(maxSize * sizeof(Grade)); // Allocate memory for the heap
    pq->size = 0;                                       // Initialize size to 0
    pq->capacity = maxSize;                             // Set the maximum capacity
}

// Function to swap two elements in the heap
void swap(Grade *a, Grade *b) {
    Grade temp = *a;
    *a = *b;
    *b = temp;
}

// Function to restore max-heap property after insertion
void heapifyUp(PriorityQueue *pq, int index) {
    // Compare the current node with its parent and swap if necessary
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->heap[index].grade > pq->heap[parent].grade) {
            swap(&pq->heap[index], &pq->heap[parent]);
            index = parent; // Move up to the parent node
        } else {
            break;
        }
    }
}

// Function to restore max-heap property after removal
void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index; // Assume the current node is the largest
    int left = 2 * index + 1;  // Index of the left child
    int right = 2 * index + 2; // Index of the right child

    // Check if the left child is larger than the current node
    if (left < pq->size && pq->heap[left].grade > pq->heap[largest].grade) {
        largest = left;
    }

    // Check if the right child is larger than the largest so far
    if (right < pq->size && pq->heap[right].grade > pq->heap[largest].grade) {
        largest = right;
    }

    // If the largest is not the current node, swap and continue heapifying
    if (largest != index) {
        swap(&pq->heap[index], &pq->heap[largest]);
        heapifyDown(pq, largest);
    }
}

// Function to push a new grade into the priority queue
void push(PriorityQueue *pq, Grade g) {
    // Check if the heap has reached its capacity
    if (pq->size == pq->capacity) {
        printf("Heap is full! Cannot push more elements.\n");
        return;
    }

    // Insert the new element at the end and restore heap property
    pq->heap[pq->size++] = g;
    heapifyUp(pq, pq->size - 1);
}

// Function to pop the maximum grade from the priority queue
Grade pop(PriorityQueue *pq) {
    // Check if the heap is empty
    if (pq->size == 0) {
        printf("Heap is empty! Cannot pop elements.\n");
        exit(1);
    }

    // Remove the top element (max grade) and restore heap property
    Grade top = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];
    heapifyDown(pq, 0);
    return top;
}

// Function to free the priority queue memory
void freePriorityQueue(PriorityQueue *pq) {
    free(pq->heap); // Free the dynamically allocated memory
}

// Function to maximize grades and return the total grade and allocation
void maximizeGrades(int n, int H, int **B, int *B_sizes, int *totalGrade, int *allocation) {
    PriorityQueue pq;
    initPriorityQueue(&pq, n + H); // Initialize the priority queue with a max size of n + H

    int hoursSpent[n]; // Track hours spent on each assignment
    for (int i = 0; i < n; i++) {
        hoursSpent[i] = 0; // Initialize hours spent to 0 for each assignment
    }

    // Initialize the priority queue with the first grade of each assignment
    for (int i = 0; i < n; i++) {
        if (B_sizes[i] > 0) { // Check if the assignment has any grades available
            Grade g = {B[i][0], i};
            push(&pq, g);
        }
    }

    *totalGrade = 0;     // Initialize total grade to 0
    int allocatedHours = 0; // Track the number of allocated hours

    // Allocate hours while there are hours left and the priority queue is not empty
    while (H > 0 && pq.size > 0) {
        Grade current = pop(&pq); // Get the highest grade available
        int assignmentIdx = current.assignmentIdx; // Assignment index of the grade

        *totalGrade += current.grade; // Add the grade to the total
        allocation[allocatedHours++] = assignmentIdx; // Record the allocation for this hour
        H--; // Decrement the remaining hours
        hoursSpent[assignmentIdx]++; // Increment the hours spent on this assignment

        // If there are more grades available for the current assignment, push the next grade
        if (hoursSpent[assignmentIdx] < B_sizes[assignmentIdx]) {
            Grade next = {B[assignmentIdx][hoursSpent[assignmentIdx]], assignmentIdx};
            push(&pq, next);
        }
    }

    freePriorityQueue(&pq); // Free the memory used by the priority queue
}

int main() {
    // int n = 3; // Number of assignments
    // int H = 5; // Total hours available

    // // Grades for each hour of effort on each assignment (decreasing order)
    // int B1[] = {9, 6, 4, 2, 1};
    // int B2[] = {7, 5, 3, 2, 1};
    // int B3[] = {8, 6, 4, 2};

    // int *B[] = {B1, B2, B3}; // Array of pointers to grades
    // int B_sizes[] = {5, 5, 4}; // Sizes of each assignment's grades

    int n = 4;  // Number of assignments
    int H = 6;  // Total hours available

    // Grades for each hour of effort on each assignment (decreasing order)
    int B1[] = {10, 7, 5, 2};
    int B2[] = {8, 6, 4, 3};
    int B3[] = {9, 6, 3, 1};
    int B4[] = {6, 4, 2, 1};

    int *B[] = {B1, B2, B3, B4}; // Array of pointers to grades
    int B_sizes[] = {4, 4, 4, 4}; // Sizes of each assignment's grades


    int totalGrade = 0;        // To store the maximum total grade
    int allocation[H];         // To store which assignment each hour is allocated to


    // Calculate maximum grades and allocation
    maximizeGrades(n, H, B, B_sizes, &totalGrade, allocation);

    // Output results
    printf("Maximum total grade: %d\n", totalGrade);
    printf("Hour allocations:\n");
    for (int i = 0; i < H; i++) {
        printf("Hour %d: Assignment %d\n", i + 1, allocation[i] + 1); // 1-based assignment index
    }

    return 0;
}
