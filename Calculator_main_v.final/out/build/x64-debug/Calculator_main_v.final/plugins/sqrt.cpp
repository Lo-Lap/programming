#include<cmath>
#include <iostream>
extern "C" __declspec(dllexport)

bool func(double& number) {	
	if (number<0) 
	{
		std::cout<<"there is no square root of a negative number"<<std::endl;
		return false;
	}
	number=std::sqrt(number);
	return true;
}