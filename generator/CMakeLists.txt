cmake_minimum_required(VERSION 3.10)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(xvkGenerator)

add_executable(generateXvkInterface "generator.cpp")
