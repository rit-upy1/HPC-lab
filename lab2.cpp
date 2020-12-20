// lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include<stdio.h>
#include<omp.h>

/* Main Program */

int main()
{
	float* array, * check, serial_sum, sum, partialSum;
	int             array_size, i;

	printf("Enter the size of the array\n");
	scanf("%d", &array_size);

	if (array_size <= 0) {
		printf("Array Size Should Be Of Positive Value ");
		exit(1);
	}
	/* Dynamic Memory Allocation */

	array = (float*)malloc(sizeof(float) * array_size);
	check = (float*)malloc(sizeof(float) * array_size);

	/* Array Elements Initialization */

	for (i = 0; i < array_size; i++) {
		array[i] = i * 5;
		check[i] = array[i];
	}

	printf("The Array Elements Are \n");

	for (i = 0; i < array_size; i++)
		printf("Array[%d]=%f\n", i, array[i]);

	sum = 0.0;
	partialSum = 0.0;

	/* OpenMP Parallel For Directive And Critical Section */

#pragma omp parallel for shared(sum)
	for (i = 0; i < array_size; i++) {
#pragma omp critical
		sum = sum + array[i];

	}

	serial_sum = 0.0;

	/* Serail Calculation */
	for (i = 0; i < array_size; i++)
		serial_sum = serial_sum + check[i];


	if (serial_sum == sum)
		printf("\nThe Serial And Parallel Sums Are Equal\n");
	else {
		printf("\nThe Serial And Parallel Sums Are UnEqual\n");
		exit(1);
	}

	/* Freeing Memory */
	free(check);
	free(array);

	printf("\nThe SumOfElements Of The Array Using OpenMP Directives Is %f\n", sum);
	printf("\nThe SumOfElements Of The Array By Serial Calculation Is %f\n", serial_sum);
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
