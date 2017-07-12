/* 
 * Peter Phe
 * TCSS 422 - Operating Systems
 * Winter 2017
 * Assignment 3 - pcMatrix Matrix Functions
 * Filename: matrix.c
 * Description: Matrix routines.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <time.h>
#define OUTPUT 0

// MATRIX ROUTINES
int ** AllocMatrix(int r, int c)
{
    int ** a;
    int i;
    a = (int**) malloc(sizeof(int *) * r);
    assert(a != 0);
    for (i = 0; i < r; i++)
    {
        a[i] = (int *) malloc(c * sizeof(int));
        assert(a[i] != 0);
    }
    return a;
}

void FreeMatrix(int ** a, int r, int c)
{
    int i;
    for (i=0; i<r; i++)
    {
        free(a[i]);
    }
    free(a);
}

// generates values for elements of a matrix
void GenMatrix(int ** matrix, const int height, const int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int * mm = matrix[i];
            //matrix[i * width + j] = rand() % 10;
            mm[j] = rand() % 10; // uncomment for final testing
            //mm[j] = 1; // delete later (test to verify prod sum == cons sum)
#if OUTPUT
            printf("matrix[%d][%d]=%d \n",i,j,mm[j]);
#endif
        }
    }
}

// returns the average of all elements in a matrix
int AvgElement(int ** matrix, const int height, const int width)
{
    int x=0;
    int y=0;
    int ele=0;
    int i, j;
    for (i=0; i<height; i++)
        for (j=0; j<width; j++)
        {
            int *mm = matrix[i];
            y=mm[j];  
            x=x+y;
            ele++;
#if OUTPUT
            printf("[%d][%d]--%d x=%d ele=%d\n",i,j,mm[j],x,ele);
#endif
        }
    printf("x=%d ele=%d\n",x, ele);
    return x / ele; 
}

// returns the sum of all elements in a matrix
int SumMatrix(int ** matrix, const int height, const int width)
{
    int total = 0;
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
			total += matrix[i][j];
    }

    return total;
}

