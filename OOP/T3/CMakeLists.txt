cmake_minimum_required(VERSION 3.0.0)
project(see_battle VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(see_battle main.cpp option_handler.cpp option_handler.h game_session.h game_session.cpp include/optionparser.h)
target_include_directories(see_battle PUBLIC include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
