#pragma once
#ifndef dll_read_h
#define dll_read_h

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <Windows.h>


class dll_read
{
private:
	std::map <std::string, std::function<double(double&)>> function;
	std::string p = ".\\plugins\\";

public:
	dll_read() {};
	void read_files();
	bool is_plugin(std::string s);
	bool calculation(std::string s, double& number);
	~dll_read() { function.clear(); };
};

#endif