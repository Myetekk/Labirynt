#pragma once
#include <iostream>
using namespace std;

int Plansza[10][10]{};
int PlanszaWyswietlana[10][10]{};


class Clas
{
public:
	int tab[3][3];
	void WyswietlTablice();
};

void Clas::WyswietlTablice()
{
	char x = 0xC4, y = 0xC5, z = 0xB3;

	cout << "    ";
	for (int i = 0; i < 10; i++)
	{
		cout.width(3);
		cout << i + 1;
	}
	cout << endl << "   " << y;

	for (int i = 1; i <= 10; i++)
		cout << x << x << x;
	cout << endl;
	for (int i = 0; i <= 10 - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << z;
		for (int j = 0; j <= 10 - 1; j++)
		{
			cout.width(3);
			cout << PlanszaWyswietlana[i][j];
		}
		cout << endl;
	}
	cout << endl;
}