#ifndef _Bst_H 
#define _Bst_H

/* 
 * Define struct "BSTNode" and its pointer "Position","SearchTree"
 * Define type "ElementType" using type "int"
 */
struct BSTNode;
typedef struct BSTNode *Position;
typedef struct BSTNode *SearchTree;
typedef int ElementType;
struct BSTNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
	int Height;
};

/* Basic functions */
int Max(int a, int b);
int Height(Position P);
SearchTree Insert(SearchTree T, ElementType X);
SearchTree Delete(SearchTree T, ElementType X);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);

/* Functions used in AVL tree */
Position SingleRotateWithLeft(Position K2);
Position SingleRotateWithRight(Position K2);
Position DoubleRotateWithLeft(Position K3);
Position DoubleRotateWithRight(Position K3);
SearchTree AvlInsert(SearchTree T, ElementType X);
SearchTree AvlDelete(SearchTree T, ElementType X);

/* Functions used in Splay tree */
SearchTree Initialize(void);
SearchTree Splay(Position T, ElementType X);
SearchTree SplayInsert(SearchTree T, ElementType X);
SearchTree SplayDelete(SearchTree T, ElementType X);

#endif
