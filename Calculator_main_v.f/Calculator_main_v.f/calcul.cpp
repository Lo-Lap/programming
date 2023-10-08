#include "calcul.h"

calcul::calcul()
{
	oper_priority = {
		{"+",1},
		{"-",1},
		{"*",2},
		{"/",2},
		{"^",3}
	};
	function.insert(
		{ "+",
		[&](double a,double b) {double c = a + b; number.push(c); }//put the result into the stack of numbers
		}
	);
	function.insert(
		{ "-",
		[&](double a,double b)
		{double c = b - a;//change order because the stack order is different from the initial order in the console
		number.push(c);
		}//put the result into the stack of numbers
		}
	);
	function.insert(
		{ "*",
		[&](double a,double b) {double c = a * b; number.push(c); }//put the result into the stack of numbers
		}
	);
	function.insert(
		{ "/",
		[&](double a,double b) {
			if (a == 0)
		{
		std::cout << "Error. You can't divide by zero" << std::endl;
		//In order not to continue processing operations, we clear stacks of numbers and operations
		deleteStacksEr();
		return;
		}
		double c = b / a;//change order because the stack order is different from the initial order in the console
		number.push(c);//put the result into the stack of numbers
		}
		}
	);
	function.insert(
		{
			"^",
			[&](double a,double b) {double c = pow(b,a);//change order because the stack order is different from the initial order in the console
			number.push(c); }
		});
}

bool calcul::validation()
{
	//exception handling
	try
	{
		dll.read_files();
	}
	catch (std::exception)
	{
		std::cout << "Error in dll" << std::endl;
		return false;
	}
	return true;
}

template <typename T>//template, because we have two stacks of different types
void calcul::clearStack(std::stack <T>& s)
{
	while (s.size() != 0) {
		s.pop();
	}
	return;
}

void calcul::readthread()
{
	char c;
	while (c = std::cin.peek())
	{
		std::string s;
		std::stringstream ss;
		ss << c;
		ss >> s;
		if (c == '\n') break;
		if (c == ' ')
		{
			std::cin.ignore();
			continue;
		};
		if (((c >= '0') && (c <= '9')) || check_neg(s))//number 0 to 9 + negative number check
		{
			double value;
			std::cin >> value;//extracting a number from the stream
			number.push(value);
			continue;
		}
		if ((c == '+') || (c == '-') || (c == '/') || (c == '*') || (c == '(') || (c == '^'))
		{
			processing_oper(s);
			if ((number.size() != 0) || (operation.size() != 0)) std::cin.ignore();//extracting the viewed symbol from the stream
			continue;
		}
		if ((c == 'c') || (c == 'l') || (c == 's') || (c == 't') || (c == 'r') || (c == 'a'))
		{
			std::string nstand;
			while (c != '(') {
				nstand.push_back(c);
				std::cin.ignore();
				c = std::cin.peek();
				if ((c == ')') || (c == '\n')) break;//the expression was entered incorrectly
			}
			if ((c == ')') || (c == '\n'))
			{
				deleteStacksEr();
				break;
			}
			operation.push(nstand);
			continue;
		}
		if (c == ')')
		{
			while (operation.top() != "(")//we perform operations in parentheses
			{
				if (function.find(operation.top()) != function.end())
				{
					oper();
					if (operation.size() == 0) break;//if there was a division by 0, then the stacks became empty and it is necessary to stop the cycle
					continue;
				}
				expr_incor();
				break;
			}
			if (number.size() != 0) std::cin.ignore();//extracting the scanned symbol from the stream, provided that there was no stack clearing due to an incorrect expression
			if (operation.size() != 0)
			{
				operation.pop();//if there was no division by zero, then the opening bracket remains in the stack and it must be removed from the stack
				if (nonstandart() == -1)//checking that a non-standard function is valid
				{
					deleteStacksEr();
					break;
				}
			}
			continue;
		}
		//caught an incorrect character
		deleteStacksEr();
		break;
	}
}

void calcul::expr_incor()
{
	std::cout << "Expression entered incorrectly" << std::endl;
	clearStack(operation);
	clearStack(number);
}

void calcul::deleteStacksEr()
{
	std::string s;
	std::getline(std::cin, s, '\n');
	expr_incor();
	std::cout << "To continue, press Enter" << std::endl;
}

void calcul::processing_oper(std::string c)//processing of the received options
{
	if ((operation.empty()) || (c == "("))//in any case, the opening bracket is either at the beginning of the stack, or we put it on the stack on top of other operations
	{
		operation.push(c);
		return;
	}

	if (oper_priority[c] <= oper_priority[operation.top()])
		//if the operation in question has a priority less than or equal to the operation already lying on the stack, then first we will count the operation that is on the stack, and then we will add a new one
	{
		oper();
		if (number.size() != 0) operation.push(c);//check if the stack is not cleared after dividing by 0
		return;
	}
	//the stack with operations is not empty and the priority of the operation in question is not less than the one already placed on the stack
	operation.push(c);
	return;
}

bool calcul::check_neg(std::string c)//processing negative numbers if it is the first number in the expression or comes after the opening parenthesis
{
	if (c == "-")
	{
		if (number.size() == 0)
			return true;
		if (operation.size() != 0)
		{
			if ((operation.top() == "(") && (operation.size() > number.size()))//when '-' is immediately after the parentheses, the number of operations exceeds the number of numbers read
				return true;
		}
		return false;//c='-' but none of the conditions are met
	}
	return false;
}

void calcul::maths()//to process all raw operations with numbers
{
	while (operation.size() != 0)
	{
		if (function.find(operation.top()) != function.end())
		{
			oper();
			continue;
		}
		//there is no processing of functions from plugins as we consider them as soon as we met,
		//so that complex expressions using non-standard functions can be correctly calculated
		expr_incor();
		break;
	}
	if (number.size() != 0)
	{
		std::cout << "Result=" << number.top() << std::endl;
		number.pop();//deleting the last number in the stack (result)
	}
}

int calcul::nonstandart()
{
	if (dll.is_plugin(operation.top()))
	{
		double a = number.top();
		number.pop();
		if (!dll.calculation(operation.top(), a)) return -1;
		number.push(a);
		operation.pop();
		return 1;
	}
	return 0;
}

void calcul::oper()//handles only one standard operation with numbers
{
	double a, b;
	a = number.top();//took the top number from the stack
	number.pop();//removed the taken number from the stack
	b = number.top();//took the top number from the stack
	number.pop();//removed the taken number from the stack

	//taking an operation from the stack with operations
	function[operation.top()](a, b);
	if (operation.size() != 0) operation.pop();//we remove the operation from the stack, provided that it is not empty, after an attempt to divide by 0
}

calcul::~calcul()
{
	clearStack(operation);//clearing the stack with operations
	clearStack(number);//clearing the stack with numbers
	function.clear();//clearing the map with operations
	oper_priority.clear();//clearing the map with priorities
}