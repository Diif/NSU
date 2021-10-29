cmake_minimum_required(VERSION 3.0.0)
project(lab4 VERSION 0.1.0)

include(CTest)
enable_testing()

# set(OpenCV_STATIC ON)
 SET("OpenCV_DIR" "C:\\Program Files (x86)\\opencv\\build")
find_package( OpenCV REQUIRED )

add_executable(lab4 main.cpp )

target_link_libraries(lab4 ${OpenCV_LIBS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
