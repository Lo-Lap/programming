#include <cmath>
#include <iostream>
extern "C" __declspec(dllexport)

double func(double number) {
	if (number <= 0)
	{
		std::cout << "The logarithm of a non-positive number does not exist" << std::endl;
	}
	return std::log10(number);
}