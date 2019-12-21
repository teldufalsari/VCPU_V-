cmake_minimum_required(VERSION 3.14)
project(VCPU C)

set(CMAKE_C_STANDARD 11)

add_executable(VCPU main.c VCPU.c VCPU.h Stack.c Stack.h)