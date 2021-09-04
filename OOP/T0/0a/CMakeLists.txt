cmake_minimum_required(VERSION 3.0.0)
project(task1 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(task1 main.cpp src/module1.cpp src/module2.cpp include/module1.h include/module2.h include/module3.h src/module3.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
