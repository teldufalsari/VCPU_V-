cmake_minimum_required(VERSION 3.14)
project(Zion_assembly)

set(CMAKE_CXX_STANDARD 14)

add_executable(Zion_assembly main.cpp build.h build.cpp prepare.h prepare.cpp service.h service.cpp)