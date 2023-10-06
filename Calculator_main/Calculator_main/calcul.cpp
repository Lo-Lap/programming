#include "calcul.h"

template <typename T>//������, ��� ��� � ��� ��� ����� ������ �����
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
		[&](double a,double b) {double c = a + b; number.push(c); }//����� ��������� � ���� � �������
		}
	);
	function.insert(
		{ "-",
		[&](double a,double b)
		{double c = b - a;//������ �������. ��� ��� ������� � ����� ���������� �� ������������ ������� � �������
		number.push(c);
		}//����� ��������� � ���� � �������
		}
	);
	function.insert(
		{ "*",
		[&](double a,double b) {double c = a * b; number.push(c); }//����� ��������� � ���� � �������
		}
	);
	function.insert(
		{ "/",
		[&](double a,double b) {if (a == 0)
		{
		cout << "Error. You can't divide by zero" << endl;
		//����� ������ �� ������������ ��������, ������� ����� ����� � ��������
		clearStack(operation);
		clearStack(number);
		return;
		}
		double c = b / a;//������ �������. ��� ��� ������� � ����� ���������� �� ������������ ������� � �������
		number.push(c);//����� ��������� � ���� � �������
		}
		}
	);
	function.insert(
		{
			"^",
			[&](double a,double b) {double c = pow(b,a);//������ �������. ��� ��� ������� � ����� ���������� �� ������������ ������� � �������
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
		if (((c >= '0') && (c <= '9')) || check_neg(s))//������� ����� �� 0 �� 9 + 
		{
			double value;
			cin >> value;//��������� ����� �� ������
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
			while (operation.top() != "(")//��������� ������� � ���������
			{
				oper();
			}
			operation.pop();//������� ������������� ������
			cin.ignore();//��������� ������������� ������ �� ������
			if (operation.size()!=0) nonstandart();//���� ����� '(' ����� ��� ������������� �������, ����� � �������, ����� �� ��������� ������� ��� �������� ������� ���������  
			continue;
		}
	}
}

void calcul::processing_oper(string c)//��������� ���������� ��������
{
	if ((operation.size() == 0) || (c == "("))//����������� ������ � ����� ������ ���� � ������ �����, ���� ����� � ���� ������ ������ ��������
	{
		operation.push(c);
		cin.ignore();//��������� ������������� ������ �� ������
		return;
	}

	if (oper_priority[c] <= oper_priority[operation.top()])
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

bool calcul::check_neg(string c)//��������� ������������� �����, ���� ��� ������ ����� � ��������� ��� ��� ����� ����������� ��������
{
	if (c == "-")
	{
		if (number.size() == 0)
			return true;
		if (operation.size() != 0)
		{
			if ((operation.top() == "(") && (operation.size() > number.size()))//����� - ����� ����� ������, �� ���������� �������� ��������� ���������� ��������� �����
			return true;
		}
		return false;//c='-' �� �� ���� �� ������� �� ���������
	}
	return false;
}


void calcul::maths()//����� ���������� ��� �������������� �������� � �������
{
	while (operation.size() != 0)
	{
		if (function.find(operation.top()) != function.end())
		{
			oper();
			continue;
		}
		//��� ��������� ������� �� plagins ��� ��� �� ������� ����� ��� �����������,
		//����� ����� ���� ��������� ��������� ������� ��������� ������������ ������������� �������
		cout << "Expression entered incorrectly" << endl;
		clearStack(operation);
		clearStack(number);
		break;
	}
	if (number.size() != 0)
	{
		cout << "Result=" << number.top() << endl;
		number.pop();//������� ��������� ����� � ����� (���������)
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

void calcul::oper()//������������ ������ ���� ����������� �������� � �������
{
	double a, b, c;
	a = number.top();//����� �������� ����� �� �����
	number.pop();//������� ������ ����� �� �����
	b = number.top();//����� �������� ����� �� �����
	number.pop();//������� ������ ����� �� �����

	//���� �������� �� ����� � ����������
	function[operation.top()](a, b);
	if (operation.size() != 0) operation.pop();//������� �������� �� ����� ��� �������, ��� �� �� ����, ����� ������� ������� �� 0
}


calcul::~calcul()
{
	clearStack(operation);//������� ���� � ����������
	clearStack(number);//������� ���� � �������
	function.clear();//������� map � ����������
	oper_priority.clear();//������� map � ������������
}