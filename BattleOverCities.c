#include <stdio.h>
#include <stdlib.h>

#define MaxCityNum 510
#define NoHighway 100000
#define Infinity 100000
#define NoNeedtoRepair 0
#define Broken 0

typedef int City;

typedef struct highwaynode Highway;
struct highwaynode
{
	City C1;
	City C2;
	int Cost;
	int Status;
};

typedef struct countrynode *Country;
struct countrynode
{
	int Nc;
	int Nh;
	int NBh;
	Highway *HArray;
	Highway *BHArray;
};

Country ReadC();
void Sort(Country C);
void Exchange(Country C, int i, int j);
void Initialize(int* MinCost, int Nc);
int GetMinCost(Country C, City S);
Highway FindMinPath(Country C, int connected[], City S);
void PrintOut(int *MinCost, Country C);

int main(void)
{
	int i;
	int MinCost[MaxCityNum];

	Country C = ReadC();
	Initialize(MinCost, C->Nc);

	for (i = 1; i <= C->Nc; i++)
		MinCost[i] = GetMinCost(C, i);

	PrintOut(MinCost, C);

	return 0;
}

Country ReadC()
{
	int i, j, N, M, C1, C2, Cost, Status;
	Country C = (Country)malloc(sizeof(struct countrynode));

	scanf("%d %d", &N, &M);
	C->Nc = N;
	C->Nh = M;
	C->HArray = (Highway*)malloc(C->Nh * sizeof(Highway));
	C->BHArray = (Highway*)malloc(C->Nh * sizeof(Highway));

	for (i = 0, j = 0; i < M; i++) {
		scanf("%d %d %d %d", &C1, &C2, &Cost, &Status);

		C->HArray[i].C1 = C1;
		C->HArray[i].C2 = C2;
		C->HArray[i].Cost = Cost;
		C->HArray[i].Status = Status;

		if (!Status) {
			C->BHArray[j].C1 = C1;
			C->BHArray[j].C2 = C2;
			C->BHArray[j].Cost = Cost;
			C->BHArray[j].Status = Status;
			j++;
		}
	}
	C->NBh = j;
	Sort(C);

	return C;
}

void Sort(Country C)
{
	int i, j;

	for (i = 0; i < C->NBh; i++)
		for (j = 0; j < C->NBh; j++)
			if (C->BHArray[j].Cost > C->BHArray[j + 1].Cost)
				Exchange(C, j, j + 1);
}

void Exchange(Country C, int i, int j)
{
	Highway H, J;
	int temp;

	H = C->HArray[i];
	J = C->HArray[j];

	temp = H.C1;
	H.C1 = J.C1;
	J.C1 = temp;

	temp = H.C2;
	H.C2 = J.C2;
	J.C2 = temp;

	temp = H.Cost;
	H.Cost = J.Cost;
	J.Cost = temp;

	temp = H.Status;
	H.Status = J.Status;
	J.Status = temp;
}

void Initialize(int* MinCost, int Nc)
{
	int i;

	for (i = 1; i <= Nc; i++)
		MinCost[i] = NoNeedtoRepair;
}

int GetMinCost(Country C, City S)
{
	int i, MinCost;
	int connected[MaxCityNum];
	Highway H;

	MinCost = NoNeedtoRepair;
	for (i = 1; i <= C->Nc; i++)
		connected[i] = 0;

	for (i = 0; i < C->Nh; i++) {
		H = C->HArray[i];
		if (H.C1 != S && H.C2 != S && H.Status) {
			connected[H.C1] = 1;
			connected[H.C2] = 1;
		}
	}

	H = FindMinPath(C, connected, S);
	while (H.Status != NoHighway) {
		MinCost += H.Cost;
		H = FindMinPath(C, connected, S);
	}

	for (i = 1; i <= C->Nc; i++)
		if (i != S && !connected[i])
			return Infinity;

	return MinCost;
}

Highway FindMinPath(Country C, int connected[], City S)
{
	int i;
	Highway H;

	for (i = 0; i < C->NBh; i++) {
		H = C->BHArray[i];
		if (H.C1 != S && H.C2 != S) {
			if (connected[H.C1] && !connected[H.C2]) {
				connected[H.C2] = 1;
				return H;
			}
			if (!connected[H.C1] && connected[H.C2]) {
				connected[H.C1] = 1;
				return H;
			}
		}
	}

	H.Status = NoHighway;
	return H;
}

void PrintOut(int *MinCost, Country C)
{
	int i, max, rear, top;
	City Queue[MaxCityNum];
	max = 0;
	top = -1;
	rear = 0;

	for (i = 1; i <= C->Nc; i++)
		if (MinCost[i] > max)
			max = MinCost[i];

	if (max == 0) {
		printf("0");
		return;
	}

	for (i = 1; i <= C->Nc; i++)
		if (MinCost[i] == max)
			Queue[++top] = i;

	for (i = rear; i < top; i++)
		printf("%d ", Queue[i]);

	printf("%d", Queue[i]);
}