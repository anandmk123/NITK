#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    // Record the start time
    clock_t start_time = clock();
    
    sleep(2);
    clock_t end_time = clock();
    
    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Print the elapsed time
    printf("Elapsed time: %f seconds\n", elapsed_time);
    
    return 0;
}
