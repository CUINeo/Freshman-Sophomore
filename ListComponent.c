#include <stdio.h>
#include <stdlib.h>

#define MaxCityNum 510
#define NoNeedtoRepair 0
#define NoHighway 100000

typedef int City;

typedef struct highwaynode *Highway;
struct highwaynode
{
	City Ct;
	int Cost;
	int Status;
	Highway Next;
};

typedef struct countrynode *Country;
struct countrynode
{
	int Nc;
	int Nh;
	Highway HArray[MaxCityNum];
};

Country ReadC();
void Initialize(int* MinCost, int Nc);
int JudgeConnection(Country C);
void DFS(Country C, int known[], City S);
int GetMinCost(Country C, City S);
void PrintOut(int *MinCost, Country C);

int main(void)
{
	int i;
	int MinCost[MaxCityNum];

	Country C = ReadC();
	Initialize(MinCost, C->Nc);

	if (JudgeConnection(C))
		printf("0");
	else {
		for (i = 1; i <= C->Nc; i++)
			MinCost[i] = GetMinCost(C, i);
		PrintOut(MinCost, C);
	}

	return 0;
}

Country ReadC()
{
	int i, N, M, C1, C2, Cost, Status;
	Highway H;
	Country C = (Country)malloc(sizeof(struct countrynode));

	scanf("%d %d", &N, &M);
	C->Nc = N;
	C->Nh = M;

	for (i = 1; i <= C->Nc; i++) {
		C->HArray[i] = (Highway)malloc(sizeof(struct highwaynode));
		C->HArray[i]->Status = NoHighway;
		C->HArray[i]->Next = NULL;
	}

	while (M--) {
		scanf("%d %d %d %d", &C1, &C2, &Cost, &Status);

		for (H = C->HArray[C1]; H->Next; H = H->Next);
		H->Next = (Highway)malloc(sizeof(struct highwaynode));
		H->Next->Next = NULL;
		H->Next->Cost = Cost;
		H->Next->Status = Status;
		H->Next->Ct = C2;

		for (H = C->HArray[C2]; H->Next; H = H->Next);
		H->Next = (Highway)malloc(sizeof(struct highwaynode));
		H->Next->Next = NULL;
		H->Next->Cost = Cost;
		H->Next->Status = Status;
		H->Next->Ct = C1;
	}

	return C;
}

void Initialize(int* MinCost, int Nc)
{
	int i;

	for (i = 1; i <= Nc; i++)
		MinCost[i] = NoNeedtoRepair;
}

int JudgeConnection(Country C)
{
	int i;
	int known[MaxCityNum];

	for (i = 1; i <= C->Nc; i++)
		known[i] = 0;

	DFS(C, known, 1);

	for (i = 1; i <= C->Nc; i++)
		if (!known[i])
			return 0;

	return 1;
}

void DFS(Country C, int known[], City S)
{
	Highway H;
	known[S] = 1;

	for (H = C->HArray[S]; H; H = H->Next)
		if (!known[H->Ct])
			DFS(C, known, H->Ct);
}

int GetMinCost(Country C, City S)
{

}

void PrintOut(int *MinCost, Country C)
{
	int i, min, rear, top;
	City Queue[MaxCityNum];
	min = 0;
	top = -1;
	rear = 0;

	for (i = 1; i <= C->Nc; i++)
		if (MinCost[i] > min)
			min = MinCost[i];

	for (i = 1; i <= C->Nc; i++)
		if (MinCost[i] == min)
			Queue[top++] = i;

	for (i = rear; i < top; i++)
		printf("%d ", Queue[i]);

	printf("%d", Queue[i]);
}