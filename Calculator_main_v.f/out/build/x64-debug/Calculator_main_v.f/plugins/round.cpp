#include<cmath>
extern "C" __declspec(dllexport)

bool func(double& number) {
	number=std::floor(number);
	return true;
}