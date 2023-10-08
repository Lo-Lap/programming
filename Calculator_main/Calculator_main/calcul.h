#pragma once
#ifndef calcul_h
#define calcul_h

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <functional>
#include <map>
#include <limits>
#include <ios> 

#include "dll_read.h"


using namespace std;

class calcul
{
private:
    stack <double> number;
    stack <string> operation;
    map <string, int> oper_priority;//приоритеты математических операций
    map <string, function<void(double, double)>> function;//соотнесение математической операции и то, что она делает
    dll_read dll;

public:
    calcul();
    void readthread();
    bool check_neg(string c);
    void maths();
    void oper();
    void nonstandart();
    void processing_oper(string c);
    template <typename T>
    void clearStack(stack <T>& s);
    ~calcul();

};
#endif