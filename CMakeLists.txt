cmake_minimum_required(VERSION 3.28)
project(SlidingPuzzleFinal)

set(CMAKE_CXX_STANDARD 17)

add_executable(SlidingPuzzleFinal main.cpp
        utilities.h
        utilities.cpp
        node.cpp
        node.h)
