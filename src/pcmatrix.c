/* 
 * Peter Phe
 * TCSS 422 - Operating Systems
 * Winter 2017
 * Assignment 3 - pcMatrix Matrix Functions
 * Filename: pcmatrix.c
 * Description: Primary module providing control flow for the pcMatrix program.
 * 				Creates a dynamic number of producer and consumer threads and 
 * 				launches them to produce and consume matrices. Each thread produces 
 * 				a total sum of the value of randomly generated elements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/counter.h"
#include "../include/prodcons.h"
#include "../include/pcmatrix.h"

int main (int argc, char * argv[])
{
	time_t t;
	int prs = 0;
	int cos = 0;
	int loops = LOOPS;
	int numw = NUMWORK;

	// handle dynamic number of threads if specified as argument
	if (argc > 1)
		numw = atoi(argv[1]);

	pthread_t pr[numw];
	pthread_t co[numw];

	// Seed the random number generator with the system time
	srand((unsigned) time(&t));

	printf("Producing %d %dx%d matrices.\n", loops, ROW, COL);
	printf("Using a shared buffer of size=%d\n", MAX);
	printf("With %d producer and consumer threads.\n", numw);

	prodcon_init(); // initialize prodcon data structure

	// create threads
	int i;
	for (i = 0; i < numw; i++)
	{
		pthread_create(&pr[i], NULL, prod_worker, &loops);
		pthread_create(&co[i], NULL, cons_worker, &loops);
	}

	// join and sum up thread values
	for (i = 0; i < numw; i++)
	{
		int *prod_sum;
		int *cons_sum;
		pthread_join(pr[i], (void **)&prod_sum); 
		pthread_join(co[i], (void **)&cons_sum);
		prs += *prod_sum;
		cos += *cons_sum;
		free(prod_sum);
		free(cons_sum);
	}
	
	printf("Produced = Consumed --> %d = %d\n", prs, cos);
	return 0;
}
