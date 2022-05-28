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
	przejœcie " "
	œciana 0xFE

PlanszaWew:
	pocz¹tek: 8
	koniec: 9
	œciana: 2
	pusto: 0
*/