#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Constant
 * --------
 * MAXNODES -- Max nodes in the binary tree
 * NILELEMENT -- the element of pointer NIL
 * true -- as the return value which represents TRUE
 * flase -- as the return value which represents FALSE
 */

#define MAXNODES 30
#define NILELEMENT 1e8
#define true 1
#define false 0

/* 
 * Define type "Col" which records the colour of nodes
 * Define type "RBTreeNode" and its pointer type "Tree"
 */

typedef enum { RED, BLACK } Col;
typedef int ElementType;
typedef struct RBTreeNode* Tree;
struct RBTreeNode
{
	Tree left;
	Tree right;
	Col colour;
	ElementType element;
};

/* Define the leaf node NIL */
static Tree NIL;

/* Private function prototypes */ 

void InitializeNIL();
Tree BuildSearchTree(ElementType Node[], int len);
Tree Insert(ElementType X, Tree T);
int RBTJudge(Tree T);
int JudgebyRedNode(Tree T);
int JudgebyBlackNode(Tree T);
int IsBlance(Tree T, int count, int num);
void FreeTree(Tree T);

/* Main Program */

int main(void)
{
	int i, n, looptimes;
	ElementType Node[MAXNODES];

	/* Initialize the leaf node NIL */
	InitializeNIL();

	/* Get the total number of the cases */
	printf("Please enter the total number of the cases(K): ");
	scanf("%d", &looptimes);
	printf("\n");

	while (looptimes--) {
		/* Get the value of N */
		printf("Please enter the total number of nodes in the binary tree(N):\n");
		scanf("%d", &n);

		/* Get the preorder traversal sequence of the tree */
		printf("Please give the preorder traversal sequence of the tree:\n");
		for (i = 0; i<n; i++)
			scanf("%d", &Node[i]);

		/* Build the search tree */
		Tree T = BuildSearchTree(Node, n);

		/* Judge if the search tree is a Red-Black tree */
		if (RBTJudge(T)) printf("This tree is a Red-Black tree.\n\n");
		else printf("This tree is not a Red-Black tree.\n\n");

		/* Free the tree */
		FreeTree(T);
	}

	/* Free the leaf node NIL */
	free(NIL);

	system("pause");
	return 0;
}

/* 
 * Function: InitializeNIL
 * Usage: InitializeNIL();
 * -----------------------
 * This function initializes the leaf node NIL.
 */

void InitializeNIL()
{
	NIL = (Tree)malloc(sizeof(struct RBTreeNode));
	assert(NIL != NULL);
	NIL->left = NIL->right = NULL;
	NIL->colour = BLACK;
	NIL->element = NILELEMENT;
}

/* 
 * Function: BuildSearchTree
 * Usage: BuildSearchTree(ElementType Node[], int len);
 * ----------------------------------------------------
 * This function builds a search tree using the elements entered.
 */

Tree BuildSearchTree(ElementType Node[], int len)
{
	if (len == 0) return NULL;

	int i;
	Tree T = NULL;
	for (i = 0; i<len; i++)
		T = Insert(Node[i], T);

	return T;
}

/* 
 * Function: Insert
 * Usage: Insert(ElementType X, Tree T);
 * -------------------------------------
 * This function inserts element X into the search tree T.
 */

Tree Insert(ElementType X, Tree T)
{
	int XABS, flag;
	if (X >= 0) {
		XABS = X;
		flag = 1;
	}
	else {
		XABS = -X;
		flag = -1;
	}

	if (T == NULL || T == NIL) {
		Tree p = (Tree)malloc(sizeof(struct RBTreeNode));
		assert(p != NULL);
		p->left = p->right = NIL;
		p->element = XABS;
		if (flag == 1) p->colour = BLACK;
		else p->colour = RED;
		T = p;
	}
	else if (XABS<T->element)
		T->left = Insert(X, T->left);
	else if (XABS>T->element)
		T->right = Insert(X, T->right);

	return T;
}

/* 
 * Function: RBTJudge
 * Usage: RBTJudge(Tree T);
 * ------------------------
 * This function judges if a search tree is a Red-Black tree.
 */

int RBTJudge(Tree T)
{
	if (T == NULL) return true;

	if (T->colour == RED) return false;
	if (!JudgebyRedNode(T)) return false;
	if (!JudgebyBlackNode(T)) return false;

	return true;
}

/* 
 * Function: JudgebyRed
 * Usage: JudgebyRed(Tree T);
 * --------------------------
 * This function judges if red nodes in the tree T have red
 * children using recursive algorithm.
 */

int JudgebyRedNode(Tree T)
{
	if (T == NULL) return true;

	if (T->colour == RED)
		if (T->left->colour == RED || T->right->colour == RED)
			return false;

	if (T->left != NIL)
		if (!JudgebyRedNode(T->left)) return false;

	if (T->right != NIL)
		if (!JudgebyRedNode(T->right)) return false;

	return true;
}

/* 
 * Function: JudgebyBlackNode
 * Usage: JudgebyBlackNode(Tree T);
 * --------------------------------
 * This function records the number of black nodes contained by
 * the simple path from the root of tree T to leftmost descendant
 * leaf and calls function IsBlance to judge if tree T is a 
 * Red-Blcak tree.
 */

int JudgebyBlackNode(Tree T)
{
	if (T == NULL) return true;

	Tree ptr = T;
	int count = 0;

	while (true) {
		if (ptr->colour == BLACK) count++;
		if (ptr == NIL) break;
		ptr = ptr->left;
	}

	return 
		IsBlance(T, count, 0) && JudgebyBlackNode(T->left)
		&& JudgebyBlackNode(T->right);
}

/* 
 * Function: IsBlance
 * Usage: IsBlance(Tree T, int count, int num);
 * --------------------------------------------
 * This function judges if all simple paths from any node to 
 * descendant leaves contain the same number of black nodes.
 */

int IsBlance(Tree T, int count, int num)
{
	if (T == NULL) return true;

	if (T->colour == BLACK) num++;
	if (T == NIL) {
		if (num != count) return false;
		else return true;
	}

	return
		(IsBlance(T->left, count, num) && IsBlance(T->right, count, num));
}

/* 
 * Function: FreeTree
 * Usage: FreeTree(Tree T);
 * ------------------------
 * This function frees the memory allocated before.
 */

void FreeTree(Tree T)
{
	if (T == NULL) return;
	if (T->left != NIL) FreeTree(T->left);
	if (T->right != NIL) FreeTree(T->right);

	free(T);
	return;
}