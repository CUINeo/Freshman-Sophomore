#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Constant
 * --------
 * MaxVertexNum -- The maximum value of the edges in the graph
 * INITIAL -- The initial value of the maximum edge in each class
 */

#define MaxVertexNum 1000
#define INITIAL 0
 
/* Define the edge type "edge" */

typedef struct edgStruct *edge;
struct edgStruct {
	int x;
	int y;
	double weight;
	edge Next; 
};

/* Define the graph type "G" */

typedef struct Graph G;
struct Graph {
    int Nv;
    int Ne;
    double C;
};

/* Private function prototypes */ 

void Initializeclass(int component[MaxVertexNum], double H[MaxVertexNum], G graph);
void Input(edge e0, edge flag, G Graph);
double max(double a, double b, double c);
void judge(edge flag, edge e0, int component[], double H[], G Graph);
void PrintOut(G Graph, int component[]);

/* Main Program */

int main(int argc, char *argv[]) 
{
	int i, j, k;

	int component[MaxVertexNum];
	/* The array used to store the number of points in a class */
	
	double H[MaxVertexNum];
	/* The array used to store the maximum value of edges in a class */
	
	edge e0 = (edge)malloc(sizeof(struct edgStruct));
	assert(e0 != NULL);

	edge flag = (edge)malloc(sizeof(struct edgStruct));
	assert(flag != NULL);

	e0->Next = NULL;
	/* Setting up empty node of the list */
	
	G Graph;
	/* Define the graph */

	printf("Please enter the number of the vertices Nv :");
	scanf("%d", &Graph.Nv);
	printf("\n");
	/* Get the total number of the vertices */
	
	printf("Please enter the number of the edges Ne :");
	scanf("%d", &Graph.Ne);
	printf("\n");
	/* Get the total number of the edges */
	
	printf("Please enter the number of the constant C :");
	scanf("%lf", &Graph.C);
	printf("\n");
	/* Get the total number of the constant C */
	
	printf("Please enter the data of every edge :");
	printf("\n");
	/* Prompt input edge data */

	Initializeclass(component, H, Graph);
	/* Initialize the data of classes */ 
	
	if (Graph.Ne > 0) {
	/* Get rid of the case of Ne is 0 */
	    Input(e0, flag, Graph); 
	    /* input data */

	    judge(flag,e0, component, H, Graph);
		/* Order judge data on the linked list */
	}
	
	PrintOut(Graph, component);
	/* Output results */

	system("pause");
	return 0;
}

/* 
 * Function: Initializeclass
 * Usage: initializeclass(int component[MaxVertexNum],double H[MaxVertexNum],G Graph);
 * -----------------------------------------------------------------------------------
 * This function initializes the class component[] and Maximum value of the edge in the class H[].
 */

void Initializeclass(int component[MaxVertexNum], double H[MaxVertexNum], G Graph)
{
	int i;

	for (i = 0; i < Graph.Nv; i++) {
		component[i] = -1;
		H[i] = INITIAL;
	}
}

/* 
 * Function: Input
 * Usage: Input(edge e0, edge flag, G Graph);
 * ------------------------------------------
 * This function gets information of edges and sort them
 * from small to large according to values of weight.
 */
 
void Input(edge e0, edge flag, G Graph)
{
	int i;
   	edge next = (edge)malloc(sizeof(struct edgStruct));
   	assert(next != NULL);

	for (i = 0; i < Graph.Ne; i++) {
		edge e = (edge)malloc(sizeof(struct edgStruct));
		assert(e != NULL);

		scanf("%d %d %lf", &e->x, &e->y, &e->weight);
		flag = e0;

		while (flag->Next) {
			next = flag->Next;

			if (e->weight >= next->weight)
				flag = flag->Next; 
			else {
				flag->Next = e;
				e->Next = next;
				break;
			}
	    }

	    if (!flag->Next) {
	    	flag->Next = e;
	    	e->Next = NULL;
		}	
	}
}

/* 
 * Function: max 
 * Usage: max(double a, double b, double c);
 * -----------------------------------------
 * This function selects the largest number from a, b, c. 
 */

double max(double a, double b, double c)
{
	if (a > b) {
    	if (a > c)
        	return a;
    	else
    		return c;
    }
    else {
    	if (b > c)
    		return b;
    	else
    		return c;
    }
}

/* 
 * Function: judge
 * Usage: judge(edge flag, edge e0, int component[], double H[], G Graph);
 * -----------------------------------------------------------------------
 * This function judges data of the linked list in order. If weight
 * of an edge meets the requirement(weight <= H[]-C/component[]) and
 * no circle after joining the edge, renew the data of H[] and
 * component[], execute path compression at the same time.
 */

void judge(edge flag, edge e0, int component[], double H[], G Graph)
{
	int b, c, j;
	flag = e0->Next;

	while (flag) {
		b = flag->x;
		c = flag->y;

      	while (component[b] >= 0)
			b=component[b];
		while (component[c] >= 0)
			c=component[c];
		/* find root */
		
		if (b != c && (H[b]-Graph.C/component[b]) >= flag->weight && 
			(H[c]-Graph.C/component[c]) >= flag->weight) {
	      	component[b] = component[b] + component[c];
	      	component[c] = b;
	      	/* Update the number of points in the component */
	      	
	      	H[b] = max(H[b], H[c], flag->weight);
	      	/* Update the Maximum value of the edge */
	      	
	      	for (j = c; j < Graph.Nv; j++)
				if (component[j] == c)
					component[j] = b;
			/* Path compression */
    	}

    	flag = flag->Next;
    }
}

/* 
 * Function: PrintOut 
 * Usage: PrintOut(G Graph, int component[]);
 * ------------------------------------------
 * This function prints array component[]
 * as requirement(printf from min to max,
 * newline after printf a component)
 */

void PrintOut(G Graph, int component[])
{
	int i, j;

	for (j = 0; j < Graph.Nv; j++) {
		if (component[j] < 0) {
			printf("%d", j);

			for (i = j; i < Graph.Nv; i++)
				if (component[i] == j)
					printf(" %d",i);
				
			printf("\n");
		} 
	}
}