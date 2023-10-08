#include "calcul.h"

template <typename T>//шаблон, так как у нас два стека разных типов
void calcul::clearStack(stack <T>& s)
{
	while (s.size() != 0) {
		s.pop();
	}
	return;
}

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
		[&](double a,double b) {double c = a + b; number.push(c); }//кладём результат в стек с числами
		}
	);
	function.insert(
		{ "-",
		[&](double a,double b)
		{double c = b - a;//меняем порядок. так как порядок в стеке отличается от изначального порядка в консоли
		number.push(c);
		}//кладём результат в стек с числами
		}
	);
	function.insert(
		{ "*",
		[&](double a,double b) {double c = a * b; number.push(c); }//кладём результат в стек с числами
		}
	);
	function.insert(
		{ "/",
		[&](double a,double b) {if (a == 0)
		{
		cout << "Error. You can't divide by zero" << endl;
		//Чтобы дальше не обрабатывать операции, очищаем стеки чисел и операций
		clearStack(operation);
		clearStack(number);
		return;
		}
		double c = b / a;//меняем порядок. так как порядок в стеке отличается от изначального порядка в консоли
		number.push(c);//кладём результат в стек с числами
		}
		}
	);
	function.insert(
		{
			"^",
			[&](double a,double b) {double c = pow(b,a);//меняем порядок. так как порядок в стеке отличается от изначального порядка в консоли
			number.push(c); }
		});
}

void calcul::readthread()
{
	char c;
	while (c = cin.peek())
	{
		std::string s;
		std::stringstream ss;
		ss << c;
		ss >> s;
		if (c == '\n') break;
		if (c == ' ')
		{
			cin.ignore();
			continue;
		};
		if (((c >= '0') && (c <= '9')) || check_neg(s))//словили цифру от 0 до 9 + 
		{
			double value;
			cin >> value;//извлекаем число из потока
			number.push(value);
			continue;
		}
		if ((c == '+') || (c == '-') || (c == '/') || (c == '*') || (c == '(') || (c == '^'))
		{
			processing_oper(s);
			continue;
		}
		if ((c == 'c') || (c == 'l'))
		{
			string nstand;
			while (c != '(') {
				nstand.push_back(c);
				cin.ignore();
				c = cin.peek();
			}

			operation.push(nstand);

			continue;
		}
		if (c == ')')
		{
			while (operation.top() != "(")//выполняем опрации в скобочках
			{
				oper();
			}
			operation.pop();//удаляем открывающуюся скобку
			cin.ignore();//извлекаем просмотренный символ из потока
			if (operation.size()!=0) nonstandart();//если после '(' сразу идёт нестандартная функция, сразу её считаем, чтобы не возникало проблем при подсчёте сложных выражений  
			continue;
		}
	}
}

void calcul::processing_oper(string c)//обработка полученных опреаций
{
	if ((operation.size() == 0) || (c == "("))//открывающую скобку в любом случае либо в начало стека, либо кладём в стек поверх других операций
	{
		operation.push(c);
		cin.ignore();//извлекаем просмотренный символ из потока
		return;
	}

	if (oper_priority[c] <= oper_priority[operation.top()])
		//если у рассматриваемой операции приоритет меньше или равен уже лежащей на стеке операции, то сначала посчитаем операцию, которая есть на стеке, а потом добавим новую
	{
		oper();
		operation.push(c);
		cin.ignore();//извлекаем просмотренный символ из потока
		return;
	}
	//стек с операциями не пуст и приоритет рассматриваемой операции не меньше, чем уже положенная на стек
	operation.push(c);
	cin.ignore();//извлекаем просмотренный символ из потока
	return;
}

bool calcul::check_neg(string c)//обработка отрицательных чисел, если оно первое число в выражении или идёт после открывающей скобочки
{
	if (c == "-")
	{
		if (number.size() == 0)
			return true;
		if (operation.size() != 0)
		{
			if ((operation.top() == "(") && (operation.size() > number.size()))//когда - сразу после скобок, то количество операций превышает количество считанных чисел
			return true;
		}
		return false;//c='-' но ни одно из условий не выполнено
	}
	return false;
}


void calcul::maths()//чтобы обработать все необработанные операции с числами
{
	while (operation.size() != 0)
	{
		if (function.find(operation.top()) != function.end())
		{
			oper();
			continue;
		}
		//нет обработки функций из plagins так как их считаем сразу как встретились,
		//чтобы можно было правильно вычислять сложные выражения использующие нестандартные функции
		cout << "Expression entered incorrectly" << endl;
		clearStack(operation);
		clearStack(number);
		break;
	}
	if (number.size() != 0)
	{
		cout << "Result=" << number.top() << endl;
		number.pop();//удаляем последнее число в стеке (результат)
	}
}

void calcul::nonstandart()
{
	if (dll.is_plugin(operation.top()))
	{
		double a = number.top();
		number.pop();
		double result = dll.calculation(operation.top(), a);
		number.push(result);
		operation.pop();
	}
}

void calcul::oper()//обрабатывает только одну стандартную операцию с числами
{
	double a, b, c;
	a = number.top();//взяли вверхнее число из стека
	number.pop();//удалили взятое число из стека
	b = number.top();//взяли вверхнее число из стека
	number.pop();//удалили взятое число из стека

	//берём операцию из стека с операциями
	function[operation.top()](a, b);
	if (operation.size() != 0) operation.pop();//удаляем операцию из стека при условии, что он не пуст, после попытки деления на 0
}


calcul::~calcul()
{
	clearStack(operation);//очищаем стек с опреациями
	clearStack(number);//очищаем стек с числами
	function.clear();//очищаем map с операциями
	oper_priority.clear();//очищаем map с приоритетами
}