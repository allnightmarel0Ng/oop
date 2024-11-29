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

add_executable(
        tests
        src/octal.cpp
        tests/main.cpp)
target_link_libraries(
        tests
        PRIVATE
        gtest_main)
target_include_directories(
        tests
        PUBLIC
        ./include/)