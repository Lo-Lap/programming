#include "dll_read.h"

dll_read::dll_read() {
	WIN32_FIND_DATAA detect;
	HANDLE det = FindFirstFileA((p + std::string("*.dll")).c_str(), &detect);
	if (det == INVALID_HANDLE_VALUE) {
		throw std::exception();//библиотека не существует
		return;
	}
	do {
		std::string func_name(detect.cFileName);
		HMODULE hm = LoadLibraryA((p + func_name).c_str());
		if (!hm) throw std::exception();//проблема в загрузке библиотеки

		std::string funct = func_name.substr(0, func_name.find(".dll"));

		auto func = (double (*) (double))GetProcAddress(hm, "func");

		if (func) {
			function.insert(std::pair<std::string, double(*)(double)>(funct, func));
			continue;
		}
		throw std::exception();
	} while (FindNextFileA(det, &detect) != NULL);
}

double dll_read::calculation(std::string s, double num) {
	
	return(function[s](num));
}

bool dll_read::is_plugin(std::string str) {
	return(function.find(str) != function.end());
}