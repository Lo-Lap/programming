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
	std::map <std::string, std::function<double(double)>> function;
	std::string p = "C:\\program_visual_studio\\programming\\Calculator_main\\plugins\\";
public:
	dll_read();
	bool is_plugin(std::string s);
	double calculation(std::string s,double number);
};

#endif