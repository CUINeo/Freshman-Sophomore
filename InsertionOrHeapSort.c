#include <stdio.h>
#include <stdlib.h>

int InsertionSort(int *I, int *Sample, int N);
int HeapSort(int *H, int *Sample, int N);
void Swap(int *a, int *b);
void PercolateDown(int *H, int i, int N);
int IsSame(int *a, int *Sample, int N);

int main(void)
{
	int i, N;
	scanf("%d", &N);

	int *I = (int*)malloc(N * sizeof(int));
	int *H = (int*)malloc((N + 1) * sizeof(int));
	int *Sample = (int*)malloc(N * sizeof(int));

	for (i = 0; i < N; i++) {
		scanf("%d", &I[i]);
		H[i] = I[i];
	}

	for (i = 0; i < N; i++)
		scanf("%d", &Sample[i]);

	if (!InsertionSort(I, Sample, N))
		HeapSort(H, Sample, N);

	return 0;
}

int InsertionSort(int *I, int *Sample, int N)
{
	int i, j, k, temp;
	static int flag = 0;

	if (N == 1 && IsSame(I, Sample, N))
		printf("Insertion Sort\n%d", I[0]);

	for (i = 1; i < N; i++) {
		if (I[i] <= I[0]) {
			temp = I[i];
			for (k = 1; k <= i; k++)
				I[k] = I[k - 1];
			I[0] = temp;
		}
		for (j = 0; j < i; j++) {
			if (I[i] >= I[j] && I[i] <= I[j + 1]) {
				temp = I[i];

				for (k = i; k > j + 1; k--)
					I[k] = I[k - 1];

				I[j + 1] = temp;
			}
		}

		if (flag) {
			printf("Insertion Sort\n");
			for (i = 0; i < N - 1; i++)
				printf("%d ", I[i]);
			printf("%d", I[i]);

			return 1;
		}

		if (IsSame(I, Sample, N))
			flag = 1;
	}

	return 0;
}

int HeapSort(int *H, int *Sample, int N)
{
	int i;
	static int flag = 0;

	for (i = N / 2; i >= 0; i--)
		PercolateDown(H, i, N);

	for (i = N - 1; i > 0; i--) {
		Swap(&H[0], &H[i]);
		PercolateDown(H, 0, i);

		if (flag) {
			printf("Heap Sort\n");
			for (i = 0; i < N - 1; i++)
				printf("%d ", H[i]);
			printf("%d", H[i]);

			return 1;
		}

		if (IsSame(H, Sample, N))
			flag = 1;
	}

	return 0;
}

void Swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void PercolateDown(int *H, int i, int N)
{
	int Child = 2 * i + 1;

	while (Child < N) {
		if (H[Child] < H[Child + 1] && Child + 1 < N)
			Child++;
		if (H[i] < H[Child])
			Swap(&H[i], &H[Child]);

		i = Child;
		Child = 2 * i + 1;
	}
}

int IsSame(int *a, int *Sample, int N)
{
	int i;

	for (i = 0; i < N; i++)
		if (a[i] != Sample[i])
			return 0;

	return 1;
}