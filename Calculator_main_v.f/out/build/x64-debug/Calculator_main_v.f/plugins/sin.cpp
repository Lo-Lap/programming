#include<cmath>
#define _USE_MATH_DEFINES
#define pi 3.14159265358979323846
extern "C" __declspec(dllexport)

bool func(double& number) {
	double d=number;
	number=std::sin(number*pi/180);
	if (abs(cos(d * pi / 180)) == 1)
	{
		number=0;//  angle=0,pi; 2*pi..
	}
	return true;
}