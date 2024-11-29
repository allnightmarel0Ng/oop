cmake_minimum_required(VERSION 3.25)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)

FetchContent_MakeAvailable(
        googletest)

add_executable(
        main
        src/main.cpp
)
target_include_directories(
        main
        PRIVATE
        ./include/
)

add_executable(
        tests
        tests/main.cpp
)
target_link_libraries(
        tests
        PRIVATE
        gtest_main
)
target_include_directories(
        tests
        PRIVATE
        ./include/
)