#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main() {
    // Record the starting time
    clock_t start = clock();

    sleep(4);

    // Record the ending time
    clock_t end = clock();

    double time_spent1 = (double)(end - start) / CLOCKS_PER_SEC;

    // Calculate the elapsed time in milliseconds
    double time_spent2 = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("The execution time is %f seconds\n", time_spent1);
    // Print the execution time
    printf("The execution time is %f milliseconds\n", time_spent2);

    return 0;
}
