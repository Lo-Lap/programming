#include<cmath>
extern "C" __declspec(dllexport)

bool func(double& number) {
	number = std::abs(number);
	return true;
}