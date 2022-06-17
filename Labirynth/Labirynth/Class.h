#pragma once
#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

//int PlanszaWew[11][11]{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
//char PlanszaWyswietlana[11][11]{ 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF,0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF };

int PlanszaWew[11][11]{}; // PlanszaWew bêdzie bazowo wype³niona "2"
char PlanszaWyswietlana[11][11]{}; //PlanszaWyswietlana bêdzie bazowo wype³niona "0xFE"

int WielkoscPlanszy = 11;

class Clas
{
public:
	void Uzupe³nieniePlansz();
	void WyswietlTabliceZew();
	void WyswietlTabliceWew();
	void GenerowaniePrzejœcia();
	void GenerowaniePlanszy();
};
void Clas::Uzupe³nieniePlansz()
{
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		for (int j = 0; j < WielkoscPlanszy; j++)
		{
			PlanszaWew[i][j] = 2;
			PlanszaWyswietlana[i][j] = 0xFE;
		}
	}
}

void Clas::WyswietlTabliceZew()
{//kreska pozioma,    pionowa
	char poz = 0xC4, pio = 0xB3;
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
	cout << "   "; 

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na górze tablicy wyœwietla A, B, C,...
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

		int j = 0;
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
	char poz = 0xC4, pio = 0xB3;
	char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy górny, pg - prawy górny itd.

	cout << "  Tablica robocza" << endl;
	cout << "   ";

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na górze wyœwietla A, B, C,...
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

		int j = 0;
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

void Clas::GenerowaniePrzejœcia()
{
	int aktualnieWiersz = 0, aktualnieKolumna = 0; // zaczynamy w punkcie startowym - w kodzie (0,0), na planszy (1,1)
	
	PlanszaWyswietlana[0][0] = ' '; //oznaczenie poczatku na planszy wyswietlanej
									//koniec nie jest oznaczony ' ' bo algorytm i tak zrobi to "za nas"

	//-------------------------------------------------------------------------
	int kierunek;
	mt19937 generator(time(nullptr));										   // generator wybierania kierunku
	uniform_int_distribution<int> kier(1, 4);// 1-gora, 2-prawo, 3-dol, 4-lewo
	//-------------------------------------------------------------------------


	bool doszedlDoKonca{};
	while (!doszedlDoKonca)
	{
		if (aktualnieWiersz == 10 && aktualnieKolumna == 10)
		{
			doszedlDoKonca = 1;
		}
		else
		{
			bool dobrze{};
			while (!dobrze)
			{
				dobrze = 1;
				kierunek = kier(generator);

				switch (kierunek)
				{
					case 1: //gora
					{
						if (aktualnieWiersz > 1) //zeby nie wychodzil poza plansze
						{//--------------------------------------------------------------
							aktualnieWiersz--;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;			  
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' '; // przesuwamy sie o 2 pola, by nie tworzyc placow 
							aktualnieWiersz--;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
						}//--------------------------------------------------------------
						else
							dobrze = 0;
						break;
					}
					case 2: //prawo
					{
						if (aktualnieKolumna < WielkoscPlanszy - 2)
						{
							aktualnieKolumna++;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieKolumna++;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
						}
						else
							dobrze = 0;
						break;
					}
					case 3: //dol
					{
						if (aktualnieWiersz < WielkoscPlanszy - 2)
						{
							aktualnieWiersz++;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieWiersz++;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
						}
						else
							dobrze = 0;
						break;
					}
					case 4: //lewo
					{
						if (aktualnieKolumna > 1)
						{
							aktualnieKolumna--;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieKolumna--;
							PlanszaWew[aktualnieWiersz][aktualnieKolumna] = 1;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
						}
						else
							dobrze = 0;
						break;
					}
				}
			}
		}
	}
	PlanszaWew[0][0] = 8; // oznaczenie poczatku na planszy roboczej
	PlanszaWew[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 9; // oznaczenie konca na planszy roboczej	
}

void Clas::GenerowaniePlanszy()
{
	Uzupe³nieniePlansz();

	GenerowaniePrzejœcia();

	WyswietlTabliceZew();
	cout << endl;
	WyswietlTabliceWew();
}
