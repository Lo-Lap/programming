
#include <iostream>
#include <stack>
#include "calcul.h"
using namespace std;

int main()
{
	calcul cal;
	char c;
	while (c=cin.peek())
	{
		if (c == '#') break;//��������� ���� ������
		cal.readthread();
		cal.maths();
		cin.ignore();
	}
	
	
}
