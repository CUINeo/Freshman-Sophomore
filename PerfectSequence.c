#include <stdio.h>
#include <stdlib.h>

#define MaxNumber (100000)
#define CutOff (20)
#define ElementType int

ElementType *ReadIn(int N);
void QuickSort(ElementType A[], int N);
void QSort(ElementType A[], int Left, int Right);
ElementType Median3(ElementType A[], int Left, int Right);
void Swap(ElementType *a, ElementType *b);
void InsertionSort(ElementType A[], int N);
void MaxArrayLen(ElementType A[], int N, double P);
int BiSearch(ElementType A[], int Left, int Right, double P);

int main(void)
{
	int N;
	double P;

	scanf("%d %lf", &N, &P);

	ElementType *A = ReadIn(N);
	QuickSort(A, N);

	MaxArrayLen(A, N, P);

	return 0;
}

ElementType *ReadIn(int N)
{
	int i;
	ElementType *A = (ElementType*)malloc(N * sizeof(ElementType));

	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);

	return A;
}

void QuickSort(ElementType A[], int N)
{
	QSort(A, 0, N - 1);
}

void QSort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if (Left + CutOff <= Right) 
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;

		for ( ; ; ) 
		{
			while (A[++i] < Pivot);
			while (A[--j] > Pivot);

			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		QSort(A, Left, i - 1);
		QSort(A, i + 1, Right);
	}
	else 
		InsertionSort(A + Left, Right - Left + 1);
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];
}

void Swap(ElementType *a, ElementType *b)
{
	ElementType temp = *a;
	*a = *b;
	*b = temp;
}

void InsertionSort(ElementType A[], int N)
{
	int i, P;
	ElementType temp;

	for (P = 1; P < N; P++) 
	{
		temp = A[P];
		for (i = P; i > 0 && A[i - 1] > temp; i--)
			A[i] = A[i - 1];
		A[i] = temp;
	}
}

void MaxArrayLen(ElementType A[], int N, double P)
{
	int i, Temp, MaxLen;

	if (A[0] * P >= A[N - 1])
	{
		printf("%d", N);
		return;
	}

	MaxLen = BiSearch(A, 0, N - 1, P);
	for (i = 1; i < N; i++)
	{
		if (MaxLen >= N - i)
			break;

		Temp = BiSearch(A, i, N - 1, P);
		if (Temp > MaxLen)
			MaxLen = Temp;
	}

	printf("%d", MaxLen);
}

int BiSearch(ElementType A[], int Left, int Right, double P)
{
	int Lpos, Rpos, Center;
	double Temp = A[Left] * P;

	Lpos = Left;
	Rpos = Right;

	while (Lpos <= Rpos)
	{
		Center = (Lpos + Rpos) / 2;

		if (A[Center] <= Temp)
			Lpos = Center + 1;
		else if (A[Center] > Temp)
			Rpos = Center - 1;
	}

	return Lpos - Left;
}