cmake_minimum_required(VERSION 3.0.0)
project(iterationGrad VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(-Wall -Wextra -O3)

add_executable(iterationGrad main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
