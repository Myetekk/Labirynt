#pragma once
#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

int PlanszaWew[10][10]{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
char PlanszaWyswietlana[10][10]{ 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF };

int WielkoscPlanszy = 10; //by³o 6 ale sprawdzam se dla 10

class Clas
{
public:
	void WyswietlTabliceZew();
	void WyswietlTabliceWew();
	void GenerowanieSciany();
	void GenerowaniePlanszy();
};

void Clas::WyswietlTabliceZew()
{//kreska pozioma,     krzy¿yk,     pionowa
	char poz = 0xC4/*, y = 0xC5*/, pio = 0xB3;
	char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy górny, pg - prawy górny itd.

	//kolory
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7);//ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1
	info1.ColorTable[2] = RGB(207, 115, 54);//kolor gracza 2

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);


	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]
	cout << "  Tablica docelowa" << endl;
	cout << "   "; //-1 spacja

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); // teraz na górze tabicy wyœwietla A, B, C,...
	}
	cout << endl;
	
//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
//-----------------------------------------------------
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << pio;

		int j = 0; //zrobi³em trochê wê¿sze na pocz¹tku bo estetycznie
		cout.width(2);
		cout << PlanszaWyswietlana[i][j];

		for (int j = 1; j <= WielkoscPlanszy - 1; j++)   //œrodek
		{
			cout.width(3);
			cout << PlanszaWyswietlana[i][j];
		}
		cout << ' ' << pio << endl;
	}
//-----------------------------------------------------
	cout << "   " << ld;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //dolna ramka
		cout << poz << poz << poz;
	cout << pd << endl;
//-----------------------------------------------------
}

void Clas::WyswietlTabliceWew()
{
	char poz = 0xC4,/* y = 0xC5,*/ pio = 0xB3;
	char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy górny, pg - prawy górny itd.

	cout << "  Tablica robocza" << endl;
	cout << "   "; // -1 spacja

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); // teraz na górze wyœwietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << pio;

		int j = 0; //zrobi³em trochê wê¿sze na pocz¹tku bo estetycznie
		cout.width(2);
		cout << PlanszaWew[i][j];
		for (int j = 1; j <= WielkoscPlanszy - 1; j++)   //œrodek
		{
			cout.width(3);
			cout << PlanszaWew[i][j];
		}
		cout << ' ' << pio << endl;
	}
	//-----------------------------------------------------
	cout << "   " << ld;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //dolna ramka
		cout << poz << poz << poz;
	cout << pd << endl;
	//-----------------------------------------------------
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