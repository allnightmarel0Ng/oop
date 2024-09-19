cmake_minimum_required(VERSION 3.25)
project(lab2)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)

FetchContent_MakeAvailable(
        googletest)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(lab2_tests
        src/octal.cpp
        src/octal.h
        tests/lab2_tests.cpp)
target_link_libraries(
        lab2_tests
        PRIVATE
        gtest_main
)