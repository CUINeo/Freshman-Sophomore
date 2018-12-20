#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "SkipList.h"
#include "Generator.h"

#define RUN_TIMES 10000

int main(void) {
	int i;
	DWORD start, stop;							// Set the timer
	double SL_Insert, SL_Delete, SL_Search;		// Time span for skip list

	double* RandomList = Generator(RUN_TIMES);
	SList list = CreateList();					// Create a skip list

	// Skip list insertion
	start = GetTickCount();
	for (i = 0; i < RUN_TIMES; i++)
		Insert(RandomList[i], list);
	stop = GetTickCount();
	SL_Insert = ((double)stop-start);

	// Skip list search
	start = GetTickCount();
	for (i = 0; i < RUN_TIMES; i++)
		Search(RandomList[i], list);
	stop = GetTickCount();
	SL_Search = ((double)stop-start);

	// Skip list deletion
	start = GetTickCount();
	for (i = 0; i < RUN_TIMES; i++)
		Delete(RandomList[i], list);
	stop = GetTickCount();
	SL_Delete = ((double)stop-start);

	// Print out results
	printf("Skip list insertion: %.8lf\n", SL_Insert);
	printf("Skip list search: %.8f\n", SL_Search);
	printf("Skip list deletion: %.8lf\n", SL_Delete);
	
	system("pause"); 
}
