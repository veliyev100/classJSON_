cmake_minimum_required(VERSION 3.29)
project(classJSON)

set(CMAKE_CXX_STANDARD 20)

add_executable(classJSON main.cpp
        JSON.h
        parser.cpp)
