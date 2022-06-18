#include "Class.h"

int main()
{
	//setlocale(LC_ALL, "polish"); // do polskich znaków

	Clas gra;

	gra.Gra_1os();
//	gra.GenerowaniePlanszy();

	cout << endl;
	system("pause");
}

/*

PlanszaZew:
	niewiadoma ?
	przejœcie " "
	œciana 0xFE 

PlanszaWew:
	pocz¹tek: 8 - miejsce startu
	koniec: 9 - meta
	œciana: 2
	pusto: 1
*/