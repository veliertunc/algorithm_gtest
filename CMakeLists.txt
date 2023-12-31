cmake_minimum_required(VERSION 3.14)

project(algorithm_gtest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    algo_test
    test_main.cpp
)

target_link_libraries(
    algo_test
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(algo_test)
