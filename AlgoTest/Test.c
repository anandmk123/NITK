// Online C compiler to run C program online
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


int main() {
    // Write C code here
        struct timeval tv1, tv2;
        gettimeofday(&tv1, NULL);
        sleep(2);
        gettimeofday(&tv2, NULL);
        printf("%f\n",(double)(tv2.tv_usec - tv1.tv_usec) / 1000000);
        printf("%f\n",(double)(tv2.tv_sec - tv1.tv_sec));

        double executiontime=(double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
                    (double)(tv2.tv_sec - tv1.tv_sec);
        printf("%f",executiontime);
         return 0;
}