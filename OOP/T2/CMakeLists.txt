cmake_minimum_required(VERSION 3.0.0)
project(workflow VERSION 0.1.0)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# add_executable(workflow main.cpp config_handler.h exceptions.h config_handler.cpp config_handler_test.cpp exceptions.cpp)
add_executable(workflow main.cpp)

target_link_libraries(workflow gtest_main)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
