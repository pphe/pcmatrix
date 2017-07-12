/* 
 * Peter Phe
 * TCSS 422 - Operating Systems
 * Winter 2017
 * Assignment 3 - pcMatrix Counter
 * Filename: counter.c
 * Description: Thread-safe synchronized counter data structure.
 */

#include <pthread.h>
#include "../include/counter.h"

void counter_init(counter_t *c)
{
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void counter_increment(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void counter_decrement(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);   
}

int counter_get(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}
