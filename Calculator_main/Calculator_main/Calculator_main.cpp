// Calculator_main.cpp : Defines the entry point for the application.
//

#include "Calculator_main.h"

#include <stack>
#include "calcul.h"
using namespace std;

int main()
{
	cout << "This is a calculator" << endl;
	cout << "Standart operations: +, -, *, /, ^, ()" << endl;
	cout << "Non-standart mathematical operations: cos, ln" << endl;
	cout << "To complete the work enter #" << endl << endl;
	cout << "Enter the expression: ";

	calcul cal;
	char c;
	while (c = cin.peek())
	{
		if (c == '#') break;//прерываем цикл записи
		cal.readthread();
		cal.maths();
		cout << endl << "Enter the expression: ";
		cin.ignore();
	}


}
