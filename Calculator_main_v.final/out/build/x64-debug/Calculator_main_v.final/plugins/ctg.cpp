#include<cmath>
#include <iostream>
#define _USE_MATH_DEFINES
#define pi 3.14159265358979323846
extern "C" __declspec(dllexport)

bool func(double& number) {
	if (abs(cos(number * pi / 180)) == 1)//in this case sin=0
	{
		std::cout << "The cotangent from 0 does not exist" << std::endl;
		return false;
	}
	double d=number;
	number = std::cos(number * pi / 180) / std::sin(number * pi / 180);
	if (abs(sin(d * pi / 180)) == 1) number=0;
	return true;
}