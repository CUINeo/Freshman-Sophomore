#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 110

typedef int ElementType;
typedef struct _node *Node;
struct _node
{
	Node firstchild;
	Node secondchild;
	ElementType element;
};

static int NodeNum;
static ElementType Element[MAXNODES];
static Node NodeArray[MAXNODES];
void Initialize();
void BuildBinarySearchTree();
void Sort();
void Swap(int i, int j);
void Inorder(Node p);
void PrintOut();

int main(void)
{
	scanf("%d", &NodeNum);
	if (!NodeNum) return 0;

	int i, fchild, schild;
	Node ptr;
	Initialize();

	for (i = 0; i<NodeNum; i++) {
		getchar();
		scanf("%d %d", &fchild, &schild);

		ptr = NodeArray[i];
		ptr->firstchild = NodeArray[fchild];
		ptr->secondchild = NodeArray[schild];
	}

	getchar();
	for (i = 0; i<NodeNum; i++)
		scanf("%d", &Element[i]);

	BuildBinarySearchTree();
	PrintOut();

	return 0;
}

void Initialize()
{
	int i;

	for (i = 0; i<NodeNum; i++) {
		Node p = (Node)malloc(sizeof(struct _node));
		p->firstchild = p->secondchild = NULL;

		NodeArray[i] = p;
	}
}

void BuildBinarySearchTree()
{
	Sort();
	Inorder(NodeArray[0]);
}

void Sort()
{
	int i, j, looptimes;

	looptimes = NodeNum;
	while (looptimes--) {
		for (i = 0; i<NodeNum; i++)
			for (j = i; j<NodeNum; j++)
				if (Element[i]>Element[j])
					Swap(i, j);
	}
}

void Swap(int i, int j)
{
	int temp;

	temp = Element[i];
	Element[i] = Element[j];
	Element[j] = temp;
}

void Inorder(Node p)
{
	static int idx = 0;

	if (p == NULL) return;

	Inorder(p->firstchild);
	p->element = Element[idx++];
	Inorder(p->secondchild);
}

void PrintOut()
{
	Node LevelOrder[MAXNODES];
	int rear, top;
	rear = top = 0;
	LevelOrder[0] = NodeArray[0];

	while (1) {
		if (rear > top) break;

		if (LevelOrder[rear]->firstchild)
			LevelOrder[++top] = LevelOrder[rear]->firstchild;
		if (LevelOrder[rear]->secondchild)
			LevelOrder[++top] = LevelOrder[rear]->secondchild;
		
		if (rear == top) printf("%d", LevelOrder[rear++]->element);
		else printf("%d ", LevelOrder[rear++]->element);
	}
}