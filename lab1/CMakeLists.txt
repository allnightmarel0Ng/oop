cmake_minimum_required(VERSION 3.21)
project(lab1)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)

FetchContent_MakeAvailable(
        googletest)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(lab1
        src/main.cpp
        src/balance.cpp
        src/balance.h)

add_executable(lab1_tests
        tests/lab1_tests.cpp
        src/balance.cpp
        src/balance.h)
target_link_libraries(
        lab1_tests
        PRIVATE
        gtest_main
)