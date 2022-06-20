#pragma once
#include <iostream>
#include <random>
#include <windows.h>
#include <string>
#include <cmath> // do abs()
//#include <locale.h> //by wy�wietli� polskie znaki
using namespace std;


int PlanszaWew[11][11]{}; // PlanszaWew b�dzie bazowo wype�niona "2"
char PlanszaWyswietlana[11][11]{}; //PlanszaWyswietlana b�dzie bazowo wype�niona "0xFE"

char Gracz1_TwojaPlansza[11][11]{};

int WielkoscPlanszy = 11;

char poz = 0xC4, pio = 0xB3;//kreska pozioma, pionowa
char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy g�rny, pg - prawy g�rny itd.

string gdzie{}, gdzie_0 = "A1";
//do "gdzie" b�dziemy podawa� wsp�rz�dn�,
//gdzie_0 zapisze poprzedni� pozycj�


COORD c; //do zmieniania pozycji kursora
/*c.X = xj;
c.Y = yj;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);*/

class Clas
{
public:
	void Kolory();
	void Uzupe�nieniePlansz();
	void WyswietlTabliceZew();
	void WyswietlTabliceWew();
	void GenerowaniePrzej�cia();
	void GenerowaniePlanszy();
	bool NowaPozycja();

	void Gracz1_Wy�wietl_Swoj�Plansz�();
	void Gra_1os();
};

void Clas::Kolory()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t�em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomara�czowy

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);


	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza �e bierzemy info1.ColorTable[n]
}

void Clas::Uzupe�nieniePlansz()
{
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		for (int j = 0; j < WielkoscPlanszy; j++)
		{
			//PlanszaWew[i][j] = 2;
			PlanszaWyswietlana[i][j] = 0xFE;
		}
	}
}

void Clas::WyswietlTabliceZew()
{	
	cout << "  Tablica docelowa" << endl;
	cout << "   "; 

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na g�rze tablicy wy�wietla A, B, C,...
	}
	cout << endl;
	
//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //g�rna ramka
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

		for (int j = 1; j <= WielkoscPlanszy - 1; j++)   //�rodek
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
	cout << "  Tablica robocza" << endl;
	cout << "   ";

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na g�rze wy�wietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //g�rna ramka
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
		for (int j = 1; j <= WielkoscPlanszy - 1; j++)   //�rodek
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

void Clas::GenerowaniePrzej�cia()
{
	int aktualnieWiersz = 0, aktualnieKolumna = 0; // zaczynamy w punkcie startowym - w kodzie (0,0), na planszy A1
	
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
	PlanszaWyswietlana[0][0] = '*'; // bo na start zaczynamy z pozycji A1
	PlanszaWyswietlana[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M'; //oznaczenie mety	
}

void Clas::Gracz1_Wy�wietl_Swoj�Plansz�()
{
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		for (int j = 0; j < WielkoscPlanszy; j++)
		{
			Gracz1_TwojaPlansza[i][j] = '?';
		}
	}
	Gracz1_TwojaPlansza[0][0] = '*'; // bo na start zaczynamy z pozycji A1
	Gracz1_TwojaPlansza[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M'; //oznaczenie mety

	//------------------------------------------------------------------------------------

	cout << "  GRACZ 1 twoja plansza" << endl;
	cout << "   ";

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na g�rze tablicy wy�wietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //g�rna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		cout.width(3);
		cout << i + 1 << pio;

		int j = 0;
		cout.width(2);
		cout << Gracz1_TwojaPlansza[i][j];

		for (int j = 1; j <= WielkoscPlanszy - 1; j++)   //�rodek
		{
			cout.width(3);
			cout << Gracz1_TwojaPlansza[i][j];
		}
		cout << ' ' << pio << endl;
	}
	//-----------------------------------------------------
	cout << "   " << ld;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //dolna ramka
		cout << poz << poz << poz;
	cout << pd << endl;	
}

bool Clas::NowaPozycja()
{
	bool poruszenie_OX = false, poruszenie_OY = false;
	cin >> gdzie;

	if (gdzie.size() < 2 || gdzie.size() > 3) 
		return false;

	if ((gdzie[0] < 'A' || gdzie[0] > 'K') && (gdzie[0] < 'a' || gdzie[0] > 'k'))
		return false;
//-----------------------------------------------------	
	if ((gdzie[0] >= 'a' || gdzie[0] <= 'k'))
		gdzie[0] -= 32;	

	if (gdzie.size() == 3)
	{
		if (gdzie[1] == '1')
		{
			if (gdzie[2] < '0' || gdzie[2] > '1')
				return false;
			else if (gdzie[1] < '1' || gdzie[1] > '9')
				return false;
		}
		else
			return false;
	}	

//------------------------------------------------------
	if (abs(gdzie[0] - gdzie_0[0] > 1))
		return false;
	else if(abs(gdzie[0] - gdzie_0[0] == 1))
		poruszenie_OX = true;

//------------------------------------------------------
	if (gdzie.size() == 2 && gdzie_0.size() == 2)
	{
		if (abs(gdzie[1] - gdzie_0[1]) > 1)
			return false;
		else if (abs(gdzie[1] - gdzie_0[1]) == 1)
			poruszenie_OY = true;

		if (gdzie[0] == gdzie_0[0])
			if (gdzie[1] == gdzie_0[1])
				return false;
	}
	else if (gdzie.size() == 3 && gdzie_0.size() == 3)
	{
		if (abs(gdzie[2] - gdzie_0[2]) > 1)
			return false;
		else if (abs(gdzie[2] - gdzie_0[2]) == 1)
			poruszenie_OY = true;

		if (gdzie[0] == gdzie_0[0])
			if (gdzie[1] == gdzie_0[1])
				if (gdzie[2] == gdzie_0[2])
					return false;
	}
	else if (gdzie.size() == 2 && gdzie_0.size() == 3)
	{
		if (gdzie_0[2] == '0')
		{
			if (gdzie[1] != '9')
				return false;
		}
		else if (gdzie_0[2] == '1')
			return false;
		else
			poruszenie_OY = true;
	}
	else if (gdzie.size() == 3 && gdzie_0.size() == 2)
	{
		if (gdzie_0[1] != '9')
			return false;
		else if (gdzie[2] == '1')
			return false;
		else
			poruszenie_OY = true;
	}
//--------------------------------------------------------
	if (poruszenie_OX == true && poruszenie_OY == true)
		return false;
	return true;
}

void Clas::Gra_1os()
{
	Kolory();
	Uzupe�nieniePlansz();
	GenerowaniePrzej�cia();

	Gracz1_Wy�wietl_Swoj�Plansz�();
	cout << endl;

	WyswietlTabliceZew();
	bool tf = false;
	cout << "gdzie chcesz sie poruszyc: ";
	do
	{
		tf = NowaPozycja();
	} while (tf == false);

	cout << endl << "OK";

}

void Clas::GenerowaniePlanszy()
{
	Kolory();
	Uzupe�nieniePlansz();

	GenerowaniePrzej�cia();

	Gracz1_Wy�wietl_Swoj�Plansz�();
	cout << endl;

	WyswietlTabliceZew();

	//WyswietlTabliceWew();
}
