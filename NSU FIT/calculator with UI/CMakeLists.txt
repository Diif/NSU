cmake_minimum_required(VERSION 3.17)
project(lab C)

set(CMAKE_C_STANDARD 99)

add_definitions(-DPATH="${CMAKE_SOURCE_DIR}/")
add_executable(lab main.c sources/toPostfix.c headers/toPostfix.h sources/calc.c headers/calc.h sources/generalLib.c headers/generalLib.h)