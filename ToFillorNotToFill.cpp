#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class GasStation
{
public:
	GasStation() { }
	GasStation(double price, double distance)
	{
		SetPrice(price);
		SetDistance(distance);
	}
	void SetPrice(double price)
	{
		Price = price;
	}
	void SetDistance(double distance)
	{
		Distance = distance;
	}
	double GetPrice()
	{
		return Price;
	}
	double GetDistance()
	{
		return Distance;
	}
private:
	double Price;
	double Distance;
};

class Highway
{
public:
	GasStation *Stations;

	Highway() { }
	Highway(int stationnum, double tdistance, double distperunit, double tankcapacity)
	{
		StationNum = stationnum;
		Tdistance = tdistance;
		DistPerUnit = distperunit;
		TankCapacity = tankcapacity;
		MaxDistance = TankCapacity * DistPerUnit;
		Stations = (GasStation*)malloc(sizeof(GasStation) * (StationNum+1));
	}
	void Exchange(int i, int j)
	{
		GasStation TempG(Stations[i].GetPrice(), Stations[i].GetDistance());
		Stations[i] = Stations[j];
		Stations[j] = TempG;
	}
	void SortbyDist()
	{
		for (int i = 0; i < StationNum; i++)
			for (int j = i; j < StationNum; j++)
				if (Stations[j].GetDistance() < Stations[i].GetDistance())
					Exchange(i, j);
	}
	void FillOrNot()
	{
		int CurrentStation;
		double CurrentGas, CurrentDist, CurrentCost;
		CurrentGas = CurrentDist = CurrentCost = 0;
		CurrentStation = 0;

		if (Stations[0].GetDistance() > 0)
		{
			cout << "The maximum travel distance = 0.00" << endl;
			return;
		}

		while (true)
		{
			if (CurrentDist == Tdistance)
			{
				cout << setiosflags(ios::fixed) << setprecision(2) << CurrentCost << endl;
				return;
			}
			else if (CurrentDist + MaxDistance < Stations[CurrentStation + 1].GetDistance())
			{
				cout << "The maximum travel distance = " 
					<< setiosflags(ios::fixed) << setprecision(2) 
					<< CurrentDist + MaxDistance << endl;
				return;
			}
			else
			{
				bool Found = false;
				int CheapStation = CurrentStation;
				for (int i = CurrentStation+1; CurrentDist + MaxDistance >= Stations[i].GetDistance(); i++)
					if (Stations[i].GetPrice() <= Stations[CurrentStation].GetPrice())
					{
						CheapStation = i;
						Found = true;
						break;
					}
				if (Found)
				{
					double DistToGo = Stations[CheapStation].GetDistance() - Stations[CurrentStation].GetDistance();
					if (DistToGo > CurrentGas * DistPerUnit)
					{
						CurrentCost += (DistToGo / DistPerUnit - CurrentGas) * Stations[CurrentStation].GetPrice();
						CurrentGas = DistToGo / DistPerUnit;
					}
				}
				else
				{
					CurrentCost += (TankCapacity - CurrentGas) * Stations[CurrentStation].GetPrice();
					CurrentGas = TankCapacity;
				}
			}
			CurrentStation++;
			CurrentGas -= (Stations[CurrentStation].GetDistance() - CurrentDist) / DistPerUnit;
			CurrentDist = Stations[CurrentStation].GetDistance();
		}
	}
	~Highway()
	{
		delete Stations;
	}
private:
	int StationNum;
	double Tdistance;
	double DistPerUnit;
	double TankCapacity;
	double MaxDistance;
};

int main()
{
	int Sn;
	double Td, Dpu, Tc, price, distance;
	cin >> Tc >> Td >> Dpu >> Sn;
	Highway H(Sn, Td, Dpu, Tc);

	for (int i = 0; i < Sn; i++)
	{
		cin >> price >> distance;
		H.Stations[i].SetPrice(price);
		H.Stations[i].SetDistance(distance);
	}
	H.Stations[Sn].SetPrice(-1);
	H.Stations[Sn].SetDistance(Td);

	H.SortbyDist();
	H.FillOrNot();
}