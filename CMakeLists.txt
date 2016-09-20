
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(imgmaker C CXX)

set(MY_SOURCES
	src/main.cpp
	src/SomeClass.cpp
	src/SomeClass.hpp
)

add_executable(imgmaker ${MY_SOURCES})
