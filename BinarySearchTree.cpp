#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

/* Basic functions */

/* 
 * Function: Max
 * Usage: Max(int a, int b);
 * -------------------------
 * This function returns the bigger element in a and b.
 */

int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/* 
 * Function: Height
 * Usage: Height(Pisition P);
 * --------------------------
 * This function returns the Height of node P.
 */

int Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

/* 
 * Function: BinSearch
 * Usage: BinSearch(SearchTree T, ElementType X);
 * ----------------------------------------------
 * This function searches for an element X in tree T.
 */

bool BinSearch(SearchTree T, ElementType X)
{
	if (T == NULL)
		return false;
	else if (X < T->Element)
		return BinSearch(T->Left, X);
	else if (X > T->Element)
		return BinSearch(T->Right, X);
		
	return true;
}

/* 
 * Function: BinInsert
 * Usage: BinInsert(SearchTree T, ElementType X);
 * ----------------------------------------------
 * This function simply inserts a new element X into tree T.
 */

SearchTree BinInsert(SearchTree T, ElementType X)
{
	if (T == NULL)
	{
		T = (SearchTree)malloc(sizeof(struct BSTNode));
		T->Element = X;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element)
		T->Left = BinInsert(T->Left, X);
	else if (X > T->Element)
		T->Right = BinInsert(T->Right, X);

	return T;
}

/* 
 * Function: BinDelete
 * Usage: BinDelete(SearchTree T, ElementType X);
 * ----------------------------------------------
 * This function simply deletes element X from tree T.
 */

SearchTree BinDelete(SearchTree T, ElementType X)
{
	Position TmpCell;

	if (T == NULL)
		return NULL;
	else if (X < T->Element)
		T->Left = BinDelete(T->Left, X);
	else if (X > T->Element)
		T->Right = BinDelete(T->Right, X);
	else if (T->Left && T->Right)
	{
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = BinDelete(T->Right, T->Element);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}

	return T;
}

/* 
 * Function: FindMin
 * Usage: FindMin(SearchTree T);
 * -----------------------------
 * This function returns the biggest element in tree T.
 */

Position FindMin(SearchTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

/* 
 * Function: FindMin
 * Usage: FindMax(SearchTree T);
 * -----------------------------
 * This function returns the smallest element in tree T.
 */

Position FindMax(SearchTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Right == NULL)
		return T;
	else
		return FindMax(T->Right);
}

/* Functions used in AVL tree */

/* 
 * Function: SingleRotateWithLeft
 * Usage: SingleRotateWithLeft(Position K2);
 * -----------------------------------------
 * This function carries out a single rotate on the left subtree of T.
 */

Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;

	return K1;
}

/* 
 * Function: SingleRotateWithRight
 * Usage: SingleRotateWithRight(Position K2);
 * ------------------------------------------
 * This function carries out a single rotate on the right subtree of T.
 */

Position SingleRotateWithRight(Position K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Right), K2->Height) + 1;

	return K1;
}

/* 
 * Function: DoubleRotateWithLeft
 * Usage: DoubleRotateWithLeft(Position K2);
 * -----------------------------------------
 * This function carries out a double rotate on the left subtree of T.
 */

