#pragma once
#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

int PlanszaWew[10][10]{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
char PlanszaWyswietlana[10][10]{ 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF };

int WielkoscPlanszy = 6;

class Clas
{
public:
	void WyswietlTabliceZew();
	void WyswietlTabliceWew();
	void GenerowanieSciany();
	void GenerowaniePlanszy();
};

void Clas::WyswietlTabliceZew()
{
	char x = 0xC4, y = 0xC5, z = 0xB3;
	cout << "Tablica docelowa " << endl;
	cout << "    ";
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << i + 1;
	}
	cout << endl << "   " << y;

	for (int i = 1; i <= WielkoscPlanszy; i++)
		cout << x << x << x;
	cout << endl;
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << z;
		for (int j = 0; j <= WielkoscPlanszy - 1; j++)
		{
			cout.width(3);
			cout << PlanszaWyswietlana[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Clas::WyswietlTabliceWew()
{
	char x = 0xC4, y = 0xC5, z = 0xB3;
	cout << "Tablica robocza " << endl;
	cout << "    ";
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << i + 1;
	}
	cout << endl << "   " << y;

	for (int i = 1; i <= WielkoscPlanszy; i++)
		cout << x << x << x;
	cout << endl;
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << z;
		for (int j = 0; j <= WielkoscPlanszy - 1; j++)
		{
			cout.width(3);
			cout << PlanszaWew[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Clas::GenerowanieSciany()
{
	PlanszaWew[0][0] = 8;
	PlanszaWew[WielkoscPlanszy-1][WielkoscPlanszy - 1] = 9;

	PlanszaWyswietlana[0][0] = ' ';
	PlanszaWyswietlana[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = ' ';

	int kolumna, wiersz;
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> pole(0, WielkoscPlanszy - 1);

	bool dobrze{};
	while (dobrze == 0)
	{
		kolumna = pole(generator);
		wiersz = pole(generator);

		if ( (PlanszaWew[wiersz - 1][kolumna] == 8 || PlanszaWew[wiersz][kolumna - 1] == 8)  ||  (PlanszaWew[wiersz - 1][kolumna] == 0 || PlanszaWew[wiersz][kolumna - 1] == 0) )
		{
			if (PlanszaWew[wiersz][kolumna] == 0 || PlanszaWew[wiersz][kolumna] == 8 || PlanszaWew[wiersz][kolumna] == 9)
				dobrze = 0;
			else
			{
				dobrze = 1;
				PlanszaWew[wiersz][kolumna] = 0;
				PlanszaWyswietlana[wiersz][kolumna] = ' '; //docelowo do usuniêcia
			}
		}
	}
	
}

void Clas::GenerowaniePlanszy()
{
	int x = (2 * WielkoscPlanszy)-3;
	for (int i = 1; i <= x; i++)
	{
		GenerowanieSciany();
	}

	WyswietlTabliceZew();
	cout << endl;
	WyswietlTabliceWew();
}


//
//if ((licznik == 0 && (PlanszaWew[wiersz - 1][kolumna] == 8 || PlanszaWew[wiersz][kolumna - 1] == 8)) || (licznik != 0 && (PlanszaWew[wiersz - 1][kolumna] == 0 || PlanszaWew[wiersz][kolumna - 1] == 0)))
//{
//	if (PlanszaWew[wiersz][kolumna] == 2 || PlanszaWew[wiersz][kolumna] == 8 || PlanszaWew[wiersz][kolumna] == 9)
//		dobrze = 0;
//	else
//	{
//		dobrze = 1;
//		PlanszaWew[wiersz][kolumna] = 2;
//		PlanszaWyswietlana[wiersz][kolumna] = 0xFE; //docelowo do usuniêcia
//	}
//}
////licznik++;