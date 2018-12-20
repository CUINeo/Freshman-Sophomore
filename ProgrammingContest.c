#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define MaxProblem 10
#define MaxNameLen 20
#define Solved 1
#define UnSolved -1
#define Infinity 100000
#define PenaltyTime 20

typedef struct _problem *Problem;
struct _problem
{
	char *Name;
	int Ptime;
	int Dtime;
	int Solve;
};

int HourToMinute(int Hour);
void Program(int Minute, int Pnumber, int Rtime);
void DecideOrder(Problem *ProSet, int *ProblemOrder, int Pnumber, 
	int *TotalTime, int *MaxSolvedNumber, int Rtime, int Minute);
int AllSolved(Problem *ProSet, int Pnumber);
int TimeCounter(int CurrentTime);

int main()
{
	int Hour, Pnumber, Rtime;

	while (True)
	{
		scanf("%d %d %d", &Hour, &Pnumber, &Rtime);
		if (Hour < 0)
			break;
		else
			Program(HourToMinute(Hour), Pnumber, Rtime);
	}

	return 0;
}

int HourToMinute(int Hour)
{
	int Minute;
	Minute = Hour * 60;
	return Minute;
}

void Program(int Minute, int Pnumber, int Rtime)
{
	int SolvedNumber, TotalTime;
	int ProblemOrder[MaxProblem];
	char N[MaxNameLen];
	Problem ProSet[MaxProblem];

	for (int i = 0; i < Pnumber; i++)
	{
		ProSet[i] = (Problem)malloc(sizeof(struct _problem));
		ProSet[i]->Name = (char*)malloc(sizeof(MaxNameLen));
		scanf("%s %d %d", N, &ProSet[i]->Ptime, &ProSet[i]->Dtime);
		strcpy(ProSet[i]->Name, N);
		ProSet[i]->Solve = UnSolved;
	}

	TotalTime = Infinity;
	SolvedNumber = 0;
	DecideOrder(ProSet, ProblemOrder, Pnumber, &TotalTime, &SolvedNumber, Rtime, Minute);

	printf("Total Time = %d\n", TotalTime);
	for (int i = 0; i < SolvedNumber; i++)
		printf("%s\n", ProSet[ProblemOrder[i]]->Name);
}

void DecideOrder(Problem *ProSet, int *ProblemOrder, int Pnumber,
	int *TotalTime, int *MaxSolvedNumber, int Rtime, int Minute)
{ 
	static int CurrentTime = 0;
	static int CurrentTotalTime = 0;
	static int CurrentSolvedNumber = 0;
	static int CurrentOrder[MaxProblem];

	if (CurrentTime == 0)
		CurrentTime += Rtime;

	int save_CT = CurrentTime;
	int save_CSN = CurrentSolvedNumber;
	int save_CTT = CurrentTotalTime;

	for (int i = 0; i < Pnumber; i++)
	{
		if (ProSet[i]->Solve == UnSolved)
		{
			ProSet[i]->Solve = Solved;
			CurrentTime += ProSet[i]->Ptime;
			int H = TimeCounter(CurrentTime);
			CurrentOrder[CurrentSolvedNumber++] = i;
			CurrentTime += (H * ProSet[i]->Dtime);

			if (CurrentTime <= Minute)
			{
				CurrentTotalTime += (CurrentTime + H * PenaltyTime);
				DecideOrder(ProSet, ProblemOrder, Pnumber, TotalTime, MaxSolvedNumber, Rtime, Minute);

				if (AllSolved(ProSet, Pnumber))
				{
					if (CurrentSolvedNumber > *MaxSolvedNumber ||
						(CurrentSolvedNumber == *MaxSolvedNumber && CurrentTotalTime < *TotalTime))
					{
						*TotalTime = CurrentTotalTime;
						*MaxSolvedNumber = CurrentSolvedNumber;
						for (int j = 0; j < *MaxSolvedNumber; j++)
							ProblemOrder[j] = CurrentOrder[j];

						ProSet[i]->Solve = UnSolved;
						CurrentSolvedNumber = save_CSN;
						CurrentTime = save_CT;
						CurrentTotalTime = save_CTT;
					}
				}

				ProSet[i]->Solve = UnSolved;
				CurrentSolvedNumber = save_CSN;
				CurrentTime = save_CT;
				CurrentTotalTime = save_CTT;
			}
			else
			{
				ProSet[i]->Solve = UnSolved;
				CurrentSolvedNumber--;

				if (CurrentSolvedNumber > *MaxSolvedNumber ||
					(CurrentSolvedNumber == *MaxSolvedNumber && CurrentTotalTime < *TotalTime))
				{
					*TotalTime = CurrentTotalTime;
					*MaxSolvedNumber = CurrentSolvedNumber;
					for (int j = 0; j < *MaxSolvedNumber; j++)
						ProblemOrder[j] = CurrentOrder[j];
				}
				ProSet[i]->Solve = UnSolved;
				CurrentSolvedNumber = save_CSN;
				CurrentTime = save_CT;
				CurrentTotalTime = save_CTT;
			}
		}
	}
}

int AllSolved(Problem *ProSet, int Pnumber)
{
	int flag = 1;

	for (int i = 0; i < Pnumber; i++)
		if (ProSet[i]->Solve == UnSolved)
		{
			flag = 0;
			break;
		}

	return flag;
}

int TimeCounter(int CurrentTime)
{
	int H = CurrentTime / 60;
	if (CurrentTime % 60 == 0)
		H -= 1;

	return H;
}