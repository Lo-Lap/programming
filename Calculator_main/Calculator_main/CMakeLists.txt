# CMakeList.txt : CMake project for Calculator_main, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project( Calculator_main )

set(CMAKE_CXX_STANDARD 20)

add_executable (Calculator_main "Calculator_main.cpp" "Calculator_main.h" "calcul.cpp" "calcul.h" "dll_read.h" "dll_read.cpp")

set( SOURCE_LIB C:/program_visual_studio/programming/Calculator_main/plugins )

set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library(cos SHARED ${SOURCE_LIB}/cos.cpp )	

add_library(lg SHARED ${SOURCE_LIB}/lg.cpp)	

target_link_libraries(Calculator_main cos lg)
