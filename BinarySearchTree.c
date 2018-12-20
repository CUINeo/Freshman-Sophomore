#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Bst.h"

clock_t start, stop;
double duration;

#define INPUT_SIZE 1000
#define RUN_TIMES 100

int main(int argc, char const *argv[])
{	
	int i, times;
	SearchTree T = NULL;
	SearchTree ST = Initialize();
	//Part I: Insert N intergers in increasing order and delete them in the same order.
	printf("Part I: \n");
	// For Basic BST
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			T = Insert(T, i);
		for(i=0; i<INPUT_SIZE; i++)
			T = Delete(T, i);
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Basic BST's runtime in part I: %.10lf \n", duration/RUN_TIMES);
	
	// For AVL Tree:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			T = AvlInsert(T, i);
		for(i=0; i<INPUT_SIZE; i++)
			T = AvlDelete(T, i);
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("AVL Tree's runtime in part I: %.10f \n", duration/RUN_TIMES);
	
	// For Splay Tree
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			ST = SplayInsert(ST, i);
		for(i=0; i<INPUT_SIZE; i++)
			ST = SplayDelete(ST, i);
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Splay Tree's runtime in part I: %.10lf \n", duration/RUN_TIMES);	
	
	//Part II: Insert N intergers in increasing order and delete them in the reverse order.
	printf("\nPart II: \n");
	// For Basic BST:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			T = Insert(T, i);
		for(i=INPUT_SIZE-1; i>=0; i--)
			T = Delete(T, i);
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Basic BST's runtime in part II: %.10lf \n", duration/RUN_TIMES);
	
	// For AVL Tree:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			T = AvlInsert(T, i);
		for(i=INPUT_SIZE-1; i>=0; i--)
			T = AvlDelete(T, i);
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("AVL Tree's runtime in part II: %.10lf \n", duration/RUN_TIMES);
	
	// For Splay Tree:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
			ST = SplayInsert(ST, i);
		for(i=INPUT_SIZE-1; i>=0; i--)
			ST = SplayDelete(ST, i);
	} 
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Splay Tree's runtime in part II: %.10lf \n", duration/RUN_TIMES);	
	
	 //Part III: Insert N intergers in random order and delete them in random order.
	printf("\nPart III: \n");
	srand((int)time(NULL));
	int *RandNum = (int*)malloc(INPUT_SIZE*sizeof(int));
	for(i=0; i<INPUT_SIZE; i++)
		RandNum[i] = i;
	int CurrentRand, Index;
	// For basic BST:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			T = Insert(T, CurrentRand);
		}
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			T = Delete(T, CurrentRand);
		}
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Basic BST's runtime in part III: %.10lf \n", duration/RUN_TIMES);	
	
	// For AVL Tree:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			T = AvlInsert(T, CurrentRand);
		}
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			T = AvlDelete(T, CurrentRand);
		}
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("AVL Tree's runtime in part III: %.10lf \n", duration/RUN_TIMES);	

	// For Splay Tree:
	start = clock();
	for(times=0; times<RUN_TIMES; times++)
	{
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			ST = SplayInsert(ST, CurrentRand);
		}
		for(i=0; i<INPUT_SIZE; i++)
		{
			Index = rand()*(INPUT_SIZE-i)/RAND_MAX;
			CurrentRand = RandNum[Index];
			RandNum[Index] = RandNum[INPUT_SIZE-1-i];
			//RandNum[INPUT_SIZE-1-i] = CurrentRand;
			ST = SplayDelete(ST, CurrentRand);
		}
	}
	stop = clock();
	duration = ((double)stop-start)/CLK_TCK;
	printf("Splay Tree's runtime in part III: %.10lf \n", duration/RUN_TIMES);		
	
	
	return 0;
}
