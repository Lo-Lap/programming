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


class calcul
{
private:
    std::stack <double> number;
    std::stack <std::string> operation;
    std::map <std::string, int> oper_priority;//mathematical operations priorities
    std::map <std::string, std::function<void(double, double)>> function;//correlation of a mathematical operation and what it does
    dll_read dll;
    bool check_neg(std::string c);
    void oper();
    int nonstandart();
    void deleteStacksEr();
    void processing_oper(std::string c);
    template <typename T>
    void clearStack(std::stack <T>& s);

public:
    calcul();
    bool validation();
    void readthread();
    void maths();
    ~calcul();
};
#endif