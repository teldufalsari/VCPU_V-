cmake_minimum_required(VERSION 3.14)
project(Zion_assembly)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(Zion_assembly main.cpp build.h build.cpp prepare.h prepare.cpp service.h service.cpp)