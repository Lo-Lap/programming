#pragma once
#ifndef calcul_h
#define calcul_h

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

class calcul
{
private:
    stack <double> number;
    stack <char> operation;

public:
    calcul();
    void readthread();
    bool check_neg(char c);
    void maths();
    void oper();
    void processing_oper(char c);
    void sum(double a, double b);
    void substraction(double a, double b);
    void division(double a, double b);
    void multiplication(double a, double b);



}; 
#endif