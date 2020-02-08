#include <stdio.h>
#include "rtos-alloc.h"
#include <time.h>

int main()
{
    void *ap = rtos_is_valid(rtos_malloc(10000000*sizeof(int)));
  
    
    
    // uint64_t execTime; /*time in nanoseconds */
    // struct timespec tick, tock;
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tick);
    // void *ap = rtos_malloc(10000000*sizeof(int));
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tock);
    // execTime = 1000000000 * (tock.tv_sec - tick.tv_sec) + tock.tv_nsec - tick.tv_nsec;
    // printf("elapsed process CPU time = %llu nanoseconds\n", (long long unsigned int) execTime);
    // return 0;
}