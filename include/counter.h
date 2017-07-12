/* 
 * Peter Phe
 * TCSS 422 - Operating Systems
 * Winter 2017
 * Assignment 3 - pcMatrix Counter
 * Filename: counter.h
 * Description: Function prototypes, data and constants for synchronized counter module.
 */
#include <pthread.h>

typedef struct __counter_t
{
    int value;
    pthread_mutex_t lock;
} counter_t;

void counter_init(counter_t *);
void counter_increment(counter_t *);
void counter_decrement(counter_t *);
int counter_get(counter_t *);
