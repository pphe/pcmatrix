/* 
 * Peter Phe
 * TCSS 422 - Operating Systems
 * Winter 2017
 * Assignment 3 - pcMatrix Matrix Functions
 * Filename: prodcons.h
 * Description: Function prototypes, data, and constants for producer/consumer module.
 */

// PRODUCER-CONSUMER put() get() function prototypes
void put(int **);
int **get(void);

// PRODUCER-CONSUMER thread method function prototypes
void *prod_worker(void *);
void *cons_worker(void *);
void prodcon_init();

