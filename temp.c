#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Eval(int N);
double Eval1(int N);

int main()
{
    for (int i = 0; i < 10; i++)
    	printf("%lf ", Eval(i));
    printf("\n");
    for (int i = 0; i < 10; i++)
    	printf("%lf ", Eval1(i));
}

double Eval(int N)
{
	int i;
	double Sum, Answer, Temp;
	double *C;

	C = (double*)malloc(sizeof(double) * (N + 1));
	C[0] = 1.0;
	C[1] = 3.0;

	for (i = 2; i <= N; i++)
	{
		Temp = (C[i - 1] - (i - 1)) * (i - 1) / 2;
		Sum = C[i - 1] + Temp;
		C[i] = 2.0 * Sum / i + i;
	}

	Answer = C[N];
	free(C);

	return Answer;
}

double Eval1(int N)
{
	int i, j;
	double Sum, Answer;
	double *C;

	C = (double*)malloc(sizeof(double) * (N + 1));
	C[0] = 1.0;

	for (i = 1; i <= N; i++)
	{
		Sum = 0.0;
		for (j = 0; j < i; j++)
			Sum += C[j];
		C[i] = 2.0 * Sum / i + i;
	}

	Answer = C[N];
	free(C);

	return Answer;
}