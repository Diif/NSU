cmake_minimum_required(VERSION 3.0.0)
project(see_battle VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
include_directories(src)


add_executable(see_battle main.cpp include/ship.h src/ship.cpp src/option_handler.cpp src/game_master.cpp src/game_field.cpp src/game_session.cpp src/coordinates.cpp include/option_handler.h include/game_session.h include/game_master.h  include/player.h include/game_field.h include/optionparser.h include/coordinates.h)
target_include_directories(see_battle PUBLIC include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
