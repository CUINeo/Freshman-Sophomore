#include <stdio.h>
#include <stdlib.h>

#define MINCOMPUTER 2
#define MAXCOMPUTER 10000

typedef enum { Input, Check, Stop } Operator;
typedef int DisjSet;
typedef int SetType;
typedef int ElementType;

void Initialize( DisjSet S[], int Num );
SetType Find( ElementType X, DisjSet S[], int Num );
void SetUnion( DisjSet S[], SetType Root1, SetType Root2 );
Operator GetOp();
void CheckandPrint( DisjSet S[], int Num );

int main(void)
{
	int Num, flag;
	SetType Root1, Root2;
	ElementType c1, c2;
	Operator Op;
	DisjSet S[MAXCOMPUTER+1];

	flag = 0;

	scanf("%d", &Num);
	Initialize(S, Num);

	while (1) {
		getchar();
		Op = GetOp();
		switch (Op) {
			case Input:
				scanf("%d %d", &c1, &c2);
				Root1 = Find( c1, S, Num );
				Root2 = Find( c2, S, Num );
				if (Root1 != 0 && Root2 != 0)
					SetUnion( S, Root1, Root2 );
				break;
			case Check:
				scanf("%d %d", &c1, &c2);
				Root1 = Find( c1, S, Num );
				Root2 = Find( c2, S, Num );
				if (Root1 == Root2 && Root1 != 0) printf("yes\n");
				else printf("no\n");
				break;
			case Stop:
				flag = 1;
				break;
		}

		if (flag == 1) break;
	}

	CheckandPrint( S, Num );

	return 0;
}

void Initialize( DisjSet S[], int Num )
{
	int i;

	for (i = Num; i > 0; i--) 
		S[i] = -1;
}

SetType Find( ElementType X, DisjSet S[], int Num )
{
	if (X > Num) return 0;

	if (S[X] < 0) 
		return X;
	else 
		return S[X] = Find( S[X], S, Num );
}

void SetUnion( DisjSet S[], SetType Root1, SetType Root2 )
{
	if (S[Root1] < S[Root2]) {
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
	else {
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
}

Operator GetOp()
{
	char c;
	Operator Op;

	scanf("%c", &c);
	if (c == 'I' || c=='i') Op = Input;
	if (c == 'C' || c=='c') Op = Check;
	if (c == 'S' || c=='s') Op = Stop;

	return Op;
}

void CheckandPrint( DisjSet S[], int Num )
{
	int i, cnt;
	cnt = 0;

	for (i = Num; i > 0; i--) 
		if (S[i] < 0) cnt++;

	if (cnt == 1) 
		printf("The network is connected.\n");
	else 
		printf("There are %d components.\n", cnt);
}
