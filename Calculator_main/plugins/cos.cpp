#include<cmath>
#define _USE_MATH_DEFINES
#define M_PI   3.14159265358979323846

extern "C" __declspec(dllexport)

double func(double number) {
	return std::cos(number*M_PI/180);
}