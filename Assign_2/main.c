#include <stdio.h>
#include "rtos-alloc.h"

int main()
{
    void *ptr = rtos_malloc(8);
    void *new_ptr = rtos_malloc(18);
    rtos_free(new_ptr);
    return 0;
}