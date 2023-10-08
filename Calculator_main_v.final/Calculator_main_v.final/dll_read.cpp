#include "dll_read.h"


void dll_read::read_files() {
	WIN32_FIND_DATAA detect;
	HANDLE det = FindFirstFileA((p + std::string("*.dll")).c_str(), &detect);

	if (det == INVALID_HANDLE_VALUE) {
		throw std::exception();//the library does not exist
		return;
	}
	do {
		std::string func_name(detect.cFileName);
		HMODULE hm = LoadLibraryA((p + func_name).c_str());
		if (!hm) throw std::exception();//the problem is loading the library

		std::string funct = func_name.substr(0, func_name.find(".dll"));

		auto func = (bool (*) (double&))GetProcAddress(hm, "func");

		if (func) {
			function.insert(std::pair<std::string, bool(*)(double&)>(funct, func));
			continue;
		}
		throw std::exception();//error in extracting the function address
	} while (FindNextFileA(det, &detect) != NULL);
}


bool dll_read::calculation(std::string s, double& num) {
	return(function[s](num));
}

bool dll_read::is_plugin(std::string str) {
	return(function.find(str) != function.end());
}