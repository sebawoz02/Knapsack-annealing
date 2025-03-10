cmake_minimum_required(VERSION 3.22)
project(Knapsack_annealing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

set(SOURCES )

add_executable(annealing.out app/main.cpp ${SOURCES})

target_include_directories(annealing.out PRIVATE inc)

#  --- Uncomment after creating first testcase ---
# Include GoogleTest
# include(FetchContent)
# FetchContent_Declare(
#         googletest
#         URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )
# FetchContent_MakeAvailable(googletest)

# enable_testing()

# Create test executable
# add_executable(test.out test/main.cpp ${SOURCES})
# target_include_directories(test.out PRIVATE inc)
# target_link_libraries(test.out PRIVATE gtest_main)

# Register tests
# include(GoogleTest)
# gtest_discover_tests(test.out)
# --- END  ---