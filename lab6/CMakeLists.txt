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

add_executable(main
        src/main.cpp
        src/npc.cpp
        src/visitor.cpp
        src/factory.cpp
        src/observer.cpp
        src/game-handler.cpp)

add_executable(test
        tests/main.cpp
        src/npc.cpp
        src/visitor.cpp
        src/factory.cpp
        src/observer.cpp
        src/game-handler.cpp)
target_link_libraries(
        test
        PRIVATE
        gtest_main)