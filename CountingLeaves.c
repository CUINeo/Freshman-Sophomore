#include <stdio.h>
#include <stdlib.h> 

#define MAXCAPACITY 100
#define END 1e8

typedef struct TreeNode *Tree;
struct TreeNode
{
	int level;
	int childnum;
};

void Print( int n );

int Node[MAXCAPACITY][MAXCAPACITY];

int main(void)
{
	int n, m, idx, childnum, i, j;

	scanf("%d %d", &n, &m);
	if ( n>MAXCAPACITY||m>=n||n==0||m<0 ) return 0;
	
	for ( i=1; i<n+1; i++ ) 
		Node[i][0] = END;
		
	for ( j=0; j<m; j++ ) {
		getchar();
		scanf("%d %d", &idx, &childnum);
				
		for ( i=0; i<childnum; i++ ) 
			scanf("%d", &Node[idx][i]);
		Node[idx][i] = END;
	}

	Print( n );

	return 0;
}

void Print( int n )
{
	int i, j, child;
	int TreeLevel[n+1];
	Tree T[n+1];

	for ( i=0; i<n+1; i++ ) 
		TreeLevel[i] = 0;

	for ( i=0; i<n+1; i++ ) 
		T[i] = (Tree)malloc(sizeof(Tree));
		
	T[1]->level = 1;
	
	for ( i=1; i<n+1; i++ ) {
		T[i]->childnum = 0;
		j = 0;
		
		child = Node[i][j];
		while ( child!=END ) {
			T[i]->childnum++;
			T[child]->level = T[i]->level+1;
			j++;
			child = Node[i][j];
		}

		if ( !T[i]->childnum ) TreeLevel[T[i]->level]++;
	}
	TreeLevel[T[n]->level+1] = END;

	for ( i=1; TreeLevel[i]!=END; i++ ) 
		printf("%d ", TreeLevel[i]);
}
