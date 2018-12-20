#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NotFound -1

typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;
enum KindOfEntry {Legitimate, Empty, Deleted};
typedef struct HashTbl *HashTable;
typedef struct HashEntry Cell;
struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};
struct HashTbl
{
	int TableSize;
	Cell *TheCells;
};

HashTable InitializeTable(int TableSize);
Position Find(ElementType Key, HashTable H);
Position Insert(ElementType Key, HashTable T);
int Hash(ElementType Key, HashTable H);
int NextPrime(int X);
int IsPrime(int X);

int main(int argc, char const *argv[])
{
	int MSize, N;
	int i;
	ElementType E;
	Position Pos;

	scanf("%d %d", &MSize, &N);
	HashTable H = InitializeTable(MSize);

	for (i = 0; i < N - 1; i++)
	{
		scanf("%d", &E);
		Pos = Insert(E, H);
		if (Pos == NotFound)
			printf("- ");
		else
			printf("%d ", Pos);
	}

	scanf("%d", &E);
	Pos = Insert(E, H);
	if (Pos == NotFound)
		printf("-");
	else
		printf("%d", Pos);
	return 0;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct HashTbl));

	H->TableSize = NextPrime(TableSize);

	H->TheCells = (Cell*)malloc(sizeof(Cell) * H->TableSize);

	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

Position Find(ElementType Key, HashTable H)
{
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash(Key, H);

	while (H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].Element != Key)
	{
		CurrentPos += 2 * ++ CollisionNum - 1;
		if (CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
		if (CollisionNum > H->TableSize)
			return NotFound;
	}
	return CurrentPos;
}

Position Insert(ElementType Key, HashTable H)
{
	Position Pos;

	Pos = Find(Key, H);
	if (Pos == NotFound)
		return NotFound;

	else if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;
	}

	return Pos;
}

int Hash(ElementType Key, HashTable H)
{
	int MSize = H->TableSize;

	return Key % MSize;
}

int NextPrime(int X)
{
	for ( ; ; )
	{
		if (IsPrime(X))
			return X;
		X++;
	}
}

int IsPrime(int X)
{
	double flag = sqrt(X) + 1;
	int i;

	if (X == 1)
		return 0;
	if (X == 2)
		return 1;

	for (i = 2; i < flag; i++)
		if (X % i == 0)
			return 0;

	return 1;
}