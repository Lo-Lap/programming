// Calculator_main_v.f.cpp : Defines the entry point for the application.
//

#include "Calculator_main_v.f.h"
#include <stack>
#include "calcul.h"

void main()
{
	std::cout << "This is a calculator" << std::endl;
	std::cout << "Standart operations: +, -, *, /, ^, ()" << std::endl;
	std::cout << "Non-standart mathematical operations: cos lg sin tg ctg ln sqrt cubsqrt abs round" << std::endl;
	std::cout << "cubsqrt - counts the cubic root" << std::endl;
	std::cout << "round - rounds to the largest integer, but not more than this number" << std::endl;
	std::cout << "To complete the work enter #" << std::endl << std::endl;

	calcul cal;
	if (cal.validation())
	{
		std::cout << "Enter the expression: ";
		char c;
		while (c = std::cin.peek())
		{
			if (c == '#') break;//interrupting the recording cycle
			cal.readthread();
			cal.maths();
			std::cin.ignore();//extracting a scanned character for a common expression from a stream
			std::cout << std::endl << "Enter the expression: ";
		}
	}


}
