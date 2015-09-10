cmake_minimum_required(VERSION 3.3)
project(logicRegression)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -std=c11")

set(SOURCE_FILES src/main.c include/main.h src/logictree.c include/logictree.h)

include_directories(./include)

add_executable(logicRegression ${SOURCE_FILES})