# CMakeList.txt : CMake project for Calculator_main_v.final, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project( Calculator_main )
set(CMAKE_CXX_STANDARD 20)
# Add source to this project's executable.

set(PROJECT_HEADERS Calculator_main.h, calcul.h)
add_executable(Calculator_main ${PROJECT_SOURCE_DIR}/ Calculator_main.cpp calcul.cpp "dll_read.cpp" "dll_read.h")

add_library(cos SHARED ./plugins/cos.cpp "plugins/cos.cpp" "dll_read.cpp" "dll_read.h")
add_library(lg SHARED ./plugins/lg.cpp "plugins/lg.cpp" "dll_read.cpp" "dll_read.h")
add_library(sin SHARED ./plugins/sin.cpp "plugins/sin.cpp" "dll_read.cpp" "dll_read.h")
add_library(tg SHARED ./plugins/tg.cpp "plugins/tg.cpp" "dll_read.cpp" "dll_read.h")
add_library(ctg SHARED ./plugins/ctg.cpp "plugins/ctg.cpp" "dll_read.cpp" "dll_read.h")
add_library(ln SHARED ./plugins/ln.cpp "plugins/ln.cpp" "dll_read.cpp" "dll_read.h")
add_library(sqrt SHARED ./plugins/sqrt.cpp "plugins/sqrt.cpp" "dll_read.cpp" "dll_read.h")
add_library(cubsqrt SHARED ./plugins/cubsqrt.cpp "plugins/cubsqrt.cpp" "dll_read.cpp" "dll_read.h")
add_library(abs SHARED ./plugins/abs.cpp "plugins/abs.cpp" "dll_read.cpp" "dll_read.h")
add_library(round SHARED ./plugins/round.cpp "plugins/round.cpp" "dll_read.cpp" "dll_read.h")

target_link_libraries(Calculator_main cos lg sin tg ctg ln sqrt cubsqrt abs round)

