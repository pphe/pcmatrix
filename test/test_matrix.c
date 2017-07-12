/* Test driver for matrix module. */
#include <stdio.h>
#include "../include/matrix.h"
#define MAX 1000000
#define ROWS 5
#define COLS 5

int main(void)
{
    int sum;
    int **matrix = AllocMatrix(ROWS, COLS);
    GenMatrix(matrix, ROWS, COLS);
    AvgElement(matrix, ROWS, COLS);
    sum = SumMatrix(matrix, ROWS, COLS);

    printf("Sum of matrix: %d\n", sum);

    FreeMatrix(matrix, ROWS, COLS);
    return 0;
}
