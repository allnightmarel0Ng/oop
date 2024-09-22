cmake_minimum_required(VERSION 3.25)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(lab5
        src/allocator.h
        src/main.cpp
        src/list.h)