Position DoubleRotateWithLeft(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

/* 
 * Function: DoubleRotateWithRIght
 * Usage: DoubleRotateWithRight(Position K2);
 * ------------------------------------------
 * This function carries out a double rotate on the right subtree of T.
 */

Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

/* 
 * Function: AvlInsert
 * Usage: AvlInsert(SearchTree T, ElementType X);
 * ----------------------------------------------
 * This function inserts a new element X into tree T and uses all
 * kinds of rotations to maintain properties of AVL tree.
 */

SearchTree AvlInsert(SearchTree T, ElementType X)
{
	if (T == NULL)
	{
		T = (SearchTree)malloc(sizeof(struct BSTNode));
		T->Element = X;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element)
	{
		T->Left = AvlInsert(T->Left, X);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = AvlInsert(T->Right, X);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

/* 
 * Function: AvlDelete
 * Usage: AvlDelete(SearchTree T, ElementType X);
 * ----------------------------------------------
 * This function deletes the element X in tree T and uses all
 * kinds of rotations to maintain properties of AVL tree.
 */

SearchTree AvlDelete(SearchTree T, ElementType X)
{
	Position TmpCell;

	if (T == NULL)
		return NULL;
	else if (X < T->Element)
	{
		T->Left = AvlDelete(T->Left, X);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (Height(T->Right->Left) > Height(T->Right->Right))
				T = DoubleRotateWithRight(T);
			else
				T = SingleRotateWithRight(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = AvlDelete(T->Right, X);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (Height(T->Left->Right) > Height(T->Left->Left))
				T = DoubleRotateWithLeft(T);
			else
				T = SingleRotateWithLeft(T);
		}
	}
	else if (T->Left && T->Right)
	{
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = BinDelete(T->Right, T->Element);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}

	if(T!=NULL) T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

/* Functions used in Splay tree */

/* Define the pointer to be used in splay functions below */

static Position NullNode = NULL;

/* 
 * Function: Initialize
 * Usage: Initialize(void);
 * ------------------------
 * This function initializes the pointer "NullNode" so that
 * other splay functions can use it.
 */

SearchTree Initialize(void)
{
	if (NullNode == NULL)
	{
		NullNode = (SearchTree)malloc(sizeof(struct BSTNode));
		NullNode->Left = NullNode->Right = NullNode;
	}
	return NullNode;
}

/* 
 * Function: Splay
 * Usage: Splay(Position T, ElementType X);
 * ----------------------------------------
 * This function first finds the element X in tree T then
 * uses all kinds of rotations to rotate node X to be
 * root of tree T.
 */

SearchTree Splay(Position T, ElementType X)
{
	static struct BSTNode Header;
	Position LeftTreeMax, RightTreeMin;
	
	Header.Left = Header.Right = NullNode;
	LeftTreeMax = RightTreeMin = &Header;
	NullNode->Element = X;

	while (X != T->Element)
	{
		if (X < T->Element)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			if (T->Left == NullNode)
				break;
			RightTreeMin->Left = T;
			RightTreeMin = T;
			T = T->Left;
		}
		else
		{
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			if (T->Right == NullNode)
				break;
			LeftTreeMax->Right = T;
			LeftTreeMax = T;
			T = T->Right;
		}
	}

	LeftTreeMax->Right = T->Left;
	RightTreeMin->Left = T->Right;
	T->Left = Header.Right;
	T->Right = Header.Left;

	return T;
}

/* 
 * Function: SplayInsert
 * Usage: SplayInsert(SearchTree T, ElementType X);
 * ------------------------------------------------
 * This function first splays tree T about element X then
 * inserts element X to be root of tree T.
 */

SearchTree SplayInsert(SearchTree T, ElementType X)
{
	static Position NewNode = NULL;

	if (NewNode == NULL)
		NewNode = (SearchTree)malloc(sizeof(struct BSTNode));
	NewNode->Element = X;

	if (T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	else
	{
		T = Splay(T, X);
		if (X < T->Element)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if (T->Element < X)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		else
			return T;
	}

	NewNode = NULL;
	return T;
}

/* 
 * Function: SplayDelet
 * Usage: SplayDelete(SearchTree T, ElementType X);
 * ------------------------------------------------
 * This function splays element X to be root of tree T then
 * delete it. After deletion if the left subtree is empty,
 * simply returns the right subtree, else splay the left subtree.
 */

SearchTree SplayDelete(SearchTree T, ElementType X)
{
	Position NewTree;

	if (T != NullNode)
	{
		T = Splay(T, X);
		if (X == T->Element)
		{
			if (T->Left == NullNode)
				NewTree = T->Right;
			else
			{
				NewTree = T->Left;
				NewTree = Splay(NewTree, X);
				NewTree->Right = T->Right;
			}
			free(T);
			T = NewTree;
		}
	}

	return T;
}
