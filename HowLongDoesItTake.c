#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100

//typedef enum { false, true } bool;
typedef int Vertex;

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    int TimeCost;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *Graph;
struct GNode{  
    int Nv;
    AdjList NodeList;
};

Graph Initialize( int Num );
void AddEdge( Graph G, Vertex start, Vertex end, int time );
int FindLongestTime( Graph G, int Num );
bool TopCheck( Graph G );
int Count( Graph G, int startpoint, int LongestTime[] );

int main(void)
{
	int m, n, start, end, time, Ltime;

	scanf("%d %d", &n, &m);
	Graph G = Initialize( n );

	while (m--) {
		getchar();
		scanf("%d %d %d", &start, &end, &time);

		AddEdge( G, start, end, time );
	}

	Ltime = FindLongestTime( G, n );
	if (Ltime == -1)
		printf("Impossible\n");
	else 
		printf("%d\n", Ltime);
}

Graph Initialize( int Num )
{
	int i;

	Graph G = (Graph)malloc(sizeof(struct GNode));
	G->Nv = Num;
	for (i = 0; i < Num; i++)
		G->NodeList[i].FirstEdge = NULL;

	return G;
}

void AddEdge( Graph G, Vertex start, Vertex end, int time )
{
	PtrToAdjVNode p, q;

	p = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	p->AdjV = end;
	p->TimeCost = time;
	p->Next = NULL;

	for (q = G->NodeList[start].FirstEdge; q&&q->Next; q = q->Next)
		;
	if (q == NULL)
		G->NodeList[start].FirstEdge = p;
	else
		q->Next = p;
}

int FindLongestTime( Graph G, int Num )
{
	if (TopCheck( G ) == false)
		return -1;

	int i, startpoint, Ltime, ret;
	int LongestTime[MaxVertexNum];

	ret = 0;

	for (startpoint = 0; startpoint < Num; startpoint++) {
		for (i = 0; i < Num; i++)
			LongestTime[i] = 0;

		Ltime = Count( G, startpoint, LongestTime );

		if (ret < Ltime)
			ret = Ltime;
	}

	return ret;
}

bool TopCheck( Graph G )
{
	int i, j, Counter;
	int Indegree[MaxVertexNum];
	PtrToAdjVNode p;

	for (i = 0; i<G->Nv; i++)
		Indegree[i] = 0;

	for (i = 0; i<G->Nv; i++)
		for (p = G->NodeList[i].FirstEdge; p; p = p->Next)
			Indegree[p->AdjV]++;

	Vertex Stack[MaxVertexNum];
	j = -1;
	for (i = 0; i<G->Nv; i++)
		if (Indegree[i] == 0)
			Stack[++j] = i;

	Counter = -1;
	while (j != -1) {
		j--;
		Counter++;

		for (p = G->NodeList[Stack[j + 1]].FirstEdge; p; p = p->Next)
			if (--Indegree[p->AdjV] == 0)
				Stack[++j] = p->AdjV;
	}

	if (Counter != G->Nv - 1)
		return false;
	else
		return true;
}

int Count( Graph G, int startpoint, int LongestTime[] )
{
	int i, Num, Ltime;
	PtrToAdjVNode p;

	Num = G->Nv;
	Ltime = 0;

	for (p = G->NodeList[startpoint].FirstEdge; p; p = p->Next)
		if (LongestTime[startpoint] + p->TimeCost > LongestTime[p->AdjV])
			LongestTime[p->AdjV] = LongestTime[startpoint] + p->TimeCost;

	for (p = G->NodeList[startpoint].FirstEdge; p; p = p->Next)
		Count( G, p->AdjV, LongestTime );

	for (i = 0; i < Num; i++)
		if (LongestTime[i] > Ltime)
			Ltime = LongestTime[i];

	return Ltime;
}