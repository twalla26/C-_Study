cmake_minimum_required(VERSION 3.22)
project(note)

set(CMAKE_CXX_STANDARD 14)

add_executable(note Point.h Point.cpp Rectangle.h Rectangle.cpp RectangleConstructor.cpp)
