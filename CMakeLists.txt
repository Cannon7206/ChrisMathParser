cmake_minimum_required(VERSION 3.31)
project(ChrisMathParser)

set(CMAKE_CXX_STANDARD 20)

add_library(MathParser STATIC ChrisMath.cpp
        funct.cpp
        funct.h
)
