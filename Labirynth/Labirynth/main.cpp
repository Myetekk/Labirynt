#include <iostream>
#include "Class.h"
using namespace std;

int main()
{
	Clas obj;

	obj.GenerowaniePlanszy();

	cout << endl;
	system("pause");
}

/*

PlanszaZew:
	niewiadoma 0xCF
	przej�cie " "
	�ciana 0xFE

PlanszaWew:
	pocz�tek: 8
	koniec: 9
	�ciana: 2
	pusto: 0
*/