cmake_minimum_required(VERSION 3.29)
project(CAB401_A2_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(CAB401_A2_Project main.cpp
        cvtree/improved.cpp
        cvtree/tidy.cpp
        cvtree.h)
