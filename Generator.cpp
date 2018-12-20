#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Generator.h"

double* Generator(int num)
{
	int i;
	double* Ret = (double*)malloc(sizeof(double) * MaxNum);

	srand((unsigned)time(NULL));	// Set the system clock as seed
	for (i = 0; i < num; i++)
		Ret[i] = rand() % MaxValue;

	return Ret;
}