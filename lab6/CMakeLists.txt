cmake_minimum_required(VERSION 3.25)
project(lab6)

set(CXX_STANDARD_REQUIRED 20)

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
        src/npc.cpp
        src/visitor.cpp
        src/factory.cpp
        src/observer.cpp
        src/game_handler.cpp
)
target_include_directories(
        main
        PUBLIC
        ./include/
)

add_executable(
        tests
        tests/main.cpp
        src/npc.cpp
        src/visitor.cpp
        src/factory.cpp
        src/observer.cpp
        src/game_handler.cpp
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