cmake_minimum_required(VERSION 3.14.0)
project(tritlog VERSION 0.1.0)

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

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tritlog main.cpp tritset.cpp tritset.h test_tritset.cpp)
# add_executable(example example.cpp)
target_link_libraries(tritlog gtest_main)

# add_executable(tritlog main.cpp tritset.cpp tritset.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
