#pragma once
#include <iostream>
#include <random>
#include <windows.h>
#include <string>
#include <cmath> // do abs()
using namespace std;


int PlanszaWew[11][11]{}; // PlanszaWew bêdzie bazowo wype³niona "2"
char PlanszaWyswietlana[11][11]{}; //PlanszaWyswietlana bêdzie bazowo wype³niona "0xFE"

char Gracz1_TwojaPlansza[11][11]{};

int WielkoscPlanszy = 11;

char poz = 0xC4, pio = 0xB3;//kreska pozioma, pionowa
char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy górny, pg - prawy górny itd.

string gdzie{}, gdzie_0 = "A1";
int x{}, y{};
//do "gdzie" bêdziemy podawaæ wspó³rzêdn¹,
//gdzie_0 zapisze poprzedni¹ pozycjê

int dobicia{}; //do trybu 1-osobowego


COORD c; //do zmieniania pozycji kursora
/*c.X = xj;
c.Y = yj;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);*/

char ³ = 0x88, Ÿ = 0xAB, ó = 0xA2, œ = 0x98, æ = 0x86, ¿ = 0xBE, ê = 0xA9, ¹ = 0xA5; // polskie znaki

bool devmode = 0;

class Clas
{
public:
	void Menu();
	void Ustawienia();

	void Kolory();
	void Uzupe³nieniePlansz();
	void WyswietlTabliceZew();
	void WyswietlTabliceWew();
	void GenerowaniePrzejœcia();
	void GenerowaniePlanszy(); // tryb 2os
	bool NowaPozycja();
	bool CzyDobije();

	void Gracz1_Wyœwietl_Swoj¹Planszê();
	void Gra_1os();
};
//------------------------------------------
// intro
void Clas::Menu()
{
	bool koniecMenu = 0;
	do
	{
		string wyborMenu;
		bool dobrze = 1;
		system("CLS");
		cout << "LABIRYNT " << endl << endl;
		cout << " 1. Gra dla dw" << ó << "ch os" << ó << "b " << endl << endl;
		cout << "2.  Gra dla jednej osoby " << endl << endl;
		cout << " 3. Ustawienia " << endl << endl;
		cout << "4.  Wyjd" << Ÿ << endl << endl;
		cout << endl;

		do
		{
			cout << endl << "Tw" << ó << "j wyb" << ó << "r: ";
			cin >> wyborMenu;
			if (wyborMenu.size() == 1)
			{
				if (wyborMenu[0] == '1')
				{
					system("CLS");

					system("pause");
				}
				else if (wyborMenu[0] == '2')
				{
					system("CLS");
					Gra_1os();
					system("pause");
				}
				else if (wyborMenu[0] == '3')
				{
					system("CLS");
					Ustawienia();
					system("pause");
				}
				else if (wyborMenu[0] == '4')
				{
					system("CLS");
					koniecMenu = 1;
				}
			}			
			else
			{
				cout << endl << "Nieprawid" << ³ << "owa liczba, podaj ponownie. ";
				dobrze = 0;
			}
		} while (dobrze == 0);
	} while (koniecMenu == 0);
}

void Clas::Ustawienia()
{
	int wybor;
	bool dobrze = 1, dobrzeUstawienia = 0;
	do
	{
		cout << "USTAWIENIA" << endl << endl;

		cout << " 1. devmode (";   if (devmode == 0)cout << "wy" << ³ << ¹ << "czone) ";   if (devmode == 1)cout << "w" << ³ << ¹ << "czone) ";   cout << endl << endl;
		cout << "2.  Powr" << ó << "t do menu " << endl << endl << endl;
		do
		{
			dobrzeUstawienia = 0;
			dobrze = 1;
			cout << endl << "Tw" << ó << "j wyb" << ó << "r: ";
			cin >> wybor;

			
			if (wybor == 1)
			{
				system("CLS");
				bool dobryWybor{};
				cout << "W" << ³ << ¹ << "czenie devmode powoduje pokazywanie si"<<ê<<" rozwi" << ¹ << "zanej planszy. " << endl;
				cout << endl << endl;
				do
				{
					dobryWybor = 1;
					
					cout << "Czy chcesz w" << ³ << ¹ << "czy" << æ << " devmode? (1 -tak, 0 -nie): ";
					cin >> devmode;

					if (devmode == 0 || devmode == 1)
					{
						system("CLS");
					}
					else
					{
						cout << endl << "Nieprawid" << ³ << "owa liczba, podaj ponownie. " << endl;
						dobryWybor = 0;
					}

				} while (dobryWybor == 0);
			}
			else if (wybor == 2)
			{
				system("CLS");
				dobrzeUstawienia = 1;
			}
			else
			{
				cout << endl << "Nieprawid" << ³ << "owa liczba, podaj ponownie. ";
				dobrze = 0;
			}
		} while (dobrze == 0);
	} while (dobrzeUstawienia == 0);
}
//------------------------------------------

void Clas::Kolory()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);


	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]
}

void Clas::Uzupe³nieniePlansz()
{
	for (int y = 0; y < WielkoscPlanszy; y++)
	{
		for (int x = 0; x < WielkoscPlanszy; x++)
		{
			//PlanszaWew[i][j] = 2;
			PlanszaWyswietlana[y][x] = 0xFE;
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

void Clas::Gracz1_Wyœwietl_Swoj¹Planszê()
{
	for (int y = 0; y < WielkoscPlanszy; y++)
	{
		for (int x = 0; x < WielkoscPlanszy; x++)
		{
			Gracz1_TwojaPlansza[y][x] = '?';
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
		cout << char(65 + i); //na górze tablicy wyœwietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int y = 0; y <= WielkoscPlanszy - 1; y++)
	{
		cout.width(3);
		cout << y + 1 << pio;

		int x = 0;
		cout.width(2);
		cout << Gracz1_TwojaPlansza[y][x];

		for (int x = 1; x <= WielkoscPlanszy - 1; x++)   //œrodek
		{
			cout.width(3);
			cout << Gracz1_TwojaPlansza[y][x];
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
	else
		if (gdzie[1] == '0')
			return false;

//------------------------------------------------------
	if (abs(gdzie[0] - gdzie_0[0] > 1))
		return false;
	else if(abs(gdzie[0] - gdzie_0[0]) == 1)
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

bool Clas::CzyDobije()
{
	x = int(gdzie[0]) - 65;
	if (gdzie.size() == 2)
	{
		y = int(gdzie[1]) - 49;
		if (PlanszaWyswietlana[y][x] != ' ')
		{
			cout << "(" << PlanszaWyswietlana[y][x] << ")  ";
			return true;
		}
	}
	else // gdzie.size() == 3
	{
		y = int(gdzie[2]) - 39;
		if (PlanszaWyswietlana[y][x] != ' ')
		{
			return true;
		}
	}		
	return false;
}

void Clas::Gra_1os()
{
	Kolory();
	Uzupe³nieniePlansz();
	GenerowaniePrzejœcia();

	Gracz1_Wyœwietl_Swoj¹Planszê();
	cout << endl;

	if (devmode == 1)
		WyswietlTabliceZew();
	
	do
	{
		do
		{
			c.X = 0;
			c.Y = 31;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "\x1b[2K"; //usuwa ca³¹ liniê
			cout << "gdzie chcesz si"<< ê <<" poruszy" << æ << ": ";

		} while (!NowaPozycja());
		//cout << endl << "sensowna pozycja" << endl;

		if (!CzyDobije())
		{
			cout << "nie dobije";
			Sleep(400);
			cout << '\r' << "\x1b[2K";

			Gracz1_TwojaPlansza[y][x] = '*';
			c.X = 5 + 3 * x;
			c.Y = 3 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << Gracz1_TwojaPlansza[y][x];

			PlanszaWyswietlana[y][x] = '*';
			c.X = 5 + 3 * x;
			c.Y = 19 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << PlanszaWyswietlana[y][x];

			gdzie_0 = gdzie;
		}
		else if (x == WielkoscPlanszy-1 && y == WielkoscPlanszy-1)
		{
			Gracz1_TwojaPlansza[x][y] = '*';
			c.X = 5 + 3 * x;
			c.Y = 3 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << Gracz1_TwojaPlansza[x][y];

			PlanszaWyswietlana[x][y] = '*';
			c.X = 5 + 3 * x;
			c.Y = 19 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << PlanszaWyswietlana[x][y];

			c.X = 0;
			c.Y = 33;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "KONIEC GRY!!!";
		}
		else
		{
			cout << "dobije do " << œ << "ciany";			
			Sleep(1000);
			cout << '\r' << "\x1b[2K";

			c.X = 5 + 3 * x;
			c.Y = 3 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			Gracz1_TwojaPlansza[y][x] = 0xFE;
			cout << Gracz1_TwojaPlansza[y][x];

			dobicia++;
		}
	} while (x != WielkoscPlanszy-1 || y != WielkoscPlanszy-1);
	

	c.X = 0;
	c.Y = 34;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Clas::GenerowaniePlanszy()
{
	/*Kolory();
	Uzupe³nieniePlansz();

	GenerowaniePrzejœcia();

	Gracz1_Wyœwietl_Swoj¹Planszê();
	cout << endl;

	WyswietlTabliceZew();*/

	//WyswietlTabliceWew();
}
