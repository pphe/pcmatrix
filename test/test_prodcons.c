/* Test driver for prodcons module. */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/prodcons.h"

int main(void)
{
	int loops = 1200000;
	int *cons_sum;
	int *prod_sum;

	printf("Producer Consumer test!\n");
	printf("Loops count: %d\n", loops);
	pthread_t prod, cons;

	prodcon_init();
	pthread_create(&prod, NULL, prod_worker, &loops);
	pthread_create(&cons, NULL, cons_worker, &loops);

	pthread_join(prod, (void **) &prod_sum);
	pthread_join(cons, (void **) &cons_sum); 
	
	if (prod_sum != NULL && cons_sum != NULL)
	{
		printf("producer sum: %d\n", *prod_sum);
		printf("consumer sum: %d\n", *cons_sum);
		free(prod_sum);
		free(cons_sum);
	}

    return 0;
}
