cmake_minimum_required(VERSION 3.13)
project(OpenMp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_executable(OpenMp src/main.cpp src/openmp/run.cpp src/openmp/run.h)