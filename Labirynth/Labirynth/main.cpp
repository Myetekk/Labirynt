#include "Class.h"

int main()
{
	//setlocale(LC_ALL, "polish"); // do polskich znak�w

	Clas gra;

	gra.Gra_1os();
//	gra.GenerowaniePlanszy();

	cout << endl;
	system("pause");
}

/*

PlanszaZew:
	niewiadoma ?
	przej�cie " "
	�ciana 0xFE 

PlanszaWew:
	pocz�tek: 8 - miejsce startu
	koniec: 9 - meta
	�ciana: 2
	pusto: 1
*/