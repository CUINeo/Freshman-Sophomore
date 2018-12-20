#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkipList.h"

#define MaxLevel 100
#define NILValue 0x7fffffff

SList CreateList() {
	/* create a NIL node */
	SLNode NIL = (SLNode)malloc(sizeof(struct Node));
	NIL->value = NILValue;

	/* create and initialize a new skip list */
	SList newList = (SList)malloc(sizeof(struct List));      
	newList->level = 0;
	newList->size = 0;

	/* create and initialize head of the new skip list */
	int NodeSpace = sizeof(Node) + MaxLevel * sizeof(SLNode);  //calculate the space that a new node needs
	newList->head = (SLNode)malloc(NodeSpace);
	newList->head->value = 0;

	for (int i = 0; i < MaxLevel; i++)
		newList->head->next[i] = NIL;			//make all the subsequent nodes of head node be the NIL node
	
	return newList;
}

void FreeList(SList list) {
	SLNode t2;
	SLNode t1 = list->head;

	while (t1->value != NILValue) {	//the subsequent node of t1 is NIL
		t2 = t1->next[0];
		free(t1);			//free the node
		t1 = t2;			//update the next node to be freed
	}			//release the space of the nodes in skip list in turn

	free(t1);
	free(list);
}

bool Search(valueType value, SList list) {
	SLNode x = list->head;
	
	for (int i = list->level; i >= 0; i--) {
		while (x->next[i]->value < value) {
			x = x->next[i];
		}
	}

	x = x->next[0];

	if (x->value == value)	//node with given value is found
		return true;
	else                	//node with given value isn't found
		return false;
}

bool Insert(valueType value, SList list) {
	int i;
	SLNode x = list->head;
	SLNode update[MaxLevel];	//update array is used to store the nodes that will be used to update pointers
	
	for (i = list->level; i >= 0; i--) {		//in every level
		while (x->next[i]->value < value) {		//find the node with maximum value less than the given value
			x = x->next[i];
		}

		update[i] = x;				//store the node
	}

	x = x->next[0];

	if (x->value == value) {   		//node with the given value exists
		//printf("The node %d has already existed.\n", value);
		return false;
	}
	
	int newLevel = RandomizeLevel();
	if (newLevel > list->level) {
		for (i = list->level + 1; i <= newLevel; i++)
			update[i] = list->head;
		list->level = newLevel;
	}
	
	int NodeSpace = sizeof(Node) + (MaxLevel) * sizeof(SLNode);  //calculate the space that a new node needs
	SLNode newNode = (SLNode)malloc(NodeSpace);
	newNode->value = value;

	for (i = 0; i <= list->level; i++) {
		newNode->next[i] = update[i]->next[i];
		update[i]->next[i] = newNode;			//insert the node
	}

	list->size++;	//update the current size of skip list
	return list;
}

bool Delete(valueType value, SList list) {
	int i;
	SLNode x = list->head;
	SLNode update[MaxLevel];

	for (i = list->level; i >= 0; i--) {   //in every level
		while (x->next[i]->value < value)  //find the node with maximum value less than the given value
			x = x->next[i];

		update[i] = x;
	}

	x = x->next[0];

	if (x->value != value){  		//node with the given value does't exist
		//printf("The node %d does not exists.\n", value);
		return false;
	}

	for (i = 0; i <= list->level; i++) {	//delete the node
		if (update[i]->next[i] != x)
			break;

		update[i]->next[i] = x->next[i];
	}

	free(x);	//free the node

	while (list->head->next[list->level]->value == NILValue && list->level > 0)
		list->level--;			//update the current level of skip list

	list->size--;		//update the current size of skip list
	return list;
}

int RandomizeLevel() {
	int l = 0;
	
	while (rand()%2)
		l++;		//like tossing a coin, if result is 1, then go up for a level
	return l;
}
