/* 
 * Filename: prodcons.c
 * Description: Implements routines for the producer/consumer module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/counter.h"
#include "../include/matrix.h"
#include "../include/pcmatrix.h"
#include "../include/prodcons.h"

// producer consumer data structures
int **bigmatrix[MAX];
int fill_ptr;
int use_ptr;

// producer consumer locks and conditions
pthread_mutex_t mutex;
pthread_cond_t empty, fill;

// shared counter for generating and consuming matrices
counter_t count, prodCount, consCount;

void prodcon_init()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&fill, NULL);
	counter_init(&count);
	counter_init(&prodCount);
	counter_init(&consCount);
	fill_ptr = 0;
	use_ptr = 0;
}

// PRODUCER-CONSUMER put() get()
void put(int **value)
{
	bigmatrix[fill_ptr] = value;
	fill_ptr = (fill_ptr + 1) % MAX;
	counter_increment(&count);
}

int **get()
{
	int **tmp = bigmatrix[use_ptr];
	use_ptr = (use_ptr + 1) % MAX;
	counter_decrement(&count);
	return tmp;
}

// PRODUCER - return total of all arrays produced
void *prod_worker(void *arg)
{
	int *sum = malloc(sizeof(int));
	*sum = 0;

	while (1)
	{
		// acquire lock
		pthread_mutex_lock(&mutex);

		// check if number of desired matrices have been produced
		if (counter_get(&prodCount) == *((int *)arg))
		{
			pthread_mutex_unlock(&mutex);
			break;
		}

		// if no -> produce next matrix and increment counter for current iteration
		int **tmp = AllocMatrix(ROW, COL);
		GenMatrix(tmp, ROW, COL);
		*sum += SumMatrix(tmp, ROW, COL);
		counter_increment(&prodCount);

		// wait until bigmatrix has room to put in list
		while (counter_get(&count) == MAX)
			pthread_cond_wait(&empty, &mutex);
		put(tmp);

		// signal consumer and release lock
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&mutex);
	}

	return (void *)sum;
}

// CONSUMER - return total of all arrays consumed
void *cons_worker(void *arg)
{
	int *sum = malloc(sizeof(int));
	*sum = 0;

	while (1)
	{
		// acquire lock
		pthread_mutex_lock(&mutex);

		// check if number of desired matrices have been consumed
		if (counter_get(&consCount) == *((int *)arg))
		{
			pthread_mutex_unlock(&mutex);
			break;
		}

		// if no -> increment counter for this iteration
		counter_increment(&consCount);

		// wait if no matrix to consume
		while (counter_get(&count) == 0)
			pthread_cond_wait(&fill, &mutex);

		// consume next matrix
		int **tmp = get();
		*sum += SumMatrix(tmp, ROW, COL);

		// signal producer and release lock
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);

		// free memory of consumed matrix
		FreeMatrix(tmp, ROW, COL);
	}

	return (void *)sum;
}

