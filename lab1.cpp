// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <omp.h>

/* Main Program */

int main()
{
	int             noOfRows, noOfCols, Vectorsize, i, j;
	float** matrix, * vector, * result, * checkOutput;

	printf("Read the matrix size noofrows and columns and vectorsize\n");
	scanf("%d%d%d", &noOfRows, &noOfCols, &Vectorsize);

	if (noOfRows <= 0 || noOfCols <= 0 || Vectorsize <= 0) {
		printf("The Matrix and Vectorsize should be of positive sign\n");
		exit(1);
	}
	/* Checking For Matrix Vector Computation Necessary Condition */

	if (noOfCols != Vectorsize) {
		printf("Matrix Vector computation cannot be possible \n");
		exit(1);
	}
	/* Dynamic Memory Allocation  And Initialization Of Matrix Elements */

	matrix = (float**)malloc(sizeof(float) * noOfRows);
	for (i = 0; i < noOfRows; i++) {
		matrix[i] = (float*)malloc(sizeof(float) * noOfCols);
		for (j = 0; j < noOfCols; j++)
			matrix[i][j] = i + j;
	}

	/* Printing The Matrix */

	printf("The Matrix is \n");
	for (i = 0; i < noOfRows; i++) {
		for (j = 0; j < noOfCols; j++)
			printf("%f \t", matrix[i][j]);
		printf("\n");
	}

	printf("\n");

	/* Dynamic Memory Allocation */

	vector = (float*)malloc(sizeof(float) * Vectorsize);

	/* vector Initialization */

	for (i = 0; i < Vectorsize; i++)
		vector[i] = i;

	printf("\n");

	/* Printing The Vector Elements */

	printf("The Vector is \n");
	for (i = 0; i < Vectorsize; i++)
		printf("%f \t", vector[i]);

	/* Dynamic Memory Allocation */

	result = (float*)malloc(sizeof(float) * noOfRows);

	checkOutput = (float*)malloc(sizeof(float) * noOfRows);

	for (i = 0; i < noOfRows; i = i + 1)
	{
		result[i] = 0;
		checkOutput[i] = 0;
	}

	/* OpenMP Parallel Directive */

#pragma omp parallel for private(j)
	for (i = 0; i < noOfRows; i = i + 1)
		for (j = 0; j < noOfCols; j = j + 1)
			result[i] = result[i] + matrix[i][j] * vector[j];

	/* Serial Computation */

	for (i = 0; i < noOfRows; i = i + 1)
		for (j = 0; j < noOfCols; j = j + 1)
			checkOutput[i] = checkOutput[i] + matrix[i][j] * vector[j];

	for (i = 0; i < noOfRows; i = i + 1)
		if (checkOutput[i] == result[i])
			continue;
		else {
			printf("There is a difference from Serial and Parallel Computation \n");
			exit(1);
		}


	printf("\nThe Matrix Computation result is \n");
	for (i = 0; i < noOfRows; i++)
		printf("%f \n", result[i]);

	/* Freeing The Memory Allocations */

	free(vector);
	free(result);
	free(matrix);
	free(checkOutput);

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
