#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 30
#define MAXOPCHAR 10

typedef enum { push, pop } Operation;

Operation GetOp();
void InorderToPostorder( int a[], int b[], int len );

static int ROOT;

int main(void)
{
	int Stack[MAXNODES];
	int* Inorder = (int*)malloc(sizeof(int)*MAXNODES);
	int* Preorder = (int*)malloc(sizeof(int)*MAXNODES);
	int* p = Inorder;
	int* q = Preorder;
	int idx, n, num;
	Operation op;
	idx = -1;

	scanf("%d", &n);
	for ( i=0; i<2*n; i++ ) {
		op = GetOp();
		switch ( op ) {
			case push:
				scanf("%d", &num);
				*q++ = num;
				Stack[++idx] = num;
				break;
			case pop:
				*p++ = Stack[idx--];
				break;
		}
	}
	
	ROOT = Preorder[0];

	InorderToPostorder( Inorder, Preorder, n );
	printf("%d", ROOT);
	
	return 0;
}

Operation GetOp()
{
	char *temp = (char*)malloc(MAXOPCHAR);

	getchar();
	scanf("%s", temp);
	if ( strcmp(temp, "push")==0 || strcmp(temp, "Push")==0 ) return push;
	if ( strcmp(temp, "pop")==0 || strcmp(temp, "Pop")==0 ) return pop;
}

void InorderToPostorder( int a[], int b[], int len )
{
	int i, j, root, rootidx;
	  
	if ( len==0 ) return;

	root = b[0];
	for ( i=0; i<len; i++ ) {
	    if (a[i]==root){
	      	rootidx=i;
	      	break;
	    }
	}

	InorderToPostorder(a, b+1, rootidx);
	InorderToPostorder(&a[rootidx+1], &b[rootidx+1], len-rootidx-1);
	if ( root!=ROOT ) printf("%d ", root);

	return;
}