cmake_minimum_required(VERSION 3.25)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3
        src/main.cpp
        src/figure.h
        src/rectangle.h
        src/rectangle.cpp
        src/point.cpp
        src/point.h
        src/trapezoid.cpp
        src/trapezoid.h
        src/trapezoid.h)
