#include <stdio.h>
#include <stdlib.h>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
typedef int ElementType;
struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

int Max(int a, int b);
int Height(Position P);
AvlTree Insert(ElementType X, AvlTree T);
Position SingleRotateWithLeft(Position K2);
Position SingleRotateWithRight(Position K2);
Position DoubleRotateWithLeft(Position K3);
Position DoubleRotateWithRight(Position K3);

int main(void)
{
	int i, N;
	ElementType X;
	AvlTree T;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &X);
		T = Insert(X, T);
	}

	printf("%d", T->Element);
	return 0;
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Height (Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->Element = X;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element)
	{
		T->Left = Insert(X, T->Left);
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
		T->Right = Insert(X, T->Right);
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

Position DoubleRotateWithLeft(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}