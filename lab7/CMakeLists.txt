cmake_minimum_required(VERSION 3.25)
project(lab7)

set(CXX_STANDARD_REQUIRED 20)

add_executable(
        main
        src/main.cpp
        src/npc.cpp
        src/visitor.cpp
        src/factory.cpp
        src/fighter.cpp
        src/game_handler.cpp
)
target_include_directories(
        main
        PUBLIC
        ./include/
)