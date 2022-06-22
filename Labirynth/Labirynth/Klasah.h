#pragma once
#include <iostream>
#include <random>
#include <windows.h>
#include <string>
#include <cmath> // do abs()
using namespace std;


char PlanszaWyswietlana[11][11]{}; //PlanszaWyswietlana bêdzie bazowo wype³niona "0xFE"
char PlanszaWyswietlana2[11][11]{};

char Gracz1_TwojaPlansza[11][11]{};
char Gracz2_TwojaPlansza[11][11]{};

char Gracz1_PlanszaWew[11][11]{};// 0- œciana, 1- przejœcie
char Gracz2_PlanszaWew[11][11]{};

int WielkoscPlanszy = 11;

char poz = 0xC4, pio = 0xB3;//kreska pozioma, pionowa
char lg = 0xDA, pg = 0xBF, ld = 0xC0, pd = 0xD9; // rogi dla planszy lg - lewy górny, pg - prawy górny itd.

string gdzie{}, gdzie_0 = "A1";
string gdzie1 = "A1", gdzie2 = "A1";
int x{}, y{};
//do "gdzie" bêdziemy podawaæ wspó³rzêdn¹,
//gdzie_0 zapisze poprzedni¹ pozycjê

int dobicia{}; //do trybu 1-osobowego

bool zakonczeniePodawaniaTryb2{};

enum Gracze {Gracz1 = 1,Gracz2};
Gracze KtóryGracz = Gracz1;

COORD c; //do zmieniania pozycji kursora
/*c.X = xj;
c.Y = yj;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);*/

char ³ = 0x88, Ÿ = 0xAB, ó = 0xA2, œ = 0x98, æ = 0x86, ¿ = 0xBE, ê = 0xA9, ¹ = 0xA5, ñ = 0xE4;; // polskie znaki

bool devmode = 0;

class Clas
{
public:
	void Menu();
	void Ustawienia();

	void Kolory();
	void Uzupe³nieniePlansz();
	void WyswietlTabliceZew();
	void WyswietlTabliceZew2();
	void GenerowaniePrzejœcia();
	bool NowaPozycja();
	bool CzyDobije();
	bool CzyDobije1();
	bool CzyDobije2();
	bool NowaPozycjaTryb2();

	void Gracz1_Wyœwietl_Swoj¹Planszê();
	void Gracz2_Wyœwietl_Swoj¹Planszê();

	void Gracz1_Wyœwietl_Swoj¹PlanszêWew();
	void Gracz2_Wyœwietl_Swoj¹PlanszêWew(int opcja);

	void Gra_1os();
	void Gra_2os();
};
//------------------------------------------
// intro
void Clas::Menu()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 3); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

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
			dobrze = 1;
			cout << endl << "Tw" << ó << "j wyb" << ó << "r: ";
			cin >> wyborMenu;
			if (wyborMenu.size() == 1)
			{
				if (wyborMenu[0] == '1')
				{
					system("CLS");
					Gra_2os();
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
	string wybor;
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

			
			if (wybor[0] == '1')
			{
				system("CLS");
				bool dobryWybor{};
				string devmodeWybor{};
				cout << "W" << ³ << ¹ << "czenie devmode powoduje pokazywanie si"<<ê<<" rozwi" << ¹ << "zanej planszy. " << endl;
				cout << endl << endl;
				do
				{
					dobryWybor = 1;
					
					cout << "Czy chcesz w" << ³ << ¹ << "czy" << æ << " devmode? (1 -tak, 0 -nie): ";
					cin >> devmodeWybor;

					if (devmodeWybor[0] == '1')
					{
						system("CLS");
						devmode = 1;
					}
					else if (devmodeWybor[0] == '0')
					{
						system("CLS");
						devmode = 0;
					}
					else
					{
						cout << endl << "Nieprawid" << ³ << "owa liczba, podaj ponownie. " << endl;
						dobryWybor = 0;
					}

				} while (dobryWybor == 0);
			}
			else if (wybor[0] == '2')
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
	info1.ColorTable[3] = RGB(0, 0, 0); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);


	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]
}

void Clas::Uzupe³nieniePlansz()
{
	for (int y = 0; y < WielkoscPlanszy; y++)
	{
		for (int x = 0; x < WielkoscPlanszy; x++)
		{
			PlanszaWyswietlana[y][x] = 0xFE;
			PlanszaWyswietlana2[y][x] = 0xFE;

			Gracz1_TwojaPlansza[y][x] = '?';
			Gracz2_TwojaPlansza[y][x] = '?';

			Gracz1_PlanszaWew[y][x] = 0xFE;
			Gracz2_PlanszaWew[y][x] = 0xFE;
		}
	}
	Gracz1_TwojaPlansza[0][0] = 'S'; // Oznaczenie startu
	Gracz1_PlanszaWew[0][0] = 'S';
	Gracz2_TwojaPlansza[0][0] = 'S';
	Gracz2_PlanszaWew[0][0] = 'S';
	Gracz1_TwojaPlansza[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M'; // Oznaczenie mety
	Gracz1_PlanszaWew[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M';
	Gracz2_TwojaPlansza[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M';
	Gracz2_PlanszaWew[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M';
}

void Clas::WyswietlTabliceZew()
{	
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	cout << "  Plansza odkryta" << endl;
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

void Clas::WyswietlTabliceZew2()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 2); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	int wierszKursora = 15;

	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "  Plansza odkryta" << endl;

	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   ";
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na górze tablicy wyœwietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int i = 0; i <= WielkoscPlanszy - 1; i++)
	{
		c.X = 43;
		c.Y = wierszKursora++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

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
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
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
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' '; // przesuwamy sie o 2 pola, by nie tworzyc placow 
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieWiersz--;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
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
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieKolumna++;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
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
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieWiersz++;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
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
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
							aktualnieKolumna--;
							PlanszaWyswietlana[aktualnieWiersz][aktualnieKolumna] = ' ';
							PlanszaWyswietlana2[aktualnieWiersz][aktualnieKolumna] = ' ';
						}
						else
							dobrze = 0;
						break;
					}
				}
			}
		}
	}
	PlanszaWyswietlana[0][0] = '*'; // bo na start zaczynamy z pozycji A1
	PlanszaWyswietlana[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M'; //oznaczenie mety

	PlanszaWyswietlana2[0][0] = '*'; // bo na start zaczynamy z pozycji A1
	PlanszaWyswietlana2[WielkoscPlanszy - 1][WielkoscPlanszy - 1] = 'M'; //oznaczenie mety
}

void Clas::Gracz1_Wyœwietl_Swoj¹Planszê()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 1); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	//------------------------------------------------------------------------------------

	cout << "  GRACZ 1:" << endl;
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

void Clas::Gracz2_Wyœwietl_Swoj¹Planszê()
{	
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 2); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	//------------------------------------------------------------------------------------
	int wierszKursora{};
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "  GRACZ 2:" << endl;
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   ";
	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na górze tablicy wyœwietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int y = 0; y <= WielkoscPlanszy - 1; y++)
	{
		c.X = 43;
		c.Y = wierszKursora++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

		cout.width(3);
		cout << y + 1 << pio;

		int x = 0;
		cout.width(2);
		cout << Gracz2_TwojaPlansza[y][x];

		for (int x = 1; x <= WielkoscPlanszy - 1; x++)   //œrodek
		{
			cout.width(3);
			cout << Gracz2_TwojaPlansza[y][x];
		}
		cout << ' ' << pio << endl;
	}
	//-----------------------------------------------------
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   " << ld;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //dolna ramka
		cout << poz << poz << poz;
	cout << pd << endl;

	
}

void Clas::Gracz1_Wyœwietl_Swoj¹PlanszêWew()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleTextAttribute(hConsole1, 1);
	//------------------------------------------------------------------------------------
	cout << "  GRACZ 1:" << endl;
	cout << "   ";

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na gorze tablicy wyswietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //gorna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int y = 0; y <= WielkoscPlanszy - 1; y++)
	{
		cout.width(3);
		cout << y + 1 << pio;

		int x = 0;
		cout.width(2);
		cout << Gracz1_PlanszaWew[y][x];

		for (int x = 1; x <= WielkoscPlanszy - 1; x++)   //srodek
		{
			cout.width(3);
			cout << Gracz1_PlanszaWew[y][x];
		}
		cout << ' ' << pio << endl;
	}
	//-----------------------------------------------------
	cout << "   " << ld;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //dolna ramka
		cout << poz << poz << poz;
	cout << pd << endl;
}

void Clas::Gracz2_Wyœwietl_Swoj¹PlanszêWew(int opcja)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleTextAttribute(hConsole1, 2);
	//------------------------------------------------------------------------------------
	int wierszKursora{};
	if (opcja == 1) wierszKursora = 16;
	if (opcja == 2) wierszKursora = 0;
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "  GRACZ 2:" << endl;
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	cout << "   ";

	for (int i = 0; i < WielkoscPlanszy; i++)
	{
		cout.width(3);
		cout << char(65 + i); //na gorze tablicy wyswietla A, B, C,...
	}
	cout << endl;

	//-----------------------------------------------------
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "   " << lg;
	for (int i = 1; i <= WielkoscPlanszy; i++)           //górna ramka
		cout << poz << poz << poz;
	cout << pg << endl;
	//-----------------------------------------------------
	for (int y = 0; y <= WielkoscPlanszy - 1; y++)
	{
		c.X = 43;
		c.Y = wierszKursora++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout.width(3);
		cout << y + 1 << pio;

		int x = 0;
		cout.width(2);
		cout << Gracz2_PlanszaWew[y][x];

		for (int x = 1; x <= WielkoscPlanszy - 1; x++)   //œrodek
		{
			cout.width(3);
			cout << Gracz2_PlanszaWew[y][x];
		}
		cout << ' ' << pio << endl;
	}
	//-----------------------------------------------------
	c.X = 43;
	c.Y = wierszKursora++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
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
	if (abs(gdzie[0] - gdzie_0[0]) > 1)
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

bool Clas::CzyDobije1()
{
	x = int(gdzie[0]) - 65;
	if (gdzie.size() == 2)
	{
		y = int(gdzie[1]) - 49;
		if (Gracz2_PlanszaWew[y][x] != ' ')
		{
			return true;
		}
	}
	else // gdzie.size() == 3
	{
		y = int(gdzie[2]) - 39;
		if (Gracz2_PlanszaWew[y][x] != ' ')
		{
			return true;
		}
	}
	return false;
}

bool Clas::CzyDobije2()
{
	x = int(gdzie[0]) - 65;
	if (gdzie.size() == 2)
	{
		y = int(gdzie[1]) - 49;
		if (Gracz1_PlanszaWew[y][x] != ' ')
		{
			return true;
		}
	}
	else // gdzie.size() == 3
	{
		y = int(gdzie[2]) - 39;
		if (Gracz1_PlanszaWew[y][x] != ' ')
		{
			return true;
		}
	}
	return false;
}

bool Clas::NowaPozycjaTryb2()
{
	cin >> gdzie;

	if (gdzie[0] == 'o' && gdzie[1] == 'k' && gdzie[2] == 'o' && gdzie[3] == 'n')
	{
		zakonczeniePodawaniaTryb2 = 1;
		return true;
	}
	else
	{
		if ((gdzie[0] == 'a' || gdzie[0] == 'A') && gdzie[1] == '1')
			return false;
		if ((gdzie[0] == 'k' || gdzie[0] == 'K') && gdzie[1] == '1' && gdzie[2] == '1')
			return false;

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
	}
	return true;
}

void Clas::Gra_1os()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 3); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	Uzupe³nieniePlansz();
	GenerowaniePrzejœcia();

	system("CLS");
	cout << "INSTRUKCJA: TRYB JEDNOOSOBOWY" << endl << endl;
	cout << "Program wygenerowa" << ³ << " plansz" << ê << ". Twoim zadaniem jest znalezienie przej" << œ << "cia z jednego rogu mapy do drugiego. " << endl << endl;
	system("pause");
	system("CLS");
	SetConsoleTextAttribute(hConsole1, 1);

	Gracz1_Wyœwietl_Swoj¹Planszê();
	cout << "   dobicia: ";

	if (devmode)
	{
		cout << endl;
		WyswietlTabliceZew();
	}
	gdzie_0 = "A1";
	do
	{
		do
		{
			c.X = 0;
			if (!devmode)
				c.Y = 18;
			else if (devmode)
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
			if (devmode)
			{
				c.X = 5 + 3 * x;
				c.Y = 19 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << PlanszaWyswietlana[y][x];
			}
			gdzie_0 = gdzie;
		}
		else if (PlanszaWyswietlana[y][x] == '*')
		{
			cout << "na tej pozycji ju" << ¿ << " by" << ³ << "e" << œ;
			Sleep(1000);
			cout << '\r' << "\x1b[2K";
		}
		else if (x == WielkoscPlanszy-1 && y == WielkoscPlanszy-1)
		{
			Gracz1_TwojaPlansza[y][x] = '*';
			c.X = 5 + 3 * x;
			c.Y = 3 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << Gracz1_TwojaPlansza[y][x];

			if (devmode)
			{
				PlanszaWyswietlana[y][x] = '*';
				c.X = 5 + 3 * x;
				c.Y = 19 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << PlanszaWyswietlana[y][x];
				c.X = 0;
				c.Y = 33;
			}
			else 
			{
				c.X = 0;
				c.Y = 20;
			}			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "KONIEC GRY!!!";
		}
		else
		{
			cout << "dobije do " << œ << "ciany" << " (" << PlanszaWyswietlana[y][x] << ")  ";
			Sleep(1000);
			cout << '\r' << "\x1b[2K";

			c.X = 5 + 3 * x;
			c.Y = 3 + y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			Gracz1_TwojaPlansza[y][x] = PlanszaWyswietlana[y][x];
			cout << Gracz1_TwojaPlansza[y][x];

			dobicia++;
			c.X = 12;
			c.Y = 15;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << dobicia;
		}
	} while (x != WielkoscPlanszy-1 || y != WielkoscPlanszy-1);	
}

void Clas::Gra_2os()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info1;
	info1.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole1, &info1);

	info1.ColorTable[0] = RGB(16, 11, 7); //ten kolor jest t³em
	info1.ColorTable[1] = RGB(105, 168, 226); //kolor gracza 1 - niebieski
	info1.ColorTable[2] = RGB(207, 115, 54); //kolor gracza 2 - pomarañczowy
	info1.ColorTable[3] = RGB(255, 255, 255); //kolor bia³y

	SetConsoleScreenBufferInfoEx(hConsole1, &info1);

	SetConsoleTextAttribute(hConsole1, 3); //(hConsole1, n) w funkcji oznacza ¿e bierzemy info1.ColorTable[n]

	Uzupe³nieniePlansz();

	system("CLS");
	cout << "INSTRUKCJA: TRYB DWUOSOBOWY" << endl << endl;
	cout << "Na pocz" << ¹ << "tku ka" << ¿ << "dy gracz tworzy plansze dla przeciwnika. Nast" << ê << "pnie rozpoczyna si" << ê << " rozgrywka. " << endl;
	cout << "Gre zaczyna GRACZ1 i gra on tak d" << ³ << "ugo, a" << ¿ << " trafi w " << œ << "ciane. Wtedy nast" << ê << "puje zmiana graczy. I tak w k" << ó << ³ << "ko, a" << ¿ << " kt" << ó << "ry" << œ << " dotrze do mety." << endl << endl;
	system("pause");



	// USTAWIANIE PLANSZ



	do
	{
		//USTAWIANIE GRACZ 1


		system("CLS");
		zakonczeniePodawaniaTryb2 = 0;

		SetConsoleTextAttribute(hConsole1, 1);
		Gracz1_Wyœwietl_Swoj¹PlanszêWew();
		cout << endl;
		if (devmode == 1) Gracz1_Wyœwietl_Swoj¹PlanszêWew();

		//----------------------------------------------------------------
		int wysokosc{};													  // Linia oddzielaj¹ca plansze
		if (devmode == 1)
			wysokosc = 32;
		if (devmode == 0)
			wysokosc = 16;
		for (int i{}; i <= wysokosc - 1; i++)
		{
			c.X = 41;
			c.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "|";
		}
		//----------------------------------------------------------------
		SetConsoleTextAttribute(hConsole1, 2);
		Gracz2_Wyœwietl_Swoj¹Planszê();
		if (devmode == 1)
		{
			Gracz2_Wyœwietl_Swoj¹PlanszêWew(1);

			SetConsoleTextAttribute(hConsole1, 1);
			c.X = 0;
			c.Y = 35;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "Gdy uznasz, " << ¿ << "e plansza jest gotowa wpisz: okon";
		}
		SetConsoleTextAttribute(hConsole1, 1);
		do
		{
			c.X = 0;
			if (devmode == 1)
				c.Y = 32;
			if (devmode == 0)
				c.Y = 16;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "\x1b[2K"; //usuwa ca³¹ liniê
			cout << "Gdzie chcesz usun" << ¹ << æ << " " << œ << "ciane: ";
		} while (!NowaPozycjaTryb2());

		x = int(gdzie[0]) - 65;
		if (gdzie.size() == 2)
		{
			y = int(gdzie[1]) - 49;
		}
		else // gdzie.size() == 3
		{
			y = int(gdzie[2]) - 39;
		}
		gdzie_0 = gdzie;
		Gracz1_PlanszaWew[y][x] = ' ';

	} while (zakonczeniePodawaniaTryb2 != 1);


	do
	{
		// USTAWIANIE GRACZ 2


		system("CLS");
		zakonczeniePodawaniaTryb2 = 0;

		SetConsoleTextAttribute(hConsole1, 1);
		Gracz1_Wyœwietl_Swoj¹Planszê();
		cout << endl;
		if (devmode == 1) Gracz1_Wyœwietl_Swoj¹PlanszêWew();

		//----------------------------------------------------------------
		int wysokosc{};													  // Linia oddzielaj¹ca plansze
		if (devmode == 1)
			wysokosc = 32;
		if (devmode == 0)
			wysokosc = 16;
		for (int i{}; i <= wysokosc - 1; i++)
		{
			c.X = 41;
			c.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "|";
		}
		//----------------------------------------------------------------
		SetConsoleTextAttribute(hConsole1, 2);
		Gracz2_Wyœwietl_Swoj¹PlanszêWew(2);
		if (devmode == 1)
		{
			Gracz2_Wyœwietl_Swoj¹PlanszêWew(1);
			c.X = 43;
			c.Y = 35;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "Gdy uznasz, " << ¿ << "e plansza jest gotowa wpisz: okon";
		}
		do
		{
			c.X = 43;
			if (devmode == 1)
				c.Y = 32;
			if (devmode == 0)
				c.Y = 16;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "\x1b[2K"; //usuwa ca³¹ liniê
			cout << "Gdzie chcesz usun" << ¹ << æ << " " << œ << "ciane: ";
		} while (!NowaPozycjaTryb2());

		x = int(gdzie[0]) - 65;
		if (gdzie.size() == 2)
		{
			y = int(gdzie[1]) - 49;
		}
		else // gdzie.size() == 3
		{
			y = int(gdzie[2]) - 39;
		}
		gdzie_0 = gdzie;
		Gracz2_PlanszaWew[y][x] = ' ';

	} while (zakonczeniePodawaniaTryb2 != 1);



	// GRANIE


	
	SetConsoleTextAttribute(hConsole1, 1);
	system("CLS");
	Gracz1_Wyœwietl_Swoj¹Planszê();
	cout << endl;
	if (devmode == 1) Gracz1_Wyœwietl_Swoj¹PlanszêWew();

	//----------------------------------------------------------------
	int wysokosc{};													  // Linia oddzielaj¹ca plansze
	if (devmode == 1)
		wysokosc = 32;
	if (devmode == 0)
		wysokosc = 16;
	for (int i{}; i <= wysokosc - 1; i++)
	{
		c.X = 41;
		c.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout << "|";
	}
	//----------------------------------------------------------------
	SetConsoleTextAttribute(hConsole1, 2);
	Gracz2_Wyœwietl_Swoj¹Planszê();
	if (devmode == 1) Gracz2_Wyœwietl_Swoj¹PlanszêWew(1);

	SetConsoleTextAttribute(hConsole1, 1);
	gdzie1 = "A1";
	gdzie2 = "A1";
	gdzie_0 = "A1";
	KtóryGracz = Gracz1;
	do
	{
		if (KtóryGracz == Gracz1)
		{
			SetConsoleTextAttribute(hConsole1, 1);
			do
			{
				c.X = 0;
				if (!devmode)
					c.Y = 18;
				else if (devmode)
					c.Y = 31;

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "\x1b[2K"; //usuwa ca³¹ liniê
				cout << "gdzie chcesz si" << ê << " poruszy" << æ << ": ";

			} while (!NowaPozycja());


			if (!CzyDobije1())
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
				/*if (devmode)
				{
					c.X = 5 + 3 * x;
					c.Y = 18 + y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					cout << PlanszaWyswietlana[y][x];
				}*/
				gdzie_0 = gdzie;
			}
			else if (PlanszaWyswietlana[y][x] == '*')
			{
				cout << "na tej pozycji ju" << ¿ << " by" << ³ << "e" << œ;
				Sleep(1000);
				cout << '\r' << "\x1b[2K";
			}
			else if (x == WielkoscPlanszy - 1 && y == WielkoscPlanszy - 1)
			{
				Gracz1_TwojaPlansza[y][x] = '*';
				c.X = 5 + 3 * x;
				c.Y = 3 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << Gracz1_TwojaPlansza[y][x];

				if (devmode)
				{
					PlanszaWyswietlana[y][x] = '*';
					c.X = 5 + 3 * x;
					c.Y = 19 + y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					cout << PlanszaWyswietlana[y][x];
					c.X = 0;
					c.Y = 33;
				}
				else
				{
					c.X = 0;
					c.Y = 20;
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "KONIEC GRY!!!";
			}
			else
			{
				cout << "dobije do " << œ << "ciany" << " (" << PlanszaWyswietlana[y][x] << ")  ";
				Sleep(1000);
				cout << '\r' << "\x1b[2K";

				c.X = 5 + 3 * x;
				c.Y = 3 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				Gracz1_TwojaPlansza[y][x] = PlanszaWyswietlana[y][x];
				cout << Gracz1_TwojaPlansza[y][x];
				KtóryGracz = Gracz2;
				gdzie1 = gdzie_0;
				gdzie_0 = gdzie2;
			}
		}
		else if (KtóryGracz == Gracz2)
		{
			SetConsoleTextAttribute(hConsole1, 2);
			do
			{
				c.X = 42;
				if (!devmode)
					c.Y = 18;
				else if (devmode)
					c.Y = 31;

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "\x1b[2K"; //usuwa ca³¹ liniê
				cout << "gdzie chcesz si" << ê << " poruszy" << æ << ": ";

			} while (!NowaPozycja());

			if (!CzyDobije2())
			{
				c.X = 42;
				if (!devmode)
					c.Y = 20;
				else if (devmode)
					c.Y = 33;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "nie dobije";
				Sleep(400);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "\x1b[2K";

				Gracz2_TwojaPlansza[y][x] = '*';
				c.X = 48 + 3 * x;
				c.Y = 3 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << Gracz2_TwojaPlansza[y][x];

				PlanszaWyswietlana2[y][x] = '*';
				/*if (devmode)
				{
					c.X = 48 + 3 * x;
					c.Y = 18 + y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					cout << PlanszaWyswietlana2[y][x];
				}*/
				gdzie_0 = gdzie;
			}
			else if (PlanszaWyswietlana2[y][x] == '*')
			{
				c.X = 42;
				if (!devmode)
					c.Y = 20;
				else if (devmode)
					c.Y = 33;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "na tej pozycji ju" << ¿ << " by" << ³ << "e" << œ;
				Sleep(1000);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "\x1b[2K";
			}
			else if (x == WielkoscPlanszy - 1 && y == WielkoscPlanszy - 1)
			{
				Gracz2_TwojaPlansza[y][x] = '*';
				c.X = 48 + 3 * x;
				c.Y = 3 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << Gracz2_TwojaPlansza[y][x];

				if (devmode)
				{
					PlanszaWyswietlana2[y][x] = '*';
					c.X = 48 + 3 * x;
					c.Y = 19 + y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					cout << PlanszaWyswietlana2[y][x];
					c.X = 42;
					c.Y = 33;
				}
				else
				{
					c.X = 42;
					c.Y = 20;
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "KONIEC GRY!!!";
			}
			else
			{
				c.X = 42;
				if (!devmode)
					c.Y = 20;
				else if (devmode)
					c.Y = 33;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "dobije do " << œ << "ciany" << " (" << PlanszaWyswietlana2[y][x] << ")  ";
				Sleep(1000);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "\x1b[2K";

				c.X = 48 + 3 * x;
				c.Y = 3 + y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				Gracz2_TwojaPlansza[y][x] = PlanszaWyswietlana2[y][x];
				cout << Gracz2_TwojaPlansza[y][x];
				KtóryGracz = Gracz1;
				gdzie2 = gdzie_0;
				gdzie_0 = gdzie1;
			}
		}

	} while (x != WielkoscPlanszy - 1 || y != WielkoscPlanszy - 1);
}