/* Test driver for counter data structure. */
#include <stdio.h>
#include "../include/counter.h"
#define MAX 1000000

int main(void)
{
    counter_t foo;
    counter_init(&foo);
    printf("Initialized value: %d\n", counter_get(&foo));

    counter_increment(&foo);
    printf("Incremented by one: %d\n", counter_get(&foo));

    counter_decrement(&foo);
    printf("Decremented by one: %d\n", counter_get(&foo));

    return 0;
}
