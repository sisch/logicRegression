cmake_minimum_required(VERSION 3.3)
project(logicRegression)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(./include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -std=c11")

set(SOURCE_FILES src/main.c src/logictree.c src/helpers.c src/model.c)
add_executable(logicRegression ${SOURCE_FILES})

set(SOURCE_TEST src/logictree.c src/helpers.c src/test.c src/model.c)
add_executable(test_logicregression ${SOURCE_TEST})
