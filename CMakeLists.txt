cmake_minimum_required(VERSION 3.3)
project(logicRegression)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c main.h logictree.c logictree.h)

include_directories(.)

add_executable(logicRegression ${SOURCE_FILES})