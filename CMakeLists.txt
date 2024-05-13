cmake_minimum_required(VERSION 3.26)
project(crypto)

set(CMAKE_CXX_STANDARD 17)

add_executable(crypto main.cpp
        Lab1.h
        Lab1.cpp
        Lab2.cpp
        Convertor.cpp
        Tests.cpp)
