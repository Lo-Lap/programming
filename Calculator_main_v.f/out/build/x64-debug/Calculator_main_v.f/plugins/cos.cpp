#include<cmath>
#define _USE_MATH_DEFINES
#define pi 3.14159265358979323846
extern "C" __declspec(dllexport)

bool func(double& number) {
	double d=number;
	number=std::cos(number*pi/180);
	if (abs(sin(d * pi / 180)) == 1) 
	{
		number=0;// angle= pi/2, 3*pi/2..
	}
	
	return true;
}