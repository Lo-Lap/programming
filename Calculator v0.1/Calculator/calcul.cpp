#include "calcul.h"

int priority(char c)//приоритеты операций
{
	if ((c == '+') || (c == '-')) return 1;
	if ((c == '*') || (c == '/')) return 2;
	return 0;
}

void calcul::processing_oper(char c)//обработка полученных опреаций
{
	if ((operation.size() == 0) || (c == '('))//открывающую скобку в любом случае либо в начало стека, либо кладём в стек поверх других операций
	{
		operation.push(c);
		cin.ignore();//извлекаем просмотренный символ из потока
		return;
	}

	if (priority(c) <= priority(operation.top()))
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

bool calcul::check_neg(char c)//обработка отрицательных чисел, если оно первое число в выражении или идёт после открывающей скобочки
{
	if (c == '-')
	{
		if (number.size() == 0)
			return true;
		if ((operation.top() == '(') && (operation.size() > number.size()))//когда - сразу после скобок, то количесвто операций превышает количество считанных чисел
		{
			return true;
		}
		return false;//c='-' но ни одно из условий не выполнено
	}
	return false;
}

void calcul::readthread()
{
	char c;
	while (c = cin.peek())
	{
		if (c == '\n') break;
		if (c == ' ')
		{
			cin.ignore();
			continue;
		};
		if (((c >= '0') && (c <= '9')) || check_neg(c))//словили цифру от 0 до 9 + 
		{
			double value;
			cin >> value;//извлекаем число из потока
			number.push(value);
			continue;
		}
		if ((c == '+') || (c == '-') || (c == '/') || (c == '*') || (c == '('))
		{
			processing_oper(c);
			continue;
		}
		if (c == ')')
		{
			while (operation.top() != '(')//выполняем опрации в скобочках
			{
				oper();
			}
			operation.pop();//удаляем открывающуюся скобку
			cin.ignore();//извлекаем просмотренный символ из потока
			continue;
		}

		cout << "Expression entered incorrectly" << endl;
		break;

	}
}

calcul::calcul()
{

}


void calcul::maths()//чтобы обработать все необработанные операции с числами
{
	while (operation.size() != 0)
	{
		oper();
	}
	if (number.size() != 0) cout << "Result=" << number.top() << endl;
	number.pop();//удаляем последнее число в стеке
}

void calcul::oper()//обрабатывает только одну операцию с числами
{
	double a, b, c;
	a = number.top();//взяли вверхнее число из стека
	number.pop();//удалили взятое число из стека
	b=number.top();//взяли вверхнее число из стека
	number.pop();//удалили взятое число из стека
	//берём операцию из стека с операциями
	switch (operation.top())
	{
	case '+': sum(a, b); break;
	case '-': substraction(b, a); break;//меняем порядок. так как порядок в стеке отличается от изначального порядка в консоли
	case '*': multiplication(a, b); break;
	case '/': division(b, a); break;//меняем порядок. так как порядок в стеке отличается от изначального порядка в консоли
	}
	if (operation.size()!=0) operation.pop();//удаляем операцию из стека при условии, что он не пуст, после попытки деления на 0
}

void calcul::sum(double a, double b)
{
	double c = a + b;
	number.push(c);//кладём результат в стек с числами
}
void calcul::substraction(double a, double b)
{
	double c = a - b;
	number.push(c);//кладём результат в стек с числами
}


template <typename T>//шаблон, так как у нас два стека разных типов
void clearStack(stack <T>& s)
{
	while (s.size() != 0) {
		s.pop();
	}
	return;
}

void calcul::division(double a, double b)
{
	if (b == 0)
	{
		cout<<"Error. You can't divide by zero";
		//Чтобы дальше не обрабатывать операции, очищаем стеки чисел и операций
		clearStack(operation);
		clearStack(number);
		return;
	}
	double c = a / b;
	number.push(c);//кладём результат в стек с числами
}
void calcul::multiplication(double a, double b)
{
	double c = a * b;
	number.push(c);//кладём результат в стек с числами
}