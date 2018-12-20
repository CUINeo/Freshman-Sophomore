#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 30

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;
	int Level;
};

Tree *Zigzag(Tree T);
void Print(Tree *LevelOrder, int Num);
Tree BuildTree(ElementType *Inorder, ElementType *Postorder, int Num, int Level);

int main()
{
	int Num, i;
	ElementType Inorder[MAXNODES], Postorder[MAXNODES];
	
	printf("Please enter the total number of nodes(no more than 30):\n");
	enteragain:
	scanf("%d", &Num);
	if (Num > 30) {
		printf("Too many nodes! Please try again:\n");
		goto enteragain;
	}

	printf("Now please give the inorder sequence of the tree:\n");
	getchar();
	for (i = 0; i < Num; i++)
		scanf("%d", &Inorder[i]);

	printf("Now please give the postorder sequence of the tree:\n");
	getchar();
	for (i = 0; i < Num; i++)
		scanf("%d", &Postorder[i]);

	Tree T = BuildTree(Inorder, Postorder, Num, 0);
	Tree *LevelOrder = Zigzag(T);
	Print(LevelOrder, Num);

	return 0;
}

Tree *Zigzag(Tree T)
{
	int rear, top;
	Tree Current;
	Tree *Queue = (Tree*)malloc(MAXNODES * sizeof(Tree));

	rear = 0;
	top = -1;

	if (T == NULL) {
		printf("Empty Tree\n");
		return NULL;
	}
	else
		Queue[++top] = T;

	 while (top >= rear) {
		Current = Queue[rear++];

		if (Current->Left)
			Queue[++top] = Current->Left;
		if (Current->Right)
			Queue[++top] = Current->Right;
	}

	return Queue;
}

void Print(Tree *LevelOrder, int Num)
{
	int i, j, k, cnt;
	Tree Tn;
	ElementType E;

	printf("The zigzag order sequence of the tree is:\n");
	
	for (cnt = 0, i = 0; cnt < Num; ) {
		Tn = LevelOrder[i];

		if (Tn->Level % 2 == 0) {
			for (j = i; LevelOrder[j]->Level % 2 == 0; j++) 
				if (j == Num - 1) {
					j++;
					break;
				}

			for (k = j - 1; k >= i; k--) {
				E = LevelOrder[k]->Element;

				if (cnt != Num - 1)
					printf("%d ", E);
				else
					printf("%d", E);

				cnt++;
			}

			i = j;
		}
		else {
			E = Tn->Element;
			i++;

			if (cnt != Num - 1)
				printf("%d ", E);
			else
				printf("%d", E);

			cnt++;
		}
	}

	printf("\n");
}

Tree BuildTree(ElementType *Inorder, ElementType *Postorder, int Num, int Level)
{
	if (Num == 0)
		return NULL;

	int i;

	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->Element = Postorder[Num - 1];
	T->Level = Level;

	for (i = 0; i < Num; i++)
		if (Inorder[i] == Postorder[Num - 1])
			break;

	T->Left = BuildTree(Inorder, Postorder, i, Level + 1);
	T->Right = BuildTree(Inorder + i + 1, Postorder + i, Num - i - 1, Level + 1);

	return T;
}