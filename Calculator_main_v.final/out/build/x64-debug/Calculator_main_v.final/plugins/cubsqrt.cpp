#include<cmath>
#include <iostream>
extern "C" __declspec(dllexport)

bool func(double& number) {	
	number=std::cbrt(number);
	return true;
}