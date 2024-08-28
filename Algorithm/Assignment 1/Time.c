#include <stdio.h>
#include <sys/time.h>
#include<stdlib.h>

long currentTimeMillis() {
  struct timeval time;
  gettimeofday(&time, NULL);

  return time.tv_sec * 1000 + time.tv_usec / 1000;
}

int main() {
  printf("%ld\n", currentTimeMillis());
  // wait 1 second
  sleep(1);
  printf("%ld\n", currentTimeMillis());
  return 0;
 }
