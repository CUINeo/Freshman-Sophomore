#include <stdio.h>
#include <stdlib.h>

#define MaxNum 100000
#define True 1

int* ReadIn(int N);
int CountTimes(int *Array, int N);
int Swap0andi(int *Array, int N, int i, int ZPos);
void Swap(int *p, int *q);
int Judge(int *Array, int N);

int main(void)
{
	int N, Times;
	scanf("%d", &N);
	int *Array = ReadIn(N);
	Times = CountTimes(Array, N);
	printf("%d", Times);

	return 0;
}

int* ReadIn(int N)
{
	int i;
	int *Array = (int*)malloc(N * sizeof(int));

	for (i = 0; i < N; i++)
		scanf("%d", &Array[i]);

	return Array;
}

int CountTimes(int *Array, int N)
{
	if (N == 1)
		return 0;

	int i, Times, LeastTimes, ZPos;

	Times = 0;
	LeastTimes = N - 1;

	for (i = 0; i < N; i++) {
		if (Array[i] == i)
			LeastTimes--;
		if (Array[i] == 0)
			ZPos = i;
	}

	while (True) {
		if (ZPos == 0) {
			for (i = 0; i < N; i++)
				if (Array[i] != i)
					break;

			ZPos = Swap0andi(Array, N, Array[i], ZPos);
		}
		else
			ZPos = Swap0andi(Array, N, ZPos, ZPos);

		Times++;

		if (Times >= LeastTimes && Judge(Array, N))
			return Times;
	}
}

int Swap0andi(int *Array, int N, int i, int ZPos)
{
	int k, IPos;

	for (k = 0; k < N; k++)
		if (Array[k] == i) {
			IPos = k;
			break;
		}

	Swap(&Array[ZPos], &Array[IPos]);

	return IPos;
}

void Swap(int *p, int *q)
{
	int temp;

	temp = *p;
	*p = *q;
	*q = temp;
}

int Judge(int *Array, int N)
{
	int i;

	for (i = 1; i < N; i++)
		if (Array[i] != i)
			return 0;

	return 1;
}