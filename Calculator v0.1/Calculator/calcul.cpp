#include "calcul.h"

int priority(char c)//���������� ��������
{
	if ((c == '+') || (c == '-')) return 1;
	if ((c == '*') || (c == '/')) return 2;
	return 0;
}

void calcul::processing_oper(char c)//��������� ���������� ��������
{
	if ((operation.size() == 0) || (c == '('))//����������� ������ � ����� ������ ���� � ������ �����, ���� ����� � ���� ������ ������ ��������
	{
		operation.push(c);
		cin.ignore();//��������� ������������� ������ �� ������
		return;
	}

	if (priority(c) <= priority(operation.top()))
		//���� � ��������������� �������� ��������� ������ ��� ����� ��� ������� �� ����� ��������, �� ������� ��������� ��������, ������� ���� �� �����, � ����� ������� �����
	{
		oper();
		operation.push(c);
		cin.ignore();//��������� ������������� ������ �� ������
		return;
	}
	//���� � ���������� �� ���� � ��������� ��������������� �������� �� ������, ��� ��� ���������� �� ����
	operation.push(c);
	cin.ignore();//��������� ������������� ������ �� ������
	return;
}

bool calcul::check_neg(char c)//��������� ������������� �����, ���� ��� ������ ����� � ��������� ��� ��� ����� ����������� ��������
{
	if (c == '-')
	{
		if (number.size() == 0)
			return true;
		if ((operation.top() == '(') && (operation.size() > number.size()))//����� - ����� ����� ������, �� ���������� �������� ��������� ���������� ��������� �����
		{
			return true;
		}
		return false;//c='-' �� �� ���� �� ������� �� ���������
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
		if (((c >= '0') && (c <= '9')) || check_neg(c))//������� ����� �� 0 �� 9 + 
		{
			double value;
			cin >> value;//��������� ����� �� ������
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
			while (operation.top() != '(')//��������� ������� � ���������
			{
				oper();
			}
			operation.pop();//������� ������������� ������
			cin.ignore();//��������� ������������� ������ �� ������
			continue;
		}

		cout << "Expression entered incorrectly" << endl;
		break;

	}
}

calcul::calcul()
{

}


void calcul::maths()//����� ���������� ��� �������������� �������� � �������
{
	while (operation.size() != 0)
	{
		oper();
	}
	if (number.size() != 0) cout << "Result=" << number.top() << endl;
	number.pop();//������� ��������� ����� � �����
}

void calcul::oper()//������������ ������ ���� �������� � �������
{
	double a, b, c;
	a = number.top();//����� �������� ����� �� �����
	number.pop();//������� ������ ����� �� �����
	b=number.top();//����� �������� ����� �� �����
	number.pop();//������� ������ ����� �� �����
	//���� �������� �� ����� � ����������
	switch (operation.top())
	{
	case '+': sum(a, b); break;
	case '-': substraction(b, a); break;//������ �������. ��� ��� ������� � ����� ���������� �� ������������ ������� � �������
	case '*': multiplication(a, b); break;
	case '/': division(b, a); break;//������ �������. ��� ��� ������� � ����� ���������� �� ������������ ������� � �������
	}
	if (operation.size()!=0) operation.pop();//������� �������� �� ����� ��� �������, ��� �� �� ����, ����� ������� ������� �� 0
}

void calcul::sum(double a, double b)
{
	double c = a + b;
	number.push(c);//����� ��������� � ���� � �������
}
void calcul::substraction(double a, double b)
{
	double c = a - b;
	number.push(c);//����� ��������� � ���� � �������
}


template <typename T>//������, ��� ��� � ��� ��� ����� ������ �����
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
		//����� ������ �� ������������ ��������, ������� ����� ����� � ��������
		clearStack(operation);
		clearStack(number);
		return;
	}
	double c = a / b;
	number.push(c);//����� ��������� � ���� � �������
}
void calcul::multiplication(double a, double b)
{
	double c = a * b;
	number.push(c);//����� ��������� � ���� � �������
}