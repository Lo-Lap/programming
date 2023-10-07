#include <cmath>
#include <iostream>
extern "C" __declspec(dllexport)

bool func(double& number) {
	if (number <= 0)
	{
		std::cout << "The logarithm of a non-positive number does not exist" << std::endl;
		return false;
	}
	number = std::log(number);
	return true;
}