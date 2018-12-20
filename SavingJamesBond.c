#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Infinity 1e5
#define MaxCrocodile 10000
#define NoCrocodileFound (-1);
#define NoPathFound (-1);
#define IslandRadii 7.5;

typedef enum { false, true } bool;

typedef struct
{
	double x;
	double y;
	double Distance;
} Crocodile;

typedef struct GNode *MGraph;
struct GNode {
	int Nv;
	Crocodile C[MaxCrocodile];
	int G[MaxCrocodile][MaxCrocodile];
};

MGraph CreateG(int N, int D);
bool IsValid(double x, double y);
int ShortestPathNum(MGraph Graph, int S, double D, int* FinalCro);
int* FindShortestPath(MGraph Graph, int S, int F);
bool ReachBank(MGraph Graph, int i, double D);

int main(void)
{
	int i, N, D, JTimes, FinalCro;
	double Distance;
	int* Path = (int*)malloc(sizeof(int)*MaxCrocodile);

	JTimes = Distance = Infinity;

	scanf("%d %d", &N, &D);
	if (D >= 50 - IslandRadii) {
		printf("1");
		system("pause");
		return 0;
	}
	MGraph Graph = CreateG(N, D);

	for (i = 0; i < Graph->Nv; i++)
		if (Graph->C[i].Distance <= IslandRadii + D) {
			int T = ShortestPathNum(Graph, i, D, &FinalCro);
			if (T < JTimes && T != NoPathFound) {
				Path = FindShortestPath(Graph, i, FinalCro);
				JTimes = T;
				Distance = Graph->C[i].Distance;
			}
			if (T == JTimes && Graph->C[i].Distance < Distance) {
				Path = FindShortestPath(Graph, i, FinalCro);
				JTimes = T;
				Distance = Graph->C[i].Distance;
			}
		}

	if (JTimes < Infinity) {
		printf("%d", JTimes);
		for (i = JTimes-2; i >= 0; i--) {
			printf("\n");
			printf("%.0lf %.0lf", Graph->C[*(Path+i)].x, Graph->C[*(Path+i)].y);
		}
	}
	else printf("0");

	system("pause");
	return 0;
}

MGraph CreateG(int N, int D)
{
	int i, j;
	double d, x1, x2, y1, y2;
	MGraph Graph = (MGraph)malloc(sizeof(struct GNode));

	for (i = 0; i < N; i++) {
		scanf("%lf %lf", &x1, &y1);
		if (IsValid(x1, y1)) {
			Graph->C[i].x = x1;
			Graph->C[i].y = y1;
		}
		else {
			i--;
			N--;
		}
	}
	Graph->Nv = N;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			Graph->G[i][j] = 0;
		Graph->C[i].Distance = sqrt(Graph->C[i].x*Graph->C[i].x + Graph->C[i].y*Graph->C[i].y);
	}

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			if (i != j) {
				x1 = Graph->C[i].x;
				x2 = Graph->C[j].x;
				y1 = Graph->C[i].y;
				y2 = Graph->C[j].y;
				d = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
				if (d <= D && d > 0)
					Graph->G[i][j] = 1;
			}
		}

	return Graph;
}

bool IsValid(double x, double y)
{
	if (x > 50 || x < -50 || y > 50 || y < -50)
		return false;
	if (sqrt(x*x + y*y) < IslandRadii)
		return false;
	
	return true;
}

int ShortestPathNum(MGraph Graph, int S, double D, int* FinalCro)
{
	int i, Num, top, rear, flag, Current;
	int Queue[MaxCrocodile];
	bool Known[MaxCrocodile];

	for (i = 0; i < Graph->Nv; i++)
		Known[i] = false;

	Num = 1;
	top = -1;
	rear = 0;
	flag = 0;
	Queue[++top] = S;
	Known[S] = true;

	while (true) {
		if (top < rear)
			break;
		Num++;
		for (; rear <= flag; ) {
			Current = Queue[rear++];
			if (ReachBank(Graph, Current, D) == true) {
				*FinalCro = Current;
				return Num;
			}
			for (i = 0; i < Graph->Nv; i++)
				if (Graph->G[Current][i] && Known[i] == false) {
					Queue[++top] = i;
					Known[i] = true;
				}
		}
		flag = top;
	}

	return NoPathFound;
}

int* FindShortestPath(MGraph Graph, int S, int F)
{
	int i, top, rear, flag, Current;
	int Path[MaxCrocodile], Queue[MaxCrocodile], Known[MaxCrocodile];
	int* ShortestPath = (int*)malloc(sizeof(int)*MaxCrocodile);

	for (i = 0; i < Graph->Nv; i++)
		Known[i] = false;

	rear = 0;
	top = -1;
	flag = 0;
	Queue[++top] = S;
	Known[S] = true;

	while (true) {
		if (top < rear)
			break;
		for (; rear <= flag; ) {
			Current = Queue[rear++];
			for (i = 0; i < Graph->Nv; i++)
				if (Graph->G[Current][i] && Known[i] == false) {
					Queue[++top] = i;
					Path[i] = Current;
					Known[i] = true;
				}
		}
		flag = top;
	}

	for (i = 0, Current = F; Current != S; Current = Path[Current])
		ShortestPath[i++] = Current;
	ShortestPath[i] = S;

	return ShortestPath;
}

bool ReachBank(MGraph Graph, int i, double D)
{
	double x, y;
	x = Graph->C[i].x;
	y = Graph->C[i].y;

	if (x <= -50 + D || x >= 50 - D || y <= -50 + D || y >= 50 - D)
		return true;
	else
		return false;
}