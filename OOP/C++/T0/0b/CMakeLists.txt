cmake_minimum_required(VERSION 3.0.0)
project(task1 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(task1 main.cpp src/solution.cpp include/solution.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
