cmake_minimum_required(VERSION 3.25)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)

FetchContent_MakeAvailable(
        googletest)

add_executable(main
        src/main.cpp
        src/rectangle.h
        src/point.h
        src/trapezoid.h
        src/rhombus.h
        src/vector.h)

add_executable(test 
        tests/main.cpp
        src/rectangle.h
        src/point.h
        src/trapezoid.h
        src/rhombus.h
        src/vector.h)
target_link_libraries(
        test
        PRIVATE
        gtest_main)
