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

add_executable(
        main
        src/main.cpp
        src/balance.cpp
)
target_include_directories(
        main
        PUBLIC
        ./include/
)

add_executable(
        tests
        tests/main.cpp
        src/balance.cpp
)
target_link_libraries(
        tests
        PRIVATE
        gtest_main
)
target_include_directories(
        tests
        PUBLIC
        ./include/
)