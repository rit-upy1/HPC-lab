// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <omp.h>

int fib(int n)
{
	if (n < 2) return n;
	else return fib(n - 1) + fib(n - 2);
}

int main()
{
	int fibnumber[100], i, j, n;
	printf("Please Enter the series limit\n");
	scanf("%d", &n);
#pragma omp parallel num_threads(2)
	{
#pragma omp critical
		if (omp_get_thread_num() == 0)
		{
			printf("There are %d threads\n", omp_get_num_threads());
			printf("Thread %d generating numbers..\n", omp_get_thread_num());
			for (i = 0;i < n;i++)
				fibnumber[i] = fib(i);
		}
		else
		{
			printf("Thread %d Printing numbers..\n", omp_get_thread_num());
			for (j = 0;j < n;j++)
				printf("%d\t", fibnumber[j]);
		}

	}
	return 0;
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
