#pragma once

typedef int valueType;

//construct the structure of a skip list's node
typedef struct Node *SLNode;
struct Node {
	valueType value;
	SLNode next[1];  //an array that points to the subsequent node of corresponding level
};

//construct the structure of a skip list
typedef struct List *SList;
struct List {
	int level;
	int size;
	SLNode head;     //head node of the skip list
};

/*-------------------------------------------------------
Function: CreateList()
Parameter: none
Return value: the created skip list
This function is used to create a new skip list 
-------------------------------------------------------*/
SList CreateList();

/*-------------------------------------------------------
Function: FreeList(SList list)
Parameter: skip list
Return value: none
This function is used to release the space that the 
skip list occupies
-------------------------------------------------------*/
void FreeList(SList list);

/*-------------------------------------------------------
Function: Search(valueType value, SList list)
Parameter: value of SLNode, skip list
Return value: bool
This function is used to search a node with the given 
value. It returns true if the node is found, returns false 
if the node doesn't exist.
-------------------------------------------------------*/
bool Search(valueType value, SList list);

/*-------------------------------------------------------
Function: Insert(valueType value, SList list)
Parameter: value of SLNode, skip list
Return value: skip list
This function is used to insert a SLNode to the skip list.
If a node with given value exists, print hint information,
otherwise returns true
-------------------------------------------------------*/
bool Insert(valueType value, SList list);

/*-------------------------------------------------------
Function: Delete(valueType value, SList list)
Parameter: value of SLNode, skip list
Return value: skip list
This function is used to delete a SLNode from the skip list,
if the node with given value doesn't exist, print hint 
information, otherwise returns true
-------------------------------------------------------*/
bool Delete(valueType value, SList list);

/*-------------------------------------------------------
Function: RandomizeLevel();
Parameter: none
Return value: int
This function is used to create a rendom level
-------------------------------------------------------*/
int RandomizeLevel();